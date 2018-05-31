/*
 * sconfig, coreboot device tree compiler
 *
 * Copyright (C) 2010 coresystems GmbH
 *   written by Patrick Georgi <patrick@georgi-clan.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <ctype.h>
#include "sconfig.h"
#include "sconfig.tab.h"

extern int linenum;

struct device *head, *lastdev;

static struct chip *chip_head;

/*
 * This is intentionally shared between chip and device structure ids because it
 * is easier to track the order of parsing for chip and device.
 */
static int count = 0;

typedef enum {
	UNSLASH,
	SPLIT_1ST,
	TO_LOWER,
	TO_UPPER,
} translate_t;

static struct device root;
static struct chip mainboard = {
	.name = "mainboard",
	.name_underscore = "mainboard",
};

static struct device root = {
	.name = "dev_root",
	.id = 0,
	.chip = &mainboard,
	.path = " .type = DEVICE_PATH_ROOT ",
	.ops = "&default_dev_ops_root",
	.parent = &root,
	.enabled = 1
};

static struct queue {
	void *data;
	struct queue *next;
	struct queue *prev;
} *q;

#define S_ALLOC(_s)	s_alloc(__func__, _s)

static void *s_alloc(const char *f, size_t s)
{
	void *data = calloc(1, s);
	if (!data) {
		fprintf(stderr, "%s: Failed to alloc mem!\n", f, s);
		exit(1);
	}
	return data;
}

struct queue *new_queue_entry(void *data)
{
	struct queue *e = S_ALLOC(sizeof(*e));

	e->data = data;
	e->next = e->prev = e;
	return e;
}

void chip_enqueue_tail(void *data)
{
	struct queue *tmp = new_queue_entry(data);

	if (!q) {
		q = tmp;
		return;
	}

	q->prev->next = tmp;
	tmp->prev = q->prev;
	q->prev = tmp;
	tmp->next = q;
}

void *chip_dequeue_tail(void)
{
	struct queue *tmp = q->prev;
	void *data;

	if (tmp == q)
		q = NULL;
	else {
		tmp->prev->next = q;
		q->prev = tmp->prev;
	}

	data = tmp->data;
	free(tmp);

	return data;
}

static struct device *new_dev(struct device *parent)
{
	struct device *dev = S_ALLOC(sizeof(struct device));

	dev->id = ++count;
	dev->parent = parent;
	dev->subsystem_vendor = -1;
	dev->subsystem_device = -1;
	head->next = dev;
	head = dev;
	return dev;
}

static int device_match(struct device *a, struct device *b)
{
	if ((a->bustype == b->bustype) && (a->parent == b->parent)
	    && (a->path_a == b->path_a) && (a->path_b == b->path_b))
		return 1;
	return 0;
}

void fold_in(struct device *parent)
{
	struct device *child = parent->children;
	struct device *latest = 0;
	while (child != latest) {
		if (child->children) {
			if (!latest)
				latest = child->children;
			parent->latestchild->next_sibling = child->children;
			parent->latestchild = child->latestchild;
		}
		child = child->next_sibling;
	}
}

int yywrap(void)
{
	return 1;
}

void yyerror(char const *str)
{
	extern char *yytext;
	fprintf(stderr, "line %d: %s: %s\n", linenum + 1, yytext, str);
	exit(1);
}

void postprocess_devtree(void)
{
	root.next_sibling = root.children;

	/*
	 * Since root is statically created we need to call fold_in explicitly
	 * here to have the next_sibling and latestchild setup correctly.
	 */
	fold_in(&root);

	struct device *dev = &root;
	while (dev) {
		/* skip functions of the same device in sibling chain */
		while (dev->sibling && dev->sibling->used)
			dev->sibling = dev->sibling->sibling;
		/* skip duplicate function elements in nextdev chain */
		while (dev->nextdev && dev->nextdev->used)
			dev->nextdev = dev->nextdev->nextdev;
		dev = dev->next_sibling;
	}
}

char *translate_name(const char *str, translate_t mode)
{
	char *b, *c;
	b = c = strdup(str);
	while (c && *c) {
		if ((mode == SPLIT_1ST) && (*c == '/')) {
			*c = 0;
			break;
		}
		if (*c == '/')
			*c = '_';
		if (*c == '-')
			*c = '_';
		if (mode == TO_UPPER)
			*c = toupper(*c);
		if (mode == TO_LOWER)
			*c = tolower(*c);
		c++;
	}
	return b;
}

struct chip *new_chip(char *path)
{
	struct chip *new_chip = S_ALLOC(sizeof(*new_chip));

	new_chip->id = ++count;
	new_chip->chiph_exists = 1;
	new_chip->name = path;
	new_chip->name_underscore = translate_name(new_chip->name, UNSLASH);

	struct stat st;
	char *chip_h = S_ALLOC(strlen(path) + 18);
	sprintf(chip_h, "src/%s", path);
	if ((stat(chip_h, &st) == -1) && (errno == ENOENT)) {
		/* root_complex gets away without a separate directory, but
		 * exists on on pretty much all AMD chipsets.
		 */
		if (!strstr(path, "/root_complex")) {
			fprintf(stderr, "ERROR: Chip component %s does not exist.\n",
				path);
			exit(1);
		}
	}

	sprintf(chip_h, "src/%s/chip.h", path);

	if ((stat(chip_h, &st) == -1) && (errno == ENOENT))
		new_chip->chiph_exists = 0;

	free(chip_h);

	new_chip->next = chip_head;
	chip_head = new_chip;

	return new_chip;
}

struct device *new_device(struct device *parent, struct chip *chip,
			  const int bustype, const char *devnum,
			  int enabled)
{
	struct device *new_d = new_dev(parent);
	new_d->bustype = bustype;

	char *tmp;
	new_d->path_a = strtol(devnum, &tmp, 16);
	if (*tmp == '.') {
		tmp++;
		new_d->path_b = strtol(tmp, NULL, 16);
	}

	char *name = S_ALLOC(10);
	sprintf(name, "_dev%d", new_d->id);
	new_d->name = name;

	new_d->enabled = enabled;
	new_d->chip = chip;

	if (parent->latestchild) {
		parent->latestchild->next_sibling = new_d;
		parent->latestchild->sibling = new_d;
	}
	parent->latestchild = new_d;
	if (!parent->children)
		parent->children = new_d;

	lastdev->nextdev = new_d;
	lastdev = new_d;

	switch (bustype) {
	case PCI:
		new_d->path = ".type=DEVICE_PATH_PCI,{.pci={ .devfn = PCI_DEVFN(0x%x,%d)}}";
		break;

	case PNP:
		new_d->path = ".type=DEVICE_PATH_PNP,{.pnp={ .port = 0x%x, .device = 0x%x }}";
		break;

	case I2C:
		new_d->path = ".type=DEVICE_PATH_I2C,{.i2c={ .device = 0x%x, .mode_10bit = %d }}";
		break;

	case APIC:
		new_d->path = ".type=DEVICE_PATH_APIC,{.apic={ .apic_id = 0x%x }}";
		break;

	case CPU_CLUSTER:
		new_d->path = ".type=DEVICE_PATH_CPU_CLUSTER,{.cpu_cluster={ .cluster = 0x%x }}";
		break;

	case CPU:
		new_d->path = ".type=DEVICE_PATH_CPU,{.cpu={ .id = 0x%x }}";
		break;

	case DOMAIN:
		new_d->path = ".type=DEVICE_PATH_DOMAIN,{.domain={ .domain = 0x%x }}";
		break;

	case IOAPIC:
		new_d->path = ".type=DEVICE_PATH_IOAPIC,{.ioapic={ .ioapic_id = 0x%x }}";
		break;

	case GENERIC:
		new_d->path = ".type=DEVICE_PATH_GENERIC,{.generic={ .id = 0x%x, .subid = 0x%x }}";
		break;

	case SPI:
		new_d->path = ".type=DEVICE_PATH_SPI,{.spi={ .cs = 0x%x }}";
		break;

	case USB:
		new_d->path = ".type=DEVICE_PATH_USB,{.usb={ .port_type = %d, .port_id = %d }}";
		break;

	case MMIO:
		new_d->path = ".type=DEVICE_PATH_MMIO,{.mmio={ .addr = 0x%x }}";
		break;
	}

	return new_d;
}

void alias_siblings(struct device *d)
{
	while (d) {
		int link = 0;
		struct device *cmp = d->next_sibling;
		while (cmp && (cmp->parent == d->parent) && (cmp->path_a == d->path_a)
		       && (cmp->path_b == d->path_b)) {
			if (!cmp->used) {
				if (device_match(d, cmp)) {
					d->multidev = 1;

					cmp->id = d->id;
					cmp->name = d->name;
					cmp->used = 1;
					cmp->link = ++link;
				}
			}
			cmp = cmp->next_sibling;
		}
		d = d->next_sibling;
	}
}

void add_resource(struct device *dev, int type, int index, int base)
{
	struct resource *r = S_ALLOC(sizeof(struct resource));

	r->type = type;
	r->index = index;
	r->base = base;
	if (dev->res) {
		struct resource *head = dev->res;
		while (head->next)
			head = head->next;
		head->next = r;
	} else {
		dev->res = r;
	}
	dev->rescnt++;
}

void add_register(struct chip *chip, char *name, char *val)
{
	struct reg *r = S_ALLOC(sizeof(struct reg));

	r->key = name;
	r->value = val;
	if (chip->reg) {
		struct reg *head = chip->reg;
		// sorting to be equal to sconfig's behaviour
		int sort = strcmp(r->key, head->key);
		if (sort == 0) {
			printf("ERROR: duplicate 'register' key.\n");
			exit(1);
		}
		if (sort < 0) {
			r->next = head;
			chip->reg = r;
		} else {
			while ((head->next)
			       && (strcmp(head->next->key, r->key) < 0))
				head = head->next;
			r->next = head->next;
			head->next = r;
		}
	} else {
		chip->reg = r;
	}
}

void add_pci_subsystem_ids(struct device *dev, int vendor, int device,
			   int inherit)
{
	if (dev->bustype != PCI && dev->bustype != DOMAIN) {
		printf("ERROR: 'subsystem' only allowed for PCI devices\n");
		exit(1);
	}

	dev->subsystem_vendor = vendor;
	dev->subsystem_device = device;
	dev->inherit_subsystem = inherit;
}

void add_ioapic_info(struct device *dev, int apicid, const char *_srcpin,
		     int irqpin)
{

	int srcpin;

	if (!_srcpin || strlen(_srcpin) < 4 || strncasecmp(_srcpin, "INT", 3) ||
	    _srcpin[3] < 'A' || _srcpin[3] > 'D') {
		printf("ERROR: malformed ioapic_irq args: %s\n", _srcpin);
		exit(1);
	}

	srcpin = _srcpin[3] - 'A';

	if (dev->bustype != PCI && dev->bustype != DOMAIN) {
		printf("ERROR: ioapic config only allowed for PCI devices\n");
		exit(1);
	}

	if (srcpin > 3) {
		printf("ERROR: srcpin '%d' invalid\n", srcpin);
		exit(1);
	}
	dev->pci_irq_info[srcpin].ioapic_irq_pin = irqpin;
	dev->pci_irq_info[srcpin].ioapic_dst_id = apicid;
}

static void pass0(FILE *fil, struct device *ptr)
{
	if (ptr->id == 0)
		fprintf(fil, "DEVTREE_CONST struct bus %s_links[];\n",
			ptr->name);

	if ((ptr->id != 0) && (!ptr->used)) {
		fprintf(fil, "DEVTREE_CONST static struct device %s;\n",
			ptr->name);
		if (ptr->rescnt > 0)
			fprintf(fil,
				"DEVTREE_CONST struct resource %s_res[];\n",
				ptr->name);
		if (ptr->children || ptr->multidev)
			fprintf(fil, "DEVTREE_CONST struct bus %s_links[];\n",
				ptr->name);
	}
}

static void pass1(FILE *fil, struct device *ptr)
{
	int pin;

	if (!ptr->used) {
		if (ptr->id != 0)
			fprintf(fil, "static ");
		fprintf(fil, "DEVTREE_CONST struct device %s = {\n",
			ptr->name);
		fprintf(fil, "#if !DEVTREE_EARLY\n");
		fprintf(fil, "\t.ops = %s,\n", (ptr->ops) ? (ptr->ops) : "0");
		fprintf(fil, "#endif\n");
		fprintf(fil, "\t.bus = &%s_links[%d],\n", ptr->parent->name,
			ptr->parent->link);
		fprintf(fil, "\t.path = {");
		fprintf(fil, ptr->path, ptr->path_a, ptr->path_b);
		fprintf(fil, "},\n");
		fprintf(fil, "\t.enabled = %d,\n", ptr->enabled);
		fprintf(fil, "\t.on_mainboard = 1,\n");
		if (ptr->subsystem_vendor > 0)
			fprintf(fil, "\t.subsystem_vendor = 0x%04x,\n",
				ptr->subsystem_vendor);

		for (pin = 0; pin < 4; pin++) {
			if (ptr->pci_irq_info[pin].ioapic_irq_pin > 0)
				fprintf(fil, "\t.pci_irq_info[%d].ioapic_irq_pin = %d,\n",
					pin, ptr->pci_irq_info[pin].ioapic_irq_pin);

			if (ptr->pci_irq_info[pin].ioapic_dst_id > 0)
				fprintf(fil, "\t.pci_irq_info[%d].ioapic_dst_id = %d,\n",
					pin, ptr->pci_irq_info[pin].ioapic_dst_id);
		}

		if (ptr->subsystem_device > 0)
			fprintf(fil, "\t.subsystem_device = 0x%04x,\n",
				ptr->subsystem_device);

		if (ptr->rescnt > 0) {
			fprintf(fil, "\t.resource_list = &%s_res[0],\n",
				ptr->name);
		}
		if (ptr->children || ptr->multidev)
			fprintf(fil, "\t.link_list = &%s_links[0],\n",
				ptr->name);
		else
			fprintf(fil, "\t.link_list = NULL,\n");
		if (ptr->sibling)
			fprintf(fil, "\t.sibling = &%s,\n", ptr->sibling->name);
		fprintf(fil, "#if !DEVTREE_EARLY\n");
		fprintf(fil, "\t.chip_ops = &%s_ops,\n",
			ptr->chip->name_underscore);
		if (ptr->chip == &mainboard)
			fprintf(fil, "\t.name = mainboard_name,\n");
		fprintf(fil, "#endif\n");
		if (ptr->chip->chiph_exists)
			fprintf(fil, "\t.chip_info = &%s_info_%d,\n",
				ptr->chip->name_underscore, ptr->chip->id);
		if (ptr->nextdev)
			fprintf(fil, "\t.next=&%s\n", ptr->nextdev->name);
		fprintf(fil, "};\n");
	}
	if (ptr->rescnt > 0) {
		int i = 1;
		fprintf(fil, "DEVTREE_CONST struct resource %s_res[] = {\n",
			ptr->name);
		struct resource *r = ptr->res;
		while (r) {
			fprintf(fil,
				"\t\t{ .flags=IORESOURCE_FIXED | IORESOURCE_ASSIGNED | IORESOURCE_");
			if (r->type == IRQ)
				fprintf(fil, "IRQ");
			if (r->type == DRQ)
				fprintf(fil, "DRQ");
			if (r->type == IO)
				fprintf(fil, "IO");
			fprintf(fil, ", .index=0x%x, .base=0x%x,", r->index,
				r->base);
			if (r->next)
				fprintf(fil, ".next=&%s_res[%d]},\n", ptr->name,
					i++);
			else
				fprintf(fil, ".next=NULL },\n");
			r = r->next;
		}
		fprintf(fil, "\t };\n");
	}
	if (!ptr->used && (ptr->children || ptr->multidev)) {
		fprintf(fil, "DEVTREE_CONST struct bus %s_links[] = {\n",
			ptr->name);
		if (ptr->multidev) {
			struct device *d = ptr;
			while (d) {
				if (device_match(d, ptr)) {
					fprintf(fil, "\t\t[%d] = {\n", d->link);
					fprintf(fil, "\t\t\t.link_num = %d,\n",
						d->link);
					fprintf(fil, "\t\t\t.dev = &%s,\n",
						d->name);
					if (d->children)
						fprintf(fil,
							"\t\t\t.children = &%s,\n",
							d->children->name);
					if (d->next_sibling
					    && device_match(d->next_sibling,
							    ptr))
						fprintf(fil,
							"\t\t\t.next=&%s_links[%d],\n",
							d->name, d->link + 1);
					else
						fprintf(fil,
							"\t\t\t.next = NULL,\n");
					fprintf(fil, "\t\t},\n");
				}
				d = d->next_sibling;
			}
		} else {
			if (ptr->children) {
				fprintf(fil, "\t\t[0] = {\n");
				fprintf(fil, "\t\t\t.link_num = 0,\n");
				fprintf(fil, "\t\t\t.dev = &%s,\n", ptr->name);
				fprintf(fil, "\t\t\t.children = &%s,\n",
					ptr->children->name);
				fprintf(fil, "\t\t\t.next = NULL,\n");
				fprintf(fil, "\t\t},\n");
			}
		}
		fprintf(fil, "\t};\n");
	}
}

static void walk_device_tree(FILE *fil, struct device *ptr,
			     void (*func)(FILE *, struct device *),
			     struct device *chips)
{
	do {
		func(fil, ptr);
		ptr = ptr->next_sibling;
	} while (ptr);
}

static void add_header(struct chip *chip, struct header *h)
{
	int include_exists = 0;

	while (h->next) {
		int result = strcmp(chip->name, h->next->name);
		if (result == 0) {
			include_exists = 1;
			break;
		}
		if (result < 0)
			break;
		h = h->next;
	}

	if (!include_exists) {
		struct header *tmp = h->next;
		h->next = S_ALLOC(sizeof(struct header));

		h->next->chiph_exists = chip->chiph_exists;
		h->next->name = chip->name;
		h->next->next = tmp;
	}
}

static void emit_headers(FILE *fil)
{
	struct header *h;
	struct chip *chip;
	struct header headers = {};

	for (chip = chip_head; chip; chip = chip->next)
		add_header(chip, &headers);

	fprintf(fil, "#include <device/device.h>\n");
	fprintf(fil, "#include <device/pci.h>\n");
	h = &headers;
	while (h->next) {
		h = h->next;
		if (h->chiph_exists)
			fprintf(fil, "#include \"%s/chip.h\"\n", h->name);
	}
	fprintf(fil, "\n#if !DEVTREE_EARLY\n");
	fprintf(fil,
		"__attribute__((weak)) struct chip_operations mainboard_ops = {};\n");
	h = &headers;
	while (h->next) {
		h = h->next;
		char *name_underscore = translate_name(h->name, UNSLASH);
		fprintf(fil,
			"__attribute__((weak)) struct chip_operations %s_ops = {};\n",
			name_underscore);
		free(name_underscore);
	}
	fprintf(fil, "#endif\n");
}

static void emit_chips(FILE *fil)
{
	struct chip *chip;

	emit_headers(fil);

	for (chip = chip_head; chip; chip = chip->next) {
		if (!chip->chiph_exists)
			continue;

		if (chip->reg) {
			fprintf(fil,
				"DEVTREE_CONST struct %s_config %s_info_%d = {\n",
				chip->name_underscore, chip->name_underscore,
				chip->id);
			struct reg *r = chip->reg;
			while (r) {
				fprintf(fil, "\t.%s = %s,\n", r->key, r->value);
				r = r->next;
			}
			fprintf(fil, "};\n\n");
		} else {
			fprintf(fil,
				"DEVTREE_CONST struct %s_config %s_info_%d = { };\n",
				chip->name_underscore, chip->name_underscore,
				chip->id);
		}
	}
}

static void inherit_subsystem_ids(FILE *file, struct device *dev)
{
	struct device *p;

	if (dev->subsystem_vendor != -1 && dev->subsystem_device != -1) {
		/* user already gave us a subsystem vendor/device */
		return;
	}

	for (p = dev; p && p != p->parent; p = p->parent) {

		if (p->bustype != PCI && p->bustype != DOMAIN)
			continue;

		if (p->inherit_subsystem) {
			dev->subsystem_vendor = p->subsystem_vendor;
			dev->subsystem_device = p->subsystem_device;
			break;
		}
	}
}

static void usage(void)
{
	printf("usage: sconfig devicetree_file output_file\n");
	exit(1);
}

enum {
	DEVICEFILE_ARG = 1,
	OUTPUTFILE_ARG
};

#define ARG_COUNT		3

int main(int argc, char **argv)
{
	if (argc != ARG_COUNT)
		usage();

	char *devtree = argv[DEVICEFILE_ARG];
	char *outputc = argv[OUTPUTFILE_ARG];

	FILE *filec = fopen(devtree, "r");
	if (!filec) {
		perror(NULL);
		exit(1);
	}

	yyrestart(filec);

	lastdev = head = &root;

	yyparse();

	fclose(filec);

	FILE *autogen = fopen(outputc, "w");
	if (!autogen) {
		fprintf(stderr, "Could not open file '%s' for writing: ",
			outputc);
		perror(NULL);
		exit(1);
	}

	emit_chips(autogen);

	walk_device_tree(autogen, &root, inherit_subsystem_ids, NULL);
	fprintf(autogen, "\n/* pass 0 */\n");
	walk_device_tree(autogen, &root, pass0, NULL);
	fprintf(autogen, "\n/* pass 1 */\n"
		"DEVTREE_CONST struct device * DEVTREE_CONST last_dev = &%s;\n",
		lastdev->name);
	walk_device_tree(autogen, &root, pass1, NULL);

	fclose(autogen);

	return 0;
}
