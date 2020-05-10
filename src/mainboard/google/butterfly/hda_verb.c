/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	/* --- Codec #0 --- */
	0x111d76e5,	// Codec Vendor / Device ID: IDT 92HD99
	0x103c18f9,	// Subsystem ID
	115,		// Number of 4 dword sets
	AZALIA_SUBVENDOR(0, 0x103c18F9),

	/* Ext. Microphone Connector:	External,Right; MicIn,3.5mm; Black,JD; DA,Seq */
	AZALIA_PIN_CFG(0, 0x0a, 0x04a11020),

	/* Headphones Connector:	External,Right; HP,3.5mm; Black,JD; DA,Seq */
	AZALIA_PIN_CFG(0, 0x0b, 0x0421101f),

	/* Not connected:		N/A,N/A; Other,Unknown; Unknown,JD; DA,Seq */
	AZALIA_PIN_CFG(0, 0x0c, 0x40f000f0),

	/* Internal Speakers:		Fixed,Int; Speaker,Other Analog; Unknown,nJD; DA,Seq */
	AZALIA_PIN_CFG(0, 0x0d, 0x90170110),

	/* Not connected */
	AZALIA_PIN_CFG(0, 0x0f, 0x40f000f0),

	/* Internal Microphone:		Fixed,Int,Top; Mic In,ATIPI; Unknown,nJD; DA,Seq */
	AZALIA_PIN_CFG(0, 0x11, 0xd5a30140),

	/*
	 * Hardware EQ Parameters
	 * Sample Rate 88200
	 */
	0x0227a63f,	0x0227a73e,	0x0227a8eb,	0x0227a93f,
	0x0227aa3e,	0x0227abeb,	0x0227ac00,	0x0227ad80,
	0x0227a681,	0x0227a782,	0x0227a829,	0x0227a981,
	0x0227aa82,	0x0227ab29,	0x0227ac01,	0x0227ad80,
	0x0227a63f,	0x0227a73e,	0x0227a8eb,	0x0227a93f,
	0x0227aa3e,	0x0227abeb,	0x0227ac02,	0x0227ad80,
	0x0227a67e,	0x0227a77b,	0x0227a846,	0x0227a97e,
	0x0227aa7b,	0x0227ab46,	0x0227ac03,	0x0227ad80,
	0x0227a6c1,	0x0227a77f,	0x0227a898,	0x0227a9c1,
	0x0227aa7f,	0x0227ab98,	0x0227ac04,	0x0227ad80,
	0x0227a63e,	0x0227a7d1,	0x0227a84f,	0x0227a93e,
	0x0227aad1,	0x0227ab4f,	0x0227ac05,	0x0227ad80,
	0x0227a683,	0x0227a7be,	0x0227a855,	0x0227a983,
	0x0227aabe,	0x0227ab55,	0x0227ac06,	0x0227ad80,
	0x0227a63d,	0x0227a7b9,	0x0227a856,	0x0227a93d,
	0x0227aab9,	0x0227ab56,	0x0227ac07,	0x0227ad80,
	0x0227a67c,	0x0227a741,	0x0227a8ab,	0x0227a97c,
	0x0227aa41,	0x0227abab,	0x0227ac08,	0x0227ad80,
	0x0227a6c3,	0x0227a775,	0x0227a85a,	0x0227a9c3,
	0x0227aa75,	0x0227ab5a,	0x0227ac09,	0x0227ad80,
	0x0227a63f,	0x0227a79e,	0x0227a829,	0x0227a93f,
	0x0227aa9e,	0x0227ab29,	0x0227ac0a,	0x0227ad80,
	0x0227a682,	0x0227a7e3,	0x0227a867,	0x0227a982,
	0x0227aae3,	0x0227ab67,	0x0227ac0b,	0x0227ad80,
	0x0227a63e,	0x0227a74f,	0x0227a89d,	0x0227a93e,
	0x0227aa4f,	0x0227ab9d,	0x0227ac0c,	0x0227ad80,
	0x0227a67d,	0x0227a71c,	0x0227a899,	0x0227a97d,
	0x0227aa1c,	0x0227ab99,	0x0227ac0d,	0x0227ad80,
	0x0227a6c2,	0x0227a712,	0x0227a839,	0x0227a9c2,
	0x0227aa12,	0x0227ab39,	0x0227ac0e,	0x0227ad80,
	0x0227a63f,	0x0227a708,	0x0227a856,	0x0227a93f,
	0x0227aa08,	0x0227ab56,	0x0227ac0f,	0x0227ad80,
	0x0227a68e,	0x0227a7ed,	0x0227a89d,	0x0227a98e,
	0x0227aaed,	0x0227ab9d,	0x0227ac10,	0x0227ad80,
	0x0227a637,	0x0227a78f,	0x0227a853,	0x0227a937,
	0x0227aa8f,	0x0227ab53,	0x0227ac11,	0x0227ad80,
	0x0227a671,	0x0227a712,	0x0227a863,	0x0227a971,
	0x0227aa12,	0x0227ab63,	0x0227ac12,	0x0227ad80,
	0x0227a6c9,	0x0227a768,	0x0227a856,	0x0227a9c9,
	0x0227aa68,	0x0227ab56,	0x0227ac13,	0x0227ad80,
	0x0227a642,	0x0227a709,	0x0227a838,	0x0227a942,
	0x0227aa09,	0x0227ab38,	0x0227ac14,	0x0227ad80,
	0x0227a69c,	0x0227a78a,	0x0227a867,	0x0227a99c,
	0x0227aa8a,	0x0227ab67,	0x0227ac15,	0x0227ad80,
	0x0227a634,	0x0227a717,	0x0227a8e3,	0x0227a934,
	0x0227aa17,	0x0227abe3,	0x0227ac16,	0x0227ad80,
	0x0227a663,	0x0227a775,	0x0227a899,	0x0227a963,
	0x0227aa75,	0x0227ab99,	0x0227ac17,	0x0227ad80,
	0x0227a6c9,	0x0227a7de,	0x0227a8e5,	0x0227a9c9,
	0x0227aade,	0x0227abe5,	0x0227ac18,	0x0227ad80,
	0x0227a640,	0x0227a700,	0x0227a800,	0x0227a940,
	0x0227aa00,	0x0227ab00,	0x0227ac19,	0x0227ad80,

	/*
	 * Hardware EQ Parameters
	 * Sample Rate 96000
	 */
	0x0227a63f,	0x0227a74e,	0x0227a888,	0x0227a93f,
	0x0227aa4e,	0x0227ab88,	0x0227ac1a,	0x0227ad80,
	0x0227a681,	0x0227a762,	0x0227a8ee,	0x0227a981,
	0x0227aa62,	0x0227abee,	0x0227ac1b,	0x0227ad80,
	0x0227a63f,	0x0227a74e,	0x0227a888,	0x0227a93f,
	0x0227aa4e,	0x0227ab88,	0x0227ac1c,	0x0227ad80,
	0x0227a67e,	0x0227a79a,	0x0227a8e7,	0x0227a97e,
	0x0227aa9a,	0x0227abe7,	0x0227ac1d,	0x0227ad80,
	0x0227a6c1,	0x0227a760,	0x0227a8c3,	0x0227a9c1,
	0x0227aa60,	0x0227abc3,	0x0227ac1e,	0x0227ad80,
	0x0227a63e,	0x0227a7e9,	0x0227a84b,	0x0227a93e,
	0x0227aae9,	0x0227ab4b,	0x0227ac1f,	0x0227ad80,
	0x0227a683,	0x0227a76c,	0x0227a8f2,	0x0227a983,
	0x0227aa6c,	0x0227abf2,	0x0227ac20,	0x0227ad80,
	0x0227a63d,	0x0227a7e7,	0x0227a880,	0x0227a93d,
	0x0227aae7,	0x0227ab80,	0x0227ac21,	0x0227ad80,
	0x0227a67c,	0x0227a793,	0x0227a80e,	0x0227a97c,
	0x0227aa93,	0x0227ab0e,	0x0227ac22,	0x0227ad80,
	0x0227a6c3,	0x0227a72f,	0x0227a835,	0x0227a9c3,
	0x0227aa2f,	0x0227ab35,	0x0227ac23,	0x0227ad80,
	0x0227a63f,	0x0227a7a5,	0x0227a8fe,	0x0227a93f,
	0x0227aaa5,	0x0227abfe,	0x0227ac24,	0x0227ad80,
	0x0227a682,	0x0227a798,	0x0227a89d,	0x0227a982,
	0x0227aa98,	0x0227ab9d,	0x0227ac25,	0x0227ad80,
	0x0227a63e,	0x0227a772,	0x0227a839,	0x0227a93e,
	0x0227aa72,	0x0227ab39,	0x0227ac26,	0x0227ad80,
	0x0227a67d,	0x0227a767,	0x0227a863,	0x0227a97d,
	0x0227aa67,	0x0227ab63,	0x0227ac27,	0x0227ad80,
	0x0227a6c1,	0x0227a7e7,	0x0227a8c8,	0x0227a9c1,
	0x0227aae7,	0x0227abc8,	0x0227ac28,	0x0227ad80,
	0x0227a63f,	0x0227a71b,	0x0227a81a,	0x0227a93f,
	0x0227aa1b,	0x0227ab1a,	0x0227ac29,	0x0227ad80,
	0x0227a68d,	0x0227a763,	0x0227a872,	0x0227a98d,
	0x0227aa63,	0x0227ab72,	0x0227ac2a,	0x0227ad80,
	0x0227a638,	0x0227a733,	0x0227a809,	0x0227a938,
	0x0227aa33,	0x0227ab09,	0x0227ac2b,	0x0227ad80,
	0x0227a672,	0x0227a79c,	0x0227a88e,	0x0227a972,
	0x0227aa9c,	0x0227ab8e,	0x0227ac2c,	0x0227ad80,
	0x0227a6c8,	0x0227a7b1,	0x0227a8dd,	0x0227a9c8,
	0x0227aab1,	0x0227abdd,	0x0227ac2d,	0x0227ad80,
	0x0227a641,	0x0227a7e1,	0x0227a8d8,	0x0227a941,
	0x0227aae1,	0x0227abd8,	0x0227ac2e,	0x0227ad80,
	0x0227a699,	0x0227a70d,	0x0227a820,	0x0227a999,
	0x0227aa0d,	0x0227ab20,	0x0227ac2f,	0x0227ad80,
	0x0227a634,	0x0227a7fe,	0x0227a823,	0x0227a934,
	0x0227aafe,	0x0227ab23,	0x0227ac30,	0x0227ad80,
	0x0227a666,	0x0227a7f2,	0x0227a8e0,	0x0227a966,
	0x0227aaf2,	0x0227abe0,	0x0227ac31,	0x0227ad80,
	0x0227a6c9,	0x0227a720,	0x0227a804,	0x0227a9c9,
	0x0227aa20,	0x0227ab04,	0x0227ac32,	0x0227ad80,
	0x0227a640,	0x0227a700,	0x0227a800,	0x0227a940,
	0x0227aa00,	0x0227ab00,	0x0227ac33,	0x0227ad80,

	/* SAFEDSP Parameters */
	0x022782c1,	0x02277127,	0x02277227,	0x02278801,
	0x02278c58,	0x02278e90,	0x0227890a,	0x02278a14,
	0x02278b0f,	0x0017b008,

	/* Misc entries */
		0x00b707c0, /* Enable PortB as Output with HP amp */
		0x00d70740, /* Enable PortD as Output */
		0x0017a200, /* Disable ClkEn of PortSenseTst */
		0x0017c621, /* Slave Port - Port A used as microphone input for
		                            combo Jack
		               Master Port - Port B used for Jack Presence Detect
		               Enable Combo Jack Detection */
		0x0017a208, /* Enable ClkEn of PortSenseTst */
		0x00170500, /* Set power state to D0 */

	/* --- Codec #3 --- */
	0x80862806,	// Codec Vendor / Device ID: Intel PantherPoint HDMI
	0x80860101,	// Subsystem ID
			// Revision ID: 0x100000
	4,		// Number of 4 dword sets
	AZALIA_SUBVENDOR(3, 0x80860101),
	AZALIA_PIN_CFG(3, 0x05, 0x18560010),
	AZALIA_PIN_CFG(3, 0x06, 0x18560020),
	AZALIA_PIN_CFG(3, 0x07, 0x18560030),
};

const u32 pc_beep_verbs[] = {
	0x02177a00, /* Digital PCBEEP Gain: 0h=-9db, 1h=-6db ... 4h=+3db, 5h=+6db */
};

AZALIA_ARRAY_SIZES;
