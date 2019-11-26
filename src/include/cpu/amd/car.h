#ifndef _CPU_AMD_CAR_H
#define _CPU_AMD_CAR_H

#include <arch/cpu.h>

void cache_as_ram_main(unsigned long bist, unsigned long cpu_init_detectedx);

void asmlinkage early_all_cores(void);

void *asmlinkage romstage_main(unsigned long bist);
void asmlinkage romstage_after_car(void);

#endif
