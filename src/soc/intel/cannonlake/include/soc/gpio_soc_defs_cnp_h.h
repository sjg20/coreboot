/*
 * This file is part of the coreboot project.
 *
 * Copyright 2018 Intel Corp.
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

#ifndef _SOC_CANNONLAKE_GPIO_SOC_DEFS_CNP_H_H_
#define _SOC_CANNONLAKE_GPIO_SOC_DEFS_CNP_H_H_

/*
 * Most of the fixed numbers and macros are based on the GPP groups.
 * The GPIO groups are accessed through register blocks called
 * communities.
 */

#define GPP_A			0
#define GPP_B			1
#define GPP_C			2
#define GPP_D			3
#define GPP_G			4
#define GPP_K			5
#define GPP_H			6
#define GPP_E			7
#define GPP_F			8
#define GPP_I			9
#define GPP_J			0xA
#define GPD			0xC
#define GPIO_NUM_GROUPS		12
#define GPIO_MAX_NUM_PER_GROUP	24

/*
 * GPIOs are ordered monotonically increasing to match ACPI/OS driver.
 */

/* Group A */
#define GPP_A0			0
#define GPP_A1			1
#define GPP_A2			2
#define GPP_A3			3
#define GPP_A4			4
#define GPP_A5			5
#define GPP_A6			6
#define GPP_A7			7
#define GPP_A8			8
#define GPP_A9			9
#define GPP_A10			10
#define GPP_A11			11
#define GPP_A12			12
#define GPP_A13			13
#define GPP_A14			14
#define GPP_A15			15
#define GPP_A16			16
#define GPP_A17			17
#define GPP_A18			18
#define GPP_A19			19
#define GPP_A20			20
#define GPP_A21			21
#define GPP_A22			22
#define GPP_A23			23
#define GPIO_RSVD_0		24

/* Group B */
#define GPP_B0			25
#define GPP_B1			26
#define GPP_B2			27
#define GPP_B3			28
#define GPP_B4			29
#define GPP_B5			30
#define GPP_B6			31
#define GPP_B7			32
#define GPP_B8			33
#define GPP_B9			34
#define GPP_B10			35
#define GPP_B11			36
#define GPP_B12			37
#define GPP_B13			38
#define GPP_B14			39
#define GPP_B15			40
#define GPP_B16			41
#define GPP_B17			42
#define GPP_B18			43
#define GPP_B19			44
#define GPP_B20			45
#define GPP_B21			46
#define GPP_B22			47
#define GPP_B23			48
#define GPIO_RSVD_1		49
#define GPIO_RSVD_2		50

#define NUM_GPIO_COM0_PADS	(GPIO_RSVD_2 - GPP_A0 + 1)

/* Group C */
#define GPP_C0			51
#define GPP_C1			52
#define GPP_C2			53
#define GPP_C3			54
#define GPP_C4			55
#define GPP_C5			56
#define GPP_C6			57
#define GPP_C7			58
#define GPP_C8			59
#define GPP_C9			60
#define GPP_C10			61
#define GPP_C11			62
#define GPP_C12			63
#define GPP_C13			64
#define GPP_C14			65
#define GPP_C15			66
#define GPP_C16			67
#define GPP_C17			68
#define GPP_C18			69
#define GPP_C19			70
#define GPP_C20			71
#define GPP_C21			72
#define GPP_C22			73
#define GPP_C23			74

/* Group D */
#define GPP_D0			75
#define GPP_D1			76
#define GPP_D2			77
#define GPP_D3			78
#define GPP_D4			79
#define GPP_D5			80
#define GPP_D6			81
#define GPP_D7			82
#define GPP_D8			83
#define GPP_D9			84
#define GPP_D10			85
#define GPP_D11			86
#define GPP_D12			87
#define GPP_D13			88
#define GPP_D14			89
#define GPP_D15			90
#define GPP_D16			91
#define GPP_D17			92
#define GPP_D18			93
#define GPP_D19			94
#define GPP_D20			95
#define GPP_D21			96
#define GPP_D22			97
#define GPP_D23			98

/* Group G */
#define GPP_G0			99
#define GPP_G1			100
#define GPP_G2			101
#define GPP_G3			102
#define GPP_G4			103
#define GPP_G5			104
#define GPP_G6			105
#define GPP_G7			106

/* AZA */
#define GPIO_RSVD_3		107
#define GPIO_RSVD_4		108
#define GPIO_RSVD_5		109
#define GPIO_RSVD_6		110
#define GPIO_RSVD_7		111
#define GPIO_RSVD_8		112
#define GPIO_RSVD_9		113
#define GPIO_RSVD_10		114

/* VGPIO_0 */
#define GPIO_RSVD_11		115
#define GPIO_RSVD_12		116
#define GPIO_RSVD_13		117
#define GPIO_RSVD_14		118
#define GPIO_RSVD_15		119
#define GPIO_RSVD_16		120
#define GPIO_RSVD_17		121
#define GPIO_RSVD_18		122
#define GPIO_RSVD_19		123
#define GPIO_RSVD_20		124
#define GPIO_RSVD_21		125
#define GPIO_RSVD_22		126
#define GPIO_RSVD_23		127
#define GPIO_RSVD_24		128
#define GPIO_RSVD_25		129
#define GPIO_RSVD_26		130
#define GPIO_RSVD_27		131
#define GPIO_RSVD_28		132
#define GPIO_RSVD_29		133
#define GPIO_RSVD_30		134
#define GPIO_RSVD_31		135
#define GPIO_RSVD_32		136
#define GPIO_RSVD_33		137
#define GPIO_RSVD_34		138
#define GPIO_RSVD_35		139
#define GPIO_RSVD_36		140
#define GPIO_RSVD_37		141
#define GPIO_RSVD_38		142
#define GPIO_RSVD_39		143
#define GPIO_RSVD_40		144
#define GPIO_RSVD_41		145
#define GPIO_RSVD_42		146

/* VGPIO_1 */
#define GPIO_RSVD_43		147
#define GPIO_RSVD_44		148
#define GPIO_RSVD_45		149
#define GPIO_RSVD_46		150
#define GPIO_RSVD_47		151
#define GPIO_RSVD_48		152
#define GPIO_RSVD_49		153
#define GPIO_RSVD_50		154

#define NUM_GPIO_COM1_PADS	(GPIO_RSVD_50 - GPP_C0 + 1)

/* Group K */
#define GPP_K0			155
#define GPP_K1			156
#define GPP_K2			157
#define GPP_K3			158
#define GPP_K4			159
#define GPP_K5			160
#define GPP_K6			161
#define GPP_K7			162
#define GPP_K8			163
#define GPP_K9			164
#define GPP_K10			165
#define GPP_K11			166
#define GPP_K12			167
#define GPP_K13			168
#define GPP_K14			169
#define GPP_K15			170
#define GPP_K16			171
#define GPP_K17			172
#define GPP_K18			173
#define GPP_K19			174
#define GPP_K20			175
#define GPP_K21			176
#define GPP_K22			177
#define GPP_K23			178

/* Group H */
#define GPP_H0			179
#define GPP_H1			180
#define GPP_H2			181
#define GPP_H3			182
#define GPP_H4			183
#define GPP_H5			184
#define GPP_H6			185
#define GPP_H7			186
#define GPP_H8			187
#define GPP_H9			188
#define GPP_H10			189
#define GPP_H11			190
#define GPP_H12			191
#define GPP_H13			192
#define GPP_H14			193
#define GPP_H15			194
#define GPP_H16			195
#define GPP_H17			196
#define GPP_H18			197
#define GPP_H19			198
#define GPP_H20			199
#define GPP_H21			200
#define GPP_H22			201
#define GPP_H23			202

/* Group E */
#define GPP_E0			203
#define GPP_E1			204
#define GPP_E2			205
#define GPP_E3			206
#define GPP_E4			207
#define GPP_E5			208
#define GPP_E6			209
#define GPP_E7			210
#define GPP_E8			211
#define GPP_E9			212
#define GPP_E10			213
#define GPP_E11			214
#define GPP_E12			215

/* Group F */
#define GPP_F0			216
#define GPP_F1			217
#define GPP_F2			218
#define GPP_F3			219
#define GPP_F4			220
#define GPP_F5			221
#define GPP_F6			222
#define GPP_F7			223
#define GPP_F8			224
#define GPP_F9			225
#define GPP_F10			226
#define GPP_F11			227
#define GPP_F12			228
#define GPP_F13			229
#define GPP_F14			230
#define GPP_F15			231
#define GPP_F16			232
#define GPP_F17			233
#define GPP_F18			234
#define GPP_F19			235
#define GPP_F20			236
#define GPP_F21			237
#define GPP_F22			238
#define GPP_F23			239

/* SPI */
#define GPIO_RSVD_51		240
#define GPIO_RSVD_52		241
#define GPIO_RSVD_53		242
#define GPIO_RSVD_54		243
#define GPIO_RSVD_55		244
#define GPIO_RSVD_56		245
#define GPIO_RSVD_57		246
#define GPIO_RSVD_58		247
#define GPIO_RSVD_59		248

#define NUM_GPIO_COM3_PADS	(GPIO_RSVD_59 - GPP_K0 + 1)

/* CPU */
#define GPIO_RSVD_60		249
#define GPIO_RSVD_61		250
#define GPIO_RSVD_62		251
#define GPIO_RSVD_63		252
#define GPIO_RSVD_64		253
#define GPIO_RSVD_65		254
#define GPIO_RSVD_66		255
#define GPIO_RSVD_67		256
#define GPIO_RSVD_68		257
#define GPIO_RSVD_69		258
#define GPIO_RSVD_70		259

/* JTAG */
#define GPIO_RSVD_71		260
#define GPIO_RSVD_72		261
#define GPIO_RSVD_73		262
#define GPIO_RSVD_74		263
#define GPIO_RSVD_75		264
#define GPIO_RSVD_76		265
#define GPIO_RSVD_77		266
#define GPIO_RSVD_78		267
#define GPIO_RSVD_79		268

/* Group I */
#define GPP_I0			269
#define GPP_I1			270
#define GPP_I2			271
#define GPP_I3			272
#define GPP_I4			273
#define GPP_I5			274
#define GPP_I6			275
#define GPP_I7			276
#define GPP_I8			277
#define GPP_I9			278
#define GPP_I10			279
#define GPP_I11			280
#define GPP_I12			281
#define GPP_I13			282
#define GPP_I14			283
#define GPIO_RSVD_80		284
#define GPIO_RSVD_81		285
#define GPIO_RSVD_82		286

/* Group J */
#define GPP_J0			287
#define GPP_J1			288
#define GPP_J2			289
#define GPP_J3			290
#define GPP_J4			291
#define GPP_J5			292
#define GPP_J6			293
#define GPP_J7			294
#define GPP_J8			295
#define GPP_J9			296
#define GPP_J10			297
#define GPP_J11			298

#define NUM_GPIO_COM4_PADS	(GPP_J11 - GPP_I0 + 1)

/* Group GPD  */
#define GPD0			299
#define GPD1			300
#define GPD2			301
#define GPD3			302
#define GPD4			303
#define GPD5			304
#define GPD6			305
#define GPD7			306
#define GPD8			307
#define GPD9			308
#define GPD10			309
#define GPD11			310

#define NUM_GPIO_COM2_PADS	(GPD11 - GPD0 + 1)

#define TOTAL_PADS		(GPD11 + 1)

#endif
