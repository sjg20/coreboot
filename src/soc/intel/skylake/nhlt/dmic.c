/* SPDX-License-Identifier: GPL-2.0-only */

#include <soc/nhlt.h>

static const struct nhlt_format_config dmic_1ch_formats[] = {
	/* 48 KHz 16-bits per sample. */
	{
		.num_channels = 1,
		.sample_freq_khz = 48,
		.container_bits_per_sample = 16,
		.valid_bits_per_sample = 16,
		.speaker_mask = SPEAKER_FRONT_CENTER,
		.settings_file = "dmic-1ch-48khz-16b.bin",
	},
};

static const struct nhlt_dmic_array_config dmic_1ch_mic_config = {
	.tdm_config = {
		.config_type = NHLT_TDM_BASIC,
	},
	.array_type = NHLT_MIC_ARRAY_VENDOR_DEFINED,
};

static const struct nhlt_endp_descriptor dmic_1ch_descriptors[] = {
	{
		.link = NHLT_LINK_PDM,
		.device = NHLT_PDM_DEV_CAVS15,
		.direction = NHLT_DIR_CAPTURE,
		.vid = NHLT_VID,
		.did = NHLT_DID_DMIC,
		.cfg = &dmic_1ch_mic_config,
		.cfg_size = sizeof(dmic_1ch_mic_config),
		.formats = dmic_1ch_formats,
		.num_formats = ARRAY_SIZE(dmic_1ch_formats),
	},
};

static const struct nhlt_format_config dmic_2ch_formats[] = {
	/* 48 KHz 16-bits per sample. */
	{
		.num_channels = 2,
		.sample_freq_khz = 48,
		.container_bits_per_sample = 16,
		.valid_bits_per_sample = 16,
		.speaker_mask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT,
		.settings_file = "dmic-2ch-48khz-16b.bin",
	},
	/* 48 KHz 32-bits per sample. */
	{
		.num_channels = 2,
		.sample_freq_khz = 48,
		.container_bits_per_sample = 32,
		.valid_bits_per_sample = 32,
		.speaker_mask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT,
		.settings_file = "dmic-2ch-48khz-32b.bin",
	},
};

static const struct nhlt_dmic_array_config dmic_2ch_mic_config = {
	.tdm_config = {
		.config_type = NHLT_TDM_MIC_ARRAY,
	},
	.array_type = NHLT_MIC_ARRAY_2CH_SMALL,
};

static const struct nhlt_endp_descriptor dmic_2ch_descriptors[] = {
	{
		.link = NHLT_LINK_PDM,
		.device = NHLT_PDM_DEV_CAVS15,
		.direction = NHLT_DIR_CAPTURE,
		.vid = NHLT_VID,
		.did = NHLT_DID_DMIC,
		.cfg = &dmic_2ch_mic_config,
		.cfg_size = sizeof(dmic_2ch_mic_config),
		.formats = dmic_2ch_formats,
		.num_formats = ARRAY_SIZE(dmic_2ch_formats),
	},
};

static const struct nhlt_format_config dmic_4ch_formats[] = {
	/* 48 KHz 16-bits per sample. */
	{
		.num_channels = 4,
		.sample_freq_khz = 48,
		.container_bits_per_sample = 16,
		.valid_bits_per_sample = 16,
		.speaker_mask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
				SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT,
		.settings_file = "dmic-4ch-48khz-16b.bin",
	},
	/* 48 KHz 32-bits per sample. */
	{
		.num_channels = 4,
		.sample_freq_khz = 48,
		.container_bits_per_sample = 32,
		.valid_bits_per_sample = 32,
		.speaker_mask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT |
				SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT,
		.settings_file = "dmic-4ch-48khz-32b.bin",
	},
};

static const struct nhlt_dmic_array_config dmic_4ch_mic_config = {
	.tdm_config = {
		.config_type = NHLT_TDM_MIC_ARRAY,
	},
	.array_type = NHLT_MIC_ARRAY_4CH_L_SHAPED,
};

static const struct nhlt_endp_descriptor dmic_4ch_descriptors[] = {
	{
		.link = NHLT_LINK_PDM,
		.device = NHLT_PDM_DEV_CAVS15,
		.direction = NHLT_DIR_CAPTURE,
		.vid = NHLT_VID,
		.did = NHLT_DID_DMIC,
		.cfg = &dmic_4ch_mic_config,
		.cfg_size = sizeof(dmic_4ch_mic_config),
		.formats = dmic_4ch_formats,
		.num_formats = ARRAY_SIZE(dmic_4ch_formats),
	},
};

int nhlt_soc_add_dmic_array(struct nhlt *nhlt, int num_channels)
{
	switch (num_channels) {
	case 1:
		return nhlt_add_endpoints(nhlt, dmic_1ch_descriptors,
					ARRAY_SIZE(dmic_1ch_descriptors));
	case 2:
		return nhlt_add_endpoints(nhlt, dmic_2ch_descriptors,
					ARRAY_SIZE(dmic_2ch_descriptors));
	case 4:
		return nhlt_add_endpoints(nhlt, dmic_4ch_descriptors,
					ARRAY_SIZE(dmic_4ch_descriptors));
	default:
		return -1;
	}
}
