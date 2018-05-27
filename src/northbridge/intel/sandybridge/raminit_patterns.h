/*
 * This file is part of the coreboot project.
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

#ifndef SANDYBRIDGE_RAMINIT_PATTERNS_H
#define SANDYBRIDGE_RAMINIT_PATTERNS_H

const u32 pattern[][16] = {
	{0x00000000, 0x00000000, 0xffffffff, 0xffffffff,
	 0x00000000, 0x00000000, 0xffffffff, 0xffffffff,
	 0x00000000, 0x00000000, 0xffffffff, 0xffffffff,
	 0x00000000, 0x00000000, 0xffffffff, 0xffffffff},
	{0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
	 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
	 0xffffffff, 0xffffffff, 0x00000000, 0x00000000,
	 0xffffffff, 0xffffffff, 0x00000000, 0x00000000},
	{0xe62d6424, 0x9277e09e, 0x8f43dc3f, 0x76eae589,
	 0x0010fdc6, 0xdc55e01c, 0x5effb0ab, 0x6cba5d29,
	 0xa43d1e64, 0xab5c2e0f, 0x7796ed16, 0x96023bf4,
	 0xa74c831d, 0x90f138c0, 0x17830a8a, 0x5ac17c47},
	{0x359ebbeb, 0x2b9b4512, 0xef584d98, 0x106bf7cb,
	 0x363525ad, 0xb3a4dfdc, 0xa6b9fcd8, 0xd21689ec,
	 0x84a3695b, 0xbd9c2e27, 0xdb3d0f44, 0x988158f1,
	 0xcca91d3f, 0xb62a6d12, 0xe905e4cf, 0x7f1fa626},
	{0xe58efeae, 0xcd006081, 0xa9119403, 0xbcfbd35f,
	 0x213b3bf7, 0x7bfcb773, 0xc85143f9, 0x0bdbff50,
	 0xa3053c90, 0x51d66cb7, 0x296f4387, 0xb715f99e,
	 0xfaddc989, 0xbb1de8a7, 0x39206b4d, 0x80174a57},
	{0xa1622ac1, 0xb4f4a5f0, 0x16dc2bc3, 0x50fb0954,
	 0x2e261721, 0x52b82c3c, 0x821902b8, 0x0d4b6c38,
	 0x1f618631, 0x047956f3, 0xd4337f5a, 0x591f8002,
	 0x27f28db2, 0xfae37369, 0xb3f27580, 0x3cdb6397},
	{0x3dee23be, 0x19f36408, 0x227f4a6a, 0x024603c5,
	 0xd5e062db, 0x6d8d4c5c, 0x7ff693b0, 0x76641be9,
	 0x9e74f41c, 0xe7bc7f33, 0x2636f2e9, 0x70279750,
	 0xce2355aa, 0x32d230ef, 0x22f9b468, 0xadd4e7a2},
	{0x936c0fed, 0xba0612d5, 0xa97c1ea7, 0x10e29d67,
	 0x1c4c5dc8, 0x83645621, 0xcd8b521c, 0xb8301817,
	 0xac7d6571, 0xcc41d200, 0x4ebdefdd, 0xd2917bde,
	 0x60f75acc, 0x7791534b, 0x26ea2a83, 0x6b74513a},
	{0xd1957b85, 0xc6f8f9ca, 0xf04fb4be, 0xfeb786fb,
	 0xa1dea3aa, 0x67fe7db6, 0x25d49c87, 0xe3d54870,
	 0x93dc1f86, 0x7d0c1a18, 0x9272e128, 0x68e1b876,
	 0xce284c9e, 0x8fa18792, 0x5785a340, 0xb6fcf198},
	{0xff7d8e4a, 0x0c21ee43, 0xe820b388, 0xb4443c0e,
	 0xa1e6e498, 0x5c426110, 0x1b434ef3, 0xbef05b91,
	 0xa6907968, 0x53662ac3, 0x6defac32, 0x2c11c29c,
	 0x6175cced, 0xb17dd3ad, 0x6e6a1076, 0x1372b1fa},
	{0x4408ed06, 0x49460ffd, 0xb49d26cb, 0x6a3662a5,
	 0x5e857047, 0xa387cd4a, 0x04edc81e, 0xfd94d8d4,
	 0x2fe48d91, 0x9d2356bc, 0x96131878, 0xaca3fce4,
	 0xbb312c6c, 0x5023b090, 0x3614be70, 0xa14dfabb},
	{0xd4cc1e83, 0x757a1930, 0xc3d16a61, 0x9e0d6681,
	 0x8a081fa9, 0xbd11c888, 0x1672f010, 0xa083f71c,
	 0x1ec02eef, 0xc4586ca8, 0x6d322b35, 0x56054679,
	 0x1552a0ff, 0x5cb7707e, 0xdfb55d4a, 0xcc76cc07},
	{0x507cf71f, 0x2166421a, 0x54be4af0, 0xfd42158c,
	 0x417b1f7f, 0x9466860b, 0x3a0075bf, 0x2055575c,
	 0xcedfe7ab, 0xbe85aa5f, 0x39d0c2e3, 0x851c19df,
	 0x39a35a3f, 0x3fb10d7d, 0x20b14899, 0x703b7f08},
	{0x8a7d9dd1, 0x33235565, 0xbd3d2e57, 0xa48c2726,
	 0x0d5e2e13, 0xae421ff9, 0x8784a224, 0xf66c1510,
	 0x057627aa, 0x8fb0cb41, 0x4289975a, 0xb181adfa,
	 0x59f2059a, 0xe86feb05, 0x84222fc1, 0x319b3ce9},
	{0xe1e243b8, 0x3b0bcc1a, 0x70396f00, 0x5caff44d,
	 0xe96961b3, 0xad73f692, 0x8b841a2d, 0xf5838839,
	 0xec9c9d04, 0xcc2b5562, 0xf8ca2549, 0xa9c52ff8,
	 0x3b2fde68, 0x3d4dc7f0, 0xa57387d0, 0x051199ad},
	{0x5f0ce4fc, 0xd830fbb7, 0x90abeb8f, 0x96d9cdbb,
	 0x58f80a80, 0x0baaca36, 0x81a23623, 0x77127614,
	 0xaa8382cd, 0x0922fbca, 0xd84d37e1, 0x721297df,
	 0x160f3b3a, 0x10a1ecdc, 0x151c92f4, 0xc1fdcdab},
	{0x261c45cc, 0xfeddd2da, 0xfc3cb1c1, 0x6639641f,
	 0x2c011892, 0x7108bee2, 0x8545e0b9, 0x7dd36dab,
	 0x07d91950, 0x1520adcb, 0xf84aa939, 0x07d9bb2d,
	 0xdf1ed826, 0xaee3c814, 0x1dca1e81, 0xc8e9f486},
	{0x933d306a, 0xaab7103d, 0xa8be37be, 0x49612f3a,
	 0xb0cf28e5, 0xf9648902, 0x106d7c11, 0xf32e1813,
	 0x21af36ef, 0xe695e4c4, 0x7ee1831d, 0x2aeda467,
	 0x99d0c655, 0x3f0691ab, 0xcd68f7c1, 0xb469a20e},
	{0x8557aef0, 0x3eb0e373, 0x0853ac31, 0xe5bded62,
	 0x3eddb0dd, 0x6bbf1caf, 0x2119c3d9, 0xe1732350,
	 0x55456c75, 0xf6119375, 0x498dd1ad, 0x13f80916,
	 0xb97f9f5e, 0x921d9f4c, 0xabdee367, 0x1d6bb8bf},
	{0xd165a3be, 0xd8b41598, 0xa20e1809, 0xefd5c8ce,
	 0x18935c80, 0xdf1911f9, 0xc9e449eb, 0xb887a4d7,
	 0x4a324f6f, 0x533e8031, 0x1c21c074, 0xa95f1ea5,
	 0x765b320a, 0x839d7dfb, 0xc7d3aa93, 0xe534ae3d},
	{0xbe8592c8, 0x068457e6, 0x89b94fa3, 0xd522ad02,
	 0x7e7db0b7, 0x2c5b896f, 0x9f8ecb37, 0x05b983ff,
	 0x3fe9b25f, 0x34a6215b, 0x0592ba34, 0xd564f85a,
	 0x156c426d, 0x25ad5460, 0xe7b5e8b7, 0xa73285c6},
	{0x5ad8d838, 0x27b42d36, 0xcc806ad1, 0x157a058a,
	 0x7297735a, 0xffd6df8d, 0xff96f7a2, 0x155b27ea,
	 0x84708101, 0x979fd78b, 0x49797d0c, 0x0dc93e3c,
	 0x20287332, 0xed759f88, 0xe5068529, 0xb83aa781},
	{0xc38b302c, 0x57b54075, 0xac810692, 0xb0d493e7,
	 0x4adda486, 0x0665ce2e, 0xb2a9c003, 0xafacc4ce,
	 0x4d5e906d, 0xb3d52fab, 0xe6962c6b, 0x850f4dd1,
	 0x5021656c, 0x5df6c06b, 0x9255125b, 0x2363c478},
	{0x188b715c, 0xe8b884b0, 0x5e6d0b9a, 0x1f0051e1,
	 0xd2d35d4c, 0xbfeaecbe, 0xc84bb0ad, 0x67a232d6,
	 0x99001587, 0xbf4313e1, 0x74f64061, 0x2c1fc562,
	 0xb6fe8ca6, 0x5226a239, 0xf5198574, 0x61b51dca},
	{0x51dcecd3, 0xbadbe596, 0xebe3e84a, 0x772bfdfc,
	 0x03656ac5, 0xa7c36e91, 0x6cd32cf0, 0xc3f699dd,
	 0x7d5aba01, 0x51e38e82, 0x23103a98, 0x20298b9d,
	 0x19436510, 0x63ad7e6c, 0x8bc2b33f, 0x27079917},
	{0x8bd5be78, 0xf2403bfa, 0x780ebdb6, 0x94c53b64,
	 0x6241c2e2, 0x5bfb081e, 0x6799e88f, 0xc997b7d1,
	 0x466ac8b1, 0xbf5909da, 0x497ea39f, 0x402ffb48,
	 0xd7470c2d, 0x8510aba9, 0x6c52a1c9, 0x812ca967},
	{0x031f7ab4, 0xd32fe890, 0x36ae6de5, 0x083dcde4,
	 0x99a7f12f, 0xe44864a7, 0x02b75fff, 0xf25dda35,
	 0x7679ff4f, 0xed421e01, 0xd9c2cfa1, 0xd36b4e82,
	 0x5315d908, 0xc7ebcb2a, 0xb6f3e4c1, 0xf5bfbae9},
	{0x3f4a2a96, 0x64d8bd5a, 0x19acd70d, 0xf62fcdd9,
	 0x5de99cdf, 0x32f3b7cb, 0x2c020578, 0x4e9bafb8,
	 0x74919a08, 0xaba33e91, 0xa6bd2254, 0x2435a9b9,
	 0x47e2a1b4, 0xe837a28e, 0xe113f1b0, 0x7654bd79},
	{0x05537a6c, 0x77be1a5c, 0x4c7492c9, 0x9086bfb0,
	 0x257adc18, 0xf4787fc1, 0xe3fb6d53, 0x9525e589,
	 0x445a65bc, 0x833f7d08, 0x69cf1f7e, 0x9a6372e1,
	 0xceedb52e, 0x31032997, 0xd1c36828, 0x132772d6},
	{0x0a166972, 0x89beaf3b, 0x8d780fbc, 0x8aea5392,
	 0x58347a41, 0x1e381ec2, 0xcc6280c8, 0xee0863e1,
	 0x976e2dd2, 0x8c6ee6e2, 0xa0ca57cd, 0x95114a7d,
	 0x3c096704, 0xa941769d, 0x2de20c05, 0x0bf8f812},
	{0x22779d6c, 0x94e12e8f, 0x5ce40299, 0xea1b55b0,
	 0x9ebec05d, 0xe076cd2b, 0x8fef5648, 0x6a284c65,
	 0xa790b705, 0xf0b19997, 0x0d8ca8af, 0x17440419,
	 0xef4f702f, 0x33cbcbb1, 0x83d60f26, 0x48988397},
	{0x0fed7f53, 0xb5acbb67, 0xc031c73f, 0x5364d9ef,
	 0xa6dbd12d, 0x82174a6c, 0xccf8e7ab, 0xc473c036,
	 0xcff493d8, 0xad9afc3b, 0x316a24e8, 0x1842bea4,
	 0x4cc0c82e, 0x28ccd91e, 0xd7311b5d, 0x50a89860},
};

static const u8 use_base[63][32] = {
  {
    0x0e, 0x9e, 0xa1, 0x39, 0x06, 0x26, 0xc5, 0xe9, 0xed, 0x07, 0x49, 0x3b, 0x34, 0x7f, 0x1c, 0xa8,
    0xdf, 0x7b, 0xb7, 0xb8, 0x28, 0xbe, 0x8a, 0x70, 0x17, 0xe5, 0xc0, 0x44, 0x4a, 0x8e, 0x61, 0x3b,
  },
  {
    0x42, 0xe6, 0xe0, 0x6a, 0xb3, 0x08, 0x28, 0xaf, 0xfa, 0xb9, 0xb7, 0x32, 0x83, 0x5c, 0xef, 0x3d,
    0x90, 0x91, 0x64, 0x31, 0xe9, 0x3c, 0x92, 0xe6, 0xa3, 0xd4, 0x6a, 0xc6, 0x01, 0xa6, 0xeb, 0xe6,
  },
  {
    0x39, 0x7f, 0x6f, 0x81, 0xb4, 0x33, 0x4a, 0xde, 0x4f, 0x77, 0x28, 0x47, 0x08, 0xf9, 0x3a, 0x55,
    0x21, 0x57, 0x27, 0x59, 0xf5, 0x96, 0xad, 0xc1, 0x10, 0x33, 0xe0, 0xe2, 0xf8, 0xb6, 0x49, 0xbd,
  },
  {
    0xdf, 0x57, 0x60, 0x27, 0x95, 0x50, 0x3a, 0x8c, 0x34, 0x8b, 0xae, 0xc5, 0x69, 0x26, 0xca, 0x39,
    0x55, 0x98, 0xfb, 0x05, 0x3c, 0x1c, 0x8d, 0xf8, 0xb9, 0x99, 0x05, 0x40, 0xe5, 0x5e, 0x2f, 0xf6,
  },
  {
    0xc1, 0x6a, 0xea, 0xd6, 0x39, 0x56, 0x08, 0x89, 0x83, 0x4c, 0xef, 0xda, 0xb2, 0x69, 0x76, 0xe4,
    0x75, 0x3f, 0x39, 0x13, 0x96, 0xb5, 0x41, 0x84, 0x00, 0x64, 0x79, 0x47, 0xe4, 0xcb, 0xc3, 0xd0,
  },
  {
    0xf8, 0xb1, 0x19, 0x76, 0x51, 0x99, 0xd7, 0x45, 0x38, 0x40, 0xbf, 0x10, 0x4c, 0x89, 0x43, 0xa9,
    0x89, 0xe2, 0x85, 0x3f, 0xb4, 0xe8, 0xbf, 0x5e, 0xc2, 0xb4, 0x16, 0x6d, 0x1c, 0x61, 0xca, 0x40,
  },
  {
    0x1c, 0xdc, 0xa6, 0xdb, 0x71, 0x8b, 0xf9, 0xbb, 0xee, 0xc2, 0xa5, 0x66, 0xa4, 0xbc, 0xb6, 0x89,
    0x58, 0xb9, 0x6f, 0x57, 0x71, 0x57, 0x5c, 0xf0, 0xed, 0xcf, 0x2c, 0x2e, 0x1d, 0x34, 0xc3, 0x00,
  },
  {
    0x1d, 0x30, 0x03, 0xb9, 0x15, 0x8e, 0x47, 0x8c, 0xf2, 0x4e, 0x2d, 0xf1, 0xbf, 0x96, 0xa7, 0xa1,
    0x3f, 0x26, 0xc3, 0xc9, 0x08, 0x0b, 0xa8, 0xdd, 0x9b, 0xeb, 0xbc, 0x77, 0x1c, 0x10, 0x03, 0x77,
  },
  {
    0x50, 0x7e, 0x62, 0x26, 0xcb, 0x49, 0x7b, 0x1a, 0xd4, 0x54, 0xf1, 0x25, 0x3d, 0xa2, 0xe6, 0x8a,
    0xb3, 0x62, 0xf1, 0x7e, 0x03, 0xef, 0x1b, 0x27, 0x21, 0xcc, 0xfc, 0x72, 0x30, 0x0c, 0x69, 0xad,
  },
  {
    0x11, 0xf5, 0xb2, 0xfa, 0x2d, 0xbc, 0xa1, 0xd9, 0x74, 0x15, 0x59, 0xf2, 0xc6, 0x66, 0x4f, 0xde,
    0x84, 0x82, 0x4f, 0xe8, 0x33, 0xd5, 0xc5, 0xdd, 0xba, 0x0c, 0xc7, 0x51, 0x1f, 0x3c, 0x6d, 0x44,
  },
  {
    0xcf, 0xf5, 0x3b, 0xc1, 0xbd, 0x5f, 0x9c, 0xad, 0x57, 0xfb, 0xfc, 0xbe, 0x95, 0xa0, 0x48, 0x58,
    0x8a, 0x68, 0x97, 0x71, 0xf3, 0xc0, 0xd1, 0x31, 0x33, 0xb9, 0x3c, 0xe9, 0x4f, 0xbb, 0x8d, 0xeb,
  },
  {
    0x29, 0x0c, 0xa1, 0xc8, 0x04, 0xdc, 0xf9, 0x25, 0x85, 0x7e, 0xea, 0x6d, 0x75, 0x28, 0x69, 0x3f,
    0x3a, 0x83, 0xe4, 0x33, 0x31, 0x77, 0x57, 0x2e, 0xa9, 0xa8, 0x05, 0xfe, 0x19, 0xb7, 0xc4, 0xd1,
  },
  {
    0x6d, 0x5d, 0x3f, 0x4f, 0x8a, 0x6a, 0x77, 0x2d, 0xf7, 0x9f, 0x73, 0xab, 0x40, 0xd9, 0x89, 0x57,
    0x69, 0xd7, 0xc8, 0xc3, 0x69, 0x54, 0x93, 0x7c, 0x9f, 0x4a, 0xcc, 0xaf, 0xcc, 0x0e, 0xe0, 0xb8,
  },
  {
    0xb6, 0xd5, 0x36, 0x3f, 0x1c, 0x34, 0x54, 0x9b, 0xfc, 0xec, 0x5b, 0xb0, 0x26, 0xa6, 0xc0, 0x61,
    0x6d, 0x4c, 0x4f, 0x86, 0x2a, 0xbd, 0x34, 0x35, 0x52, 0x2c, 0x82, 0x01, 0x66, 0x0e, 0x80, 0x01,
  },
  {
    0x48, 0x39, 0x43, 0xb8, 0xf9, 0x2b, 0x25, 0xe8, 0xf7, 0xf0, 0x1a, 0xed, 0x33, 0x1e, 0x30, 0xba,
    0x15, 0x37, 0xeb, 0xae, 0x97, 0xa7, 0x36, 0xa4, 0xc7, 0x1f, 0x91, 0x01, 0x38, 0x80, 0x5a, 0x76,
  },
  {
    0x74, 0xbe, 0x15, 0x6b, 0x85, 0x28, 0xe4, 0xc4, 0x13, 0x68, 0x67, 0x03, 0x27, 0x7e, 0x32, 0x08,
    0x87, 0x23, 0xda, 0xf2, 0x47, 0xdd, 0xac, 0x2c, 0xc5, 0x7f, 0x06, 0xc8, 0x17, 0x4c, 0x6c, 0x81,
  },
  {
    0x0d, 0x9f, 0x68, 0xbb, 0xa6, 0x6c, 0x7d, 0x3f, 0x81, 0xcf, 0x9a, 0x52, 0x87, 0xce, 0x98, 0x25,
    0x40, 0x2b, 0x1b, 0xdf, 0xd3, 0x6b, 0x53, 0xed, 0x80, 0xd2, 0x3d, 0xca, 0xdf, 0x07, 0x4e, 0x6b,
  },
  {
    0xff, 0xf1, 0xd2, 0x1f, 0xbd, 0xd6, 0xa7, 0x3d, 0xb4, 0xc6, 0x88, 0x9d, 0x7b, 0x05, 0x04, 0x0b,
    0x4c, 0x6f, 0x11, 0x7f, 0x19, 0x18, 0x48, 0xf1, 0x26, 0xad, 0xd0, 0x60, 0xfa, 0x40, 0x35, 0xbb,
  },
  {
    0xae, 0xec, 0x0e, 0x2e, 0xfd, 0x46, 0xf0, 0x9c, 0x06, 0x1b, 0x62, 0xbf, 0xf0, 0x3e, 0xba, 0xdf,
    0xb2, 0xa2, 0x83, 0x83, 0xda, 0x04, 0x15, 0xec, 0x1e, 0x2e, 0x1a, 0x64, 0x08, 0x8e, 0xd3, 0x87,
  },
  {
    0x61, 0x14, 0x05, 0x0b, 0xdb, 0xf4, 0xf0, 0xa3, 0x41, 0x11, 0x7b, 0xd9, 0xa1, 0x40, 0x4f, 0x62,
    0x98, 0x37, 0xa0, 0x90, 0x3d, 0x78, 0x63, 0x24, 0xbc, 0x8e, 0x9e, 0x99, 0x2e, 0xc7, 0xb1, 0x6d,
  },
  {
    0x0f, 0xf1, 0x5f, 0xe4, 0x94, 0x3d, 0x24, 0x0d, 0xa2, 0xcf, 0xed, 0xbb, 0x55, 0x8e, 0xdb, 0x07,
    0x12, 0x05, 0x79, 0x82, 0xb1, 0x3a, 0x71, 0x76, 0xbb, 0x8b, 0xcb, 0xcc, 0x00, 0x40, 0x2e, 0xab,
  },
  {
    0x48, 0x59, 0xfa, 0x46, 0x15, 0x5e, 0xa2, 0x0d, 0xe8, 0x81, 0x69, 0xe6, 0x2f, 0x5f, 0x6d, 0xaf,
    0xad, 0xc7, 0x30, 0xd6, 0xec, 0x03, 0x1e, 0x19, 0xdd, 0x1d, 0x00, 0x94, 0x0b, 0x93, 0x5a, 0x28,
  },
  {
    0xfa, 0x64, 0x62, 0x57, 0x02, 0x7e, 0x37, 0xb8, 0x10, 0xa9, 0x4b, 0xe7, 0xbf, 0x03, 0xdc, 0x1c,
    0xe7, 0x21, 0x68, 0x60, 0x53, 0xec, 0xf0, 0xfc, 0xbf, 0xe5, 0x8e, 0xca, 0x77, 0xdb, 0xa5, 0xae,
  },
  {
    0xc1, 0xa9, 0x9f, 0xc2, 0x87, 0x11, 0xad, 0x1c, 0xc5, 0x56, 0x61, 0xc0, 0x20, 0x33, 0xc9, 0x85,
    0xf0, 0x81, 0x36, 0x18, 0xdb, 0xaa, 0x7e, 0x79, 0x36, 0x2d, 0xfc, 0x8f, 0x72, 0x3c, 0x4c, 0xa3,
  },
  {
    0xb4, 0xd3, 0x38, 0xed, 0xd3, 0x6c, 0x03, 0x26, 0x0e, 0x1c, 0x8a, 0xa8, 0x72, 0x17, 0xcb, 0xf7,
    0x87, 0xf3, 0x3f, 0x73, 0x5d, 0x12, 0xe8, 0x3b, 0x55, 0xb6, 0xcc, 0xc6, 0x85, 0xad, 0x9f, 0x9e,
  },
  {
    0xe9, 0x97, 0xde, 0x7f, 0xe0, 0x9a, 0xc1, 0xdc, 0x96, 0x4c, 0xc3, 0x0d, 0x2d, 0xd4, 0x98, 0x54,
    0x89, 0x1c, 0x57, 0x7d, 0x17, 0x96, 0xe9, 0x2f, 0x02, 0x73, 0x07, 0x5c, 0x8b, 0x44, 0xd7, 0x75,
  },
  {
    0xaf, 0xf2, 0x39, 0xc4, 0x23, 0xff, 0xd5, 0x85, 0xf3, 0x11, 0x44, 0x9e, 0xab, 0x59, 0x29, 0x33,
    0xe6, 0xc2, 0x1d, 0xba, 0xa8, 0x5b, 0x70, 0xc3, 0xc0, 0xf8, 0x56, 0x3b, 0x8e, 0x43, 0x4c, 0x4b,
  },
  {
    0x46, 0x93, 0xb5, 0x8a, 0x71, 0x67, 0xcb, 0x42, 0x6b, 0x1b, 0x43, 0x58, 0x8b, 0x18, 0xb9, 0xf3,
    0xdc, 0x91, 0x1c, 0x08, 0x83, 0xe3, 0x63, 0xfa, 0xf9, 0x99, 0x99, 0xcb, 0x05, 0x15, 0x7b, 0x85,
  },
  {
    0xcf, 0xc6, 0x3c, 0x01, 0xbd, 0xfb, 0x00, 0x8c, 0x8b, 0x07, 0x69, 0xac, 0x61, 0xdb, 0x30, 0xd5,
    0x7c, 0x71, 0x98, 0x69, 0x2e, 0x4a, 0x4a, 0x44, 0xe4, 0x72, 0x6f, 0xf2, 0x9d, 0x58, 0x02, 0x23,
  },
  {
    0x29, 0x10, 0xe1, 0xe5, 0x3f, 0xe6, 0x26, 0xaf, 0x30, 0x3c, 0xfe, 0x1f, 0x97, 0x21, 0xdd, 0x8c,
    0xbb, 0x90, 0xdb, 0x2a, 0xb5, 0xb4, 0x46, 0x43, 0x50, 0x0b, 0x6b, 0xa8, 0x8f, 0x55, 0xfb, 0xd2,
  },
  {
    0x89, 0x56, 0x19, 0xf9, 0x4a, 0xec, 0x38, 0x99, 0xaa, 0xcc, 0xc5, 0x15, 0xdf, 0x19, 0xee, 0x1a,
    0xc0, 0x94, 0xaf, 0x0f, 0x7b, 0xf4, 0x06, 0xf1, 0x70, 0xa3, 0x79, 0x06, 0xba, 0x4e, 0x09, 0xa6,
  },
  {
    0x53, 0x3a, 0x35, 0x98, 0xa9, 0xcb, 0x2c, 0x72, 0x73, 0xb2, 0xb0, 0x63, 0x38, 0xfc, 0xa3, 0xa5,
    0xa3, 0xf1, 0x4d, 0x04, 0x2f, 0x1b, 0x83, 0xbd, 0xed, 0x20, 0x8e, 0xa5, 0x1e, 0x9d, 0xd6, 0x69,
  },
  {
    0x78, 0x44, 0xe3, 0x22, 0xa4, 0x7c, 0x53, 0xef, 0x60, 0x8e, 0x39, 0x95, 0x7d, 0x9d, 0x3d, 0x0b,
    0x4a, 0x4f, 0xf4, 0x73, 0xf8, 0xfe, 0xe7, 0x65, 0x86, 0x72, 0x13, 0x0b, 0x4e, 0x8f, 0x4d, 0x7b,
  },
  {
    0x46, 0xba, 0xd2, 0x82, 0x46, 0x18, 0x6e, 0x46, 0x96, 0x05, 0x1d, 0xfb, 0xf6, 0xde, 0xba, 0xb5,
    0x6b, 0x73, 0x7a, 0xd5, 0x76, 0x11, 0xb7, 0x7c, 0x0d, 0x61, 0xba, 0xf9, 0x05, 0x12, 0x2b, 0x4e,
  },
  {
    0x41, 0x08, 0x8b, 0x63, 0x10, 0xeb, 0x85, 0x10, 0xf3, 0x05, 0x84, 0xc0, 0x81, 0x1f, 0x7f, 0xd3,
    0x9d, 0x01, 0xdc, 0x32, 0xd0, 0xe2, 0xd1, 0xd1, 0x41, 0x8a, 0xa0, 0xf2, 0x64, 0xda, 0x8b, 0x0e,
  },
  {
    0x99, 0xf1, 0xf2, 0x88, 0xe8, 0x72, 0x8b, 0x40, 0x17, 0xcc, 0xa7, 0x4c, 0x7d, 0xf1, 0xc4, 0x3f,
    0xbf, 0xf8, 0xbe, 0xc9, 0xce, 0xce, 0x2b, 0xe9, 0x4d, 0x5b, 0xd1, 0xef, 0x76, 0xae, 0x3b, 0xbb,
  },
  {
    0x64, 0x69, 0x47, 0x03, 0xe9, 0x3b, 0xc2, 0x2d, 0x2d, 0x1a, 0xdd, 0xa4, 0xac, 0xb6, 0x6e, 0x7a,
    0x41, 0x7d, 0x82, 0xed, 0x54, 0xf7, 0x05, 0xd8, 0xae, 0x07, 0x6c, 0x1c, 0xf6, 0x51, 0xa1, 0xc0,
  },
  {
    0x84, 0xaf, 0xe8, 0x59, 0x0c, 0x14, 0x24, 0xec, 0xa0, 0xd2, 0xf3, 0x8f, 0x2f, 0x22, 0xe4, 0x52,
    0xf8, 0xa7, 0x39, 0x74, 0x7f, 0x80, 0x23, 0x3f, 0x30, 0xe3, 0xcb, 0x26, 0x12, 0x5c, 0xa7, 0x93,
  },
  {
    0x48, 0xc8, 0x41, 0x42, 0xc5, 0xe7, 0x4d, 0x91, 0x54, 0xa6, 0x5b, 0xba, 0x46, 0x89, 0xd5, 0x42,
    0x46, 0xbc, 0xf2, 0x67, 0x4a, 0xf9, 0x88, 0xe9, 0x02, 0xa5, 0xc2, 0x38, 0x9d, 0x6a, 0x75, 0xcd,
  },
  {
    0xab, 0x9b, 0x2c, 0x09, 0xda, 0xaa, 0xe9, 0xe2, 0xd7, 0xf1, 0xa4, 0x86, 0x41, 0x14, 0xcb, 0x4e,
    0x2b, 0xd1, 0x5a, 0x9a, 0x46, 0x47, 0x90, 0xb2, 0x63, 0x16, 0xcb, 0x60, 0x1c, 0x12, 0xe3, 0x2b,
  },
  {
    0x54, 0x21, 0xc0, 0xbc, 0xb8, 0x29, 0xce, 0xa4, 0xf2, 0x38, 0xb4, 0x0d, 0x7d, 0xfa, 0xd4, 0x3e,
    0x28, 0xf4, 0xc4, 0xf4, 0x4a, 0x9f, 0x11, 0xf2, 0xe2, 0x31, 0xa3, 0x72, 0x16, 0xbb, 0xd9, 0x05,
  },
  {
    0xdc, 0x6e, 0xbe, 0x64, 0xa2, 0xb2, 0x64, 0x46, 0x00, 0xee, 0xd2, 0xa5, 0x81, 0x86, 0x44, 0xa4,
    0x5c, 0xc4, 0xba, 0xc4, 0xa2, 0x44, 0x36, 0x77, 0xb2, 0xec, 0x0d, 0xbe, 0x8f, 0xc0, 0x80, 0x6f,
  },
  {
    0x51, 0x51, 0xb2, 0x50, 0x11, 0x0b, 0x60, 0xb8, 0x8e, 0xc2, 0xf7, 0xa8, 0xb4, 0xd2, 0x48, 0xc3,
    0x51, 0x43, 0x52, 0xeb, 0x37, 0xac, 0xd0, 0xf7, 0x61, 0xa1, 0xe9, 0xe3, 0xa7, 0xdf, 0x26, 0xa9,
  },
  {
    0x10, 0xd9, 0xf2, 0xfe, 0x71, 0x8e, 0x49, 0x2c, 0x64, 0x53, 0xb0, 0x9e, 0x7a, 0xcc, 0x86, 0xab,
    0x06, 0xd7, 0xc7, 0x13, 0xd1, 0xcb, 0x21, 0x42, 0x97, 0x29, 0x5d, 0xff, 0xaa, 0xec, 0x52, 0x40,
  },
  {
    0x7b, 0x35, 0x93, 0xb9, 0xca, 0xbb, 0x7e, 0x09, 0x8f, 0x34, 0x32, 0x02, 0xe7, 0x0c, 0xcf, 0xd1,
    0x6c, 0x2d, 0x11, 0xcd, 0xa5, 0x3b, 0xba, 0x14, 0x47, 0xc5, 0x2c, 0xb8, 0xf6, 0xfb, 0x9d, 0x77,
  },
  {
    0x45, 0xce, 0x12, 0x8e, 0xa2, 0x4e, 0x56, 0x58, 0xa7, 0xcf, 0x26, 0x4e, 0x32, 0x21, 0xe0, 0x2b,
    0xed, 0x8d, 0xe2, 0xd9, 0x51, 0x32, 0x9b, 0xdc, 0x7b, 0x0e, 0x14, 0x0a, 0xdb, 0x63, 0x6b, 0x42,
  },
  {
    0x9d, 0x49, 0x72, 0xea, 0x89, 0xc7, 0xa2, 0xfd, 0x9a, 0x55, 0xd7, 0x05, 0x16, 0xeb, 0xf7, 0x49,
    0xb6, 0xcf, 0x56, 0xf7, 0x2b, 0xef, 0x6d, 0xbe, 0xdd, 0x0e, 0x90, 0x01, 0xaf, 0x1b, 0xbb, 0xaa,
  },
  {
    0x2c, 0xb7, 0x26, 0x43, 0x02, 0xc5, 0x7b, 0xc6, 0x71, 0x1f, 0xf2, 0x28, 0xb4, 0xea, 0x5f, 0x02,
    0xc6, 0xeb, 0xb4, 0xf7, 0x6f, 0x01, 0x7f, 0xfe, 0x3a, 0xb0, 0xe3, 0xf3, 0x31, 0xd3, 0xcb, 0x0f,
  },
  {
    0x75, 0x54, 0x90, 0xec, 0xed, 0xcc, 0xbc, 0x5c, 0x9b, 0x44, 0x30, 0x57, 0x57, 0xe0, 0xec, 0x58,
    0x20, 0x54, 0x20, 0xb0, 0x92, 0x3a, 0x06, 0x9f, 0x69, 0xcb, 0x88, 0xee, 0x52, 0x6e, 0x4c, 0xf6,
  },
  {
    0x2a, 0x08, 0xd8, 0xdd, 0x2e, 0x07, 0x54, 0x0b, 0x37, 0xc6, 0x09, 0x26, 0x98, 0xf7, 0x45, 0xf6,
    0x05, 0x4f, 0x35, 0xe6, 0xb0, 0x44, 0xff, 0x62, 0x89, 0x47, 0x69, 0x30, 0xea, 0x3b, 0x7b, 0x81,
  },
  {
    0x0f, 0x7f, 0x34, 0xbf, 0xf9, 0xce, 0xe7, 0x4c, 0xe1, 0x7a, 0x24, 0x74, 0xeb, 0x8b, 0xb0, 0x65,
    0x18, 0x19, 0xaf, 0x44, 0x45, 0x5e, 0xd9, 0xa4, 0xf0, 0xd8, 0xe8, 0x09, 0x22, 0x58, 0x4e, 0x4d,
  },
  {
    0x48, 0x41, 0x7a, 0xd2, 0x26, 0xda, 0x39, 0xb2, 0xba, 0x03, 0x17, 0xe9, 0x80, 0x8e, 0x53, 0x4c,
    0xac, 0x64, 0x6b, 0xa7, 0x5f, 0xed, 0x64, 0x60, 0xb7, 0x5e, 0x7a, 0x68, 0x1a, 0x8a, 0xda, 0x2b,
  },
  {
    0x52, 0x01, 0x25, 0xb0, 0x59, 0xcf, 0x61, 0x30, 0x52, 0xe7, 0x77, 0x66, 0xc9, 0x35, 0xac, 0xfe,
    0xc0, 0xa2, 0x18, 0x58, 0xf1, 0xc1, 0x8f, 0x28, 0x72, 0x2f, 0xdc, 0x36, 0x10, 0x5b, 0xd9, 0x6f,
  },
  {
    0x05, 0xbf, 0x47, 0x32, 0x0e, 0xa7, 0xc6, 0xd6, 0x13, 0xa1, 0x72, 0x38, 0x8c, 0x1a, 0xbc, 0x6d,
    0x7c, 0xd8, 0x34, 0xac, 0x69, 0x5b, 0x43, 0xc4, 0x00, 0xf8, 0xf2, 0xa7, 0xaf, 0x9f, 0xb0, 0xde,
  },
  {
    0x54, 0x67, 0xce, 0xf2, 0xfc, 0x91, 0xd2, 0x4d, 0x73, 0xc6, 0xc9, 0xc3, 0xfe, 0xcf, 0x72, 0xa0,
    0xc7, 0x43, 0xff, 0x87, 0x4b, 0xe3, 0x7f, 0xba, 0xd4, 0xa2, 0xa3, 0x14, 0x8f, 0xa0, 0x39, 0x91,
  },
  {
    0xbd, 0x24, 0x35, 0xb5, 0x0e, 0x7a, 0x13, 0xb3, 0x92, 0x83, 0xaa, 0xbd, 0x0c, 0x22, 0x93, 0xbb,
    0x2a, 0xe7, 0x7a, 0x56, 0x2d, 0xae, 0x41, 0x62, 0x52, 0xb2, 0xe9, 0xbd, 0x29, 0x05, 0x51, 0x95,
  },
  {
    0x97, 0x8f, 0x21, 0x82, 0x72, 0x4f, 0x65, 0xc8, 0xfc, 0x2e, 0x5e, 0x8a, 0x1a, 0xce, 0x34, 0x39,
    0x12, 0xe6, 0x9b, 0xc3, 0xab, 0x51, 0xa9, 0x40, 0xf7, 0xbe, 0x94, 0xd0, 0x66, 0xda, 0xa5, 0x39,
  },
  {
    0x5a, 0x48, 0x43, 0x9a, 0x8e, 0x22, 0x85, 0x9b, 0x28, 0xc9, 0x63, 0xa2, 0x57, 0xa6, 0xe2, 0x16,
    0x64, 0xec, 0x3c, 0x59, 0x13, 0xc4, 0x7b, 0x51, 0xea, 0xfe, 0x2e, 0x70, 0xbd, 0xd9, 0x77, 0x85,
  },
  {
    0x2b, 0x74, 0xb6, 0x95, 0x18, 0x94, 0x54, 0x6d, 0xae, 0xdd, 0xe9, 0xb2, 0xf9, 0xbd, 0xce, 0x27,
    0xa9, 0x87, 0x42, 0x13, 0x22, 0x29, 0x87, 0x7a, 0x04, 0xe3, 0xbe, 0x2f, 0x9c, 0x18, 0xbb, 0x13,
  },
  {
    0x80, 0x95, 0x43, 0xaa, 0x19, 0x90, 0x03, 0x4f, 0x47, 0xbf, 0xf5, 0x8e, 0x2d, 0x55, 0x23, 0xb7,
    0x7b, 0x5d, 0xaa, 0x34, 0x37, 0xb2, 0x70, 0x86, 0x5e, 0xc4, 0x94, 0xf3, 0x61, 0xfd, 0x87, 0x65,
  },
  {
    0xd4, 0xbc, 0x03, 0x65, 0xb0, 0xc5, 0x44, 0x81, 0x7b, 0x06, 0x94, 0x79, 0xca, 0x1f, 0xe2, 0x28,
    0x53, 0xc8, 0xa7, 0x10, 0x13, 0x77, 0xb7, 0x5c, 0x9a, 0x34, 0x1e, 0xd5, 0x78, 0xb1, 0x21, 0x61,
  },
  {
    0x90, 0x0e, 0x7f, 0xa3, 0x24, 0x18, 0x12, 0xbf, 0x45, 0xd2, 0x52, 0xa3, 0x99, 0x74, 0x89, 0xd2,
    0x12, 0x8d, 0x32, 0x3c, 0xd0, 0x28, 0x54, 0x98, 0x6c, 0x9e, 0xdd, 0xc0, 0xd5, 0xf1, 0x8a, 0xb1,
  },
  {
    0x82, 0xad, 0x7a, 0x5c, 0x4d, 0x81, 0x54, 0x41, 0x79, 0x42, 0x54, 0x5c, 0x49, 0x41, 0xed, 0x49,
    0xc7, 0x06, 0x61, 0xbb, 0x89, 0x2b, 0x90, 0x04, 0x1f, 0x8c, 0x31, 0x3b, 0x39, 0x4f, 0xf8, 0x33,
  },
};
static const u8 invert[63][32] = {
  {
    0x95, 0xb2, 0xa8, 0xe3, 0xac, 0xcf, 0x27, 0x3e, 0x1c, 0xa3, 0xcf, 0x7a, 0x20, 0xb4, 0x52, 0x83,
    0x0e, 0x21, 0x2d, 0xfe, 0x6f, 0x2e, 0x38, 0x13, 0x01, 0x2e, 0xa0, 0x58, 0x58, 0x6d, 0x4a, 0x6f,
  },
  {
    0x63, 0x26, 0x5c, 0xd2, 0x9a, 0xc6, 0x8c, 0x5d, 0xc2, 0x0d, 0xba, 0x4f, 0x79, 0x88, 0xd1, 0x15,
    0x64, 0x55, 0x90, 0x7b, 0x76, 0x2d, 0x60, 0x04, 0x92, 0x77, 0x18, 0xd0, 0xba, 0x7f, 0xee, 0x3a,
  },
  {
    0x57, 0xc1, 0x0b, 0x23, 0x06, 0x57, 0x0c, 0xde, 0xa1, 0xa5, 0x8d, 0xc6, 0x8e, 0xbd, 0x9e, 0x09,
    0xe5, 0xed, 0xe3, 0xfb, 0xb1, 0xa0, 0xda, 0x73, 0xfc, 0x3e, 0x5e, 0x6d, 0x38, 0x36, 0x26, 0xec,
  },
  {
    0x8e, 0xe5, 0x30, 0x36, 0x9e, 0x30, 0x82, 0x02, 0xf6, 0x7c, 0x06, 0x71, 0xbb, 0x6e, 0x09, 0x68,
    0x16, 0xca, 0x10, 0x32, 0x90, 0xcc, 0x7a, 0x99, 0x18, 0x70, 0xe6, 0xe7, 0x3a, 0x78, 0x86, 0xe6,
  },
  {
    0x18, 0x98, 0x14, 0xa7, 0xb7, 0x1f, 0x24, 0xed, 0xd0, 0xfc, 0x71, 0xa0, 0x7e, 0xef, 0xdd, 0xe2,
    0xa2, 0xf8, 0x2a, 0xc2, 0x5d, 0x94, 0x03, 0x13, 0x29, 0x39, 0x86, 0xed, 0x08, 0x99, 0x83, 0xab,
  },
  {
    0xcd, 0x22, 0xa0, 0xbc, 0xea, 0xe7, 0xde, 0xca, 0x0c, 0x72, 0xbd, 0xf7, 0x40, 0x46, 0x92, 0xc5,
    0xa4, 0xf3, 0x48, 0x9a, 0x8f, 0x52, 0xab, 0x19, 0x07, 0x98, 0xae, 0x9b, 0xe7, 0xfc, 0xbd, 0x05,
  },
  {
    0xd2, 0xce, 0x28, 0x79, 0x3f, 0xdd, 0xa1, 0x1c, 0x21, 0xe4, 0xeb, 0x54, 0x85, 0x5c, 0x9d, 0x64,
    0xd5, 0x5b, 0xb6, 0x06, 0x43, 0xcc, 0x80, 0x8b, 0xe3, 0xdb, 0x26, 0xf5, 0x7e, 0x5f, 0x81, 0x9d,
  },
  {
    0x54, 0x42, 0xe9, 0x30, 0xd2, 0x2c, 0xba, 0x16, 0xa7, 0x99, 0x28, 0xe7, 0x54, 0x61, 0xee, 0x17,
    0xf0, 0x70, 0x34, 0xe2, 0xe7, 0x66, 0x16, 0x00, 0x95, 0x7b, 0xbd, 0xd8, 0x07, 0xab, 0xa9, 0x5b,
  },
  {
    0xe7, 0x58, 0x21, 0x24, 0x0e, 0x32, 0xbd, 0x6b, 0xcb, 0xa6, 0xd9, 0x91, 0xd7, 0xfd, 0xe4, 0x4c,
    0x58, 0xd6, 0x06, 0x11, 0x02, 0x90, 0xe5, 0x1d, 0x91, 0x2f, 0x0f, 0x43, 0xe3, 0xc7, 0x66, 0xd8,
  },
  {
    0x45, 0x65, 0x5e, 0x17, 0xe1, 0x00, 0xfd, 0x42, 0x30, 0x25, 0x0e, 0xa5, 0x26, 0x8a, 0x17, 0xfe,
    0xd0, 0xa2, 0xff, 0x7a, 0x09, 0xd3, 0x5a, 0xb4, 0x71, 0x84, 0x29, 0x03, 0x71, 0x70, 0x9b, 0x6e,
  },
  {
    0xc7, 0x2d, 0xe6, 0xef, 0xba, 0x0b, 0x97, 0x9a, 0x91, 0xf2, 0xda, 0x26, 0x62, 0xe5, 0xbe, 0x5d,
    0xc5, 0x5d, 0x71, 0xc1, 0xb7, 0x3f, 0xb3, 0xb8, 0x74, 0xd0, 0x0c, 0x03, 0x74, 0xc0, 0x0c, 0xe4,
  },
  {
    0x56, 0x38, 0x1e, 0x31, 0xca, 0x3b, 0xb5, 0xc4, 0xff, 0x5a, 0x9e, 0x86, 0xfe, 0x98, 0x0c, 0x27,
    0x23, 0x2c, 0xa0, 0x76, 0x6f, 0xae, 0xf3, 0xde, 0x71, 0x40, 0x0c, 0xdc, 0x41, 0xf9, 0x89, 0x99,
  },
  {
    0x2c, 0x27, 0xed, 0x69, 0x50, 0x53, 0xc5, 0x97, 0xf4, 0x88, 0x9a, 0x2b, 0xce, 0x8a, 0xc5, 0xfb,
    0x0d, 0xbc, 0x6f, 0x9c, 0x84, 0x30, 0xf3, 0xcb, 0xc1, 0x30, 0xa4, 0xb5, 0x46, 0xd4, 0xcb, 0xea,
  },
  {
    0xb7, 0xf0, 0x86, 0x66, 0xd3, 0x55, 0x64, 0xc9, 0x1b, 0x9b, 0x3d, 0x79, 0x13, 0x0a, 0x3e, 0xa1,
    0xcf, 0x54, 0x17, 0x77, 0xeb, 0x32, 0x1c, 0x47, 0x7d, 0xf0, 0xb4, 0x11, 0x3d, 0xd7, 0xef, 0x04,
  },
  {
    0xf7, 0x7e, 0x71, 0xb6, 0x5e, 0xed, 0xf3, 0xfb, 0x56, 0x82, 0x22, 0x61, 0x29, 0xa2, 0x5d, 0xc6,
    0xcd, 0x03, 0x47, 0xc7, 0xcc, 0xe4, 0xf2, 0xa4, 0x3f, 0xed, 0x36, 0xae, 0xa7, 0x30, 0x84, 0x22,
  },
  {
    0x13, 0x70, 0xe7, 0x97, 0x14, 0xfa, 0xa9, 0xb7, 0xd5, 0xa1, 0xa4, 0xfd, 0xe8, 0x0c, 0x92, 0xcf,
    0xc4, 0xdc, 0x5d, 0xb9, 0xa4, 0xa2, 0x16, 0xf8, 0x67, 0xdc, 0x12, 0x47, 0xb7, 0x75, 0xfd, 0x3c,
  },
  {
    0x29, 0xaa, 0xdd, 0xb5, 0xdc, 0x7f, 0xce, 0xad, 0x02, 0x65, 0x27, 0x5e, 0xa5, 0x5d, 0x23, 0x0f,
    0xa7, 0x51, 0x4d, 0xf2, 0x7d, 0x2a, 0x31, 0xbf, 0x32, 0x3b, 0x80, 0xe3, 0xda, 0x56, 0xdb, 0xfc,
  },
  {
    0x70, 0xd0, 0x50, 0x6d, 0xf2, 0xb3, 0x6f, 0xc1, 0x9a, 0x98, 0x02, 0x87, 0xb5, 0x31, 0x3d, 0x19,
    0xaa, 0xf4, 0xd2, 0xd4, 0x48, 0xb1, 0x08, 0x06, 0x98, 0x39, 0x00, 0x06, 0x20, 0xe5, 0x0c, 0xe1,
  },
  {
    0xe6, 0xaf, 0x94, 0xa0, 0xdf, 0xc3, 0x6b, 0xb4, 0xcf, 0x78, 0xc0, 0xe8, 0x56, 0xdc, 0xac, 0xbb,
    0x5e, 0x9e, 0xda, 0x90, 0x1e, 0x7f, 0x44, 0x06, 0xe0, 0x00, 0x6a, 0xd9, 0xd1, 0xf9, 0x56, 0xac,
  },
  {
    0x15, 0xa2, 0x90, 0x13, 0x4f, 0xa0, 0x9d, 0x0d, 0x9c, 0xf8, 0xc9, 0x20, 0x1c, 0x8e, 0x68, 0xcb,
    0x1f, 0x75, 0xb3, 0xb2, 0x14, 0xff, 0x19, 0x20, 0x5f, 0x30, 0xb1, 0x05, 0x36, 0x7c, 0xa2, 0xed,
  },
  {
    0x9a, 0xb2, 0xf5, 0xfd, 0x04, 0x3e, 0x6b, 0x4a, 0x1d, 0x3a, 0x63, 0x96, 0x00, 0xad, 0x6c, 0x7c,
    0x4f, 0xaf, 0x4d, 0xb5, 0x03, 0x4a, 0xf7, 0x28, 0x7f, 0x1f, 0x38, 0xad, 0xfd, 0xc7, 0x4b, 0x7f,
  },
  {
    0xf4, 0x5a, 0x9f, 0xf6, 0xd0, 0x1a, 0x23, 0x76, 0xee, 0x15, 0x10, 0x2c, 0x30, 0xbd, 0x45, 0xfc,
    0x65, 0x60, 0x20, 0xc5, 0x9b, 0xb4, 0x42, 0x83, 0xe9, 0x03, 0xd5, 0xec, 0xba, 0xb2, 0x3b, 0xb8,
  },
  {
    0xf4, 0x1b, 0xc1, 0x73, 0x1a, 0x6c, 0x88, 0xfd, 0xc2, 0xfb, 0xe8, 0x7e, 0xcb, 0x8a, 0x0e, 0x0e,
    0x6a, 0x13, 0x54, 0xb0, 0x7b, 0xb8, 0x68, 0x90, 0x21, 0x38, 0x4e, 0x1f, 0x86, 0x51, 0x14, 0x2c,
  },
  {
    0x6c, 0xd3, 0xc3, 0x8f, 0x06, 0x45, 0xec, 0x65, 0x87, 0x02, 0x3d, 0x89, 0x61, 0xde, 0x80, 0x42,
    0xf6, 0xe0, 0x8d, 0x91, 0xf0, 0x3a, 0x7a, 0x66, 0xba, 0x1c, 0xc7, 0xb6, 0x3d, 0xc4, 0x7f, 0x91,
  },
  {
    0x53, 0xf6, 0x90, 0x34, 0x88, 0x3e, 0xb7, 0xef, 0x56, 0x39, 0x6e, 0x1f, 0x48, 0x14, 0xe4, 0x09,
    0xc6, 0xea, 0xc4, 0xd9, 0xed, 0x2e, 0x2e, 0x33, 0x03, 0x00, 0xb9, 0xac, 0x22, 0x65, 0xe9, 0x1b,
  },
  {
    0x55, 0x78, 0x89, 0x36, 0xa0, 0x07, 0xa6, 0x99, 0xbf, 0x7c, 0xb5, 0xbd, 0xb6, 0x1e, 0xc3, 0x58,
    0xb3, 0x0f, 0x78, 0x64, 0x74, 0x77, 0x00, 0x50, 0x2e, 0x4c, 0x6a, 0xa1, 0xe8, 0x93, 0x89, 0x5d,
  },
  {
    0x09, 0xf8, 0xdd, 0xe0, 0x42, 0xa4, 0x2e, 0x9d, 0xff, 0x0e, 0x70, 0x73, 0x9c, 0x87, 0xa0, 0x81,
    0x4d, 0xb1, 0xc3, 0xf3, 0xff, 0x96, 0x3b, 0x2a, 0xdf, 0x6d, 0x97, 0xba, 0x06, 0xa7, 0x7e, 0x0a,
  },
  {
    0x1f, 0x46, 0xb4, 0x72, 0x14, 0x5b, 0x85, 0x01, 0x83, 0xcc, 0x24, 0x17, 0xc2, 0x07, 0xda, 0x60,
    0x6c, 0xab, 0xfa, 0xe5, 0xd9, 0xb4, 0xf0, 0x3f, 0xca, 0xf1, 0x30, 0x8d, 0xd2, 0x4e, 0xe3, 0xb4,
  },
  {
    0x4f, 0xb3, 0x0d, 0x98, 0x38, 0x70, 0x28, 0xa2, 0xca, 0x5d, 0x2c, 0xdf, 0x1f, 0xce, 0xff, 0xcc,
    0x75, 0x49, 0xa0, 0xef, 0x54, 0xd9, 0x32, 0x1b, 0x17, 0xb6, 0x7e, 0x7a, 0xa6, 0x5f, 0x7a, 0xff,
  },
  {
    0x81, 0x6b, 0x06, 0x73, 0x5b, 0x32, 0x0d, 0x37, 0xb4, 0x50, 0x63, 0x52, 0x25, 0x72, 0x5c, 0xf5,
    0x5d, 0x58, 0xa6, 0xbf, 0x08, 0xcc, 0x1d, 0x70, 0x2d, 0x12, 0x5d, 0xd7, 0xbd, 0xca, 0xe7, 0x10,
  },
  {
    0x8f, 0xfc, 0x57, 0x17, 0xce, 0x47, 0x10, 0x79, 0xae, 0x66, 0xa5, 0xcc, 0x98, 0x0b, 0x77, 0xe8,
    0xa2, 0x6e, 0xc1, 0x0d, 0x03, 0xe3, 0x5b, 0xed, 0x38, 0x0e, 0x31, 0x2d, 0x19, 0x4d, 0xd6, 0x2a,
  },
  {
    0xc6, 0x9d, 0x2d, 0x0b, 0xad, 0x6d, 0x0c, 0x61, 0x2d, 0x62, 0xe4, 0xce, 0x73, 0x47, 0x72, 0x20,
    0x0c, 0x8e, 0x8f, 0xe9, 0xe7, 0x67, 0x66, 0x2e, 0x17, 0x54, 0xec, 0x15, 0x3e, 0x1b, 0xf3, 0x04,
  },
  {
    0xf4, 0xee, 0x03, 0x30, 0x2e, 0x1e, 0xa4, 0xb1, 0x86, 0x6d, 0xc3, 0x54, 0xf3, 0xc5, 0x61, 0xa6,
    0xb9, 0x28, 0x29, 0x11, 0x91, 0xcb, 0xbd, 0xc9, 0x77, 0x62, 0x09, 0x8c, 0xa4, 0x40, 0x84, 0x97,
  },
  {
    0xff, 0x98, 0x9b, 0xbc, 0xc2, 0xf0, 0xf8, 0x7f, 0x5c, 0x86, 0x74, 0x33, 0xee, 0x42, 0x6e, 0xab,
    0xd4, 0xd2, 0x1a, 0x0d, 0x41, 0x2d, 0xac, 0xa1, 0x3e, 0x56, 0xed, 0x4b, 0x27, 0x5a, 0x65, 0xe4,
  },
  {
    0x2b, 0xb1, 0xe3, 0x64, 0xaa, 0x32, 0x17, 0x57, 0x7c, 0x67, 0xb8, 0x6b, 0x00, 0x53, 0xbe, 0x3e,
    0xec, 0xd1, 0x1b, 0xc4, 0xc3, 0x8d, 0xe6, 0x19, 0xe8, 0x3a, 0x25, 0x98, 0x4e, 0xe9, 0xd4, 0x60,
  },
  {
    0xa6, 0x2e, 0xb3, 0xc8, 0xcd, 0xc9, 0xc2, 0x8e, 0xe1, 0xf0, 0x8f, 0x96, 0x8e, 0xc6, 0x37, 0x11,
    0xbc, 0x6c, 0x0c, 0xf6, 0xb6, 0x83, 0x38, 0x96, 0x7a, 0x74, 0x5a, 0xa7, 0xe1, 0x11, 0x8d, 0x8b,
  },
  {
    0x90, 0xf2, 0x4d, 0xbd, 0x83, 0x39, 0xe6, 0x54, 0xf6, 0x75, 0xf6, 0x2c, 0x28, 0x3d, 0xd1, 0xcf,
    0xe1, 0xfb, 0x9f, 0x97, 0x19, 0xca, 0x4d, 0x2c, 0x38, 0x3d, 0x36, 0xed, 0x19, 0xe9, 0x4a, 0x0b,
  },
  {
    0x1a, 0x61, 0xb8, 0x19, 0x59, 0x16, 0x74, 0xec, 0xdb, 0x7b, 0xeb, 0xd6, 0xae, 0xcd, 0xe9, 0x55,
    0xdb, 0x45, 0xdc, 0xf2, 0x35, 0x84, 0xe9, 0xe6, 0x17, 0x48, 0xac, 0x38, 0x05, 0x21, 0x2c, 0x8e,
  },
  {
    0x41, 0xac, 0x17, 0x42, 0xcc, 0x17, 0x10, 0x02, 0x07, 0x7e, 0xfc, 0x4d, 0x77, 0x06, 0x70, 0xcb,
    0x40, 0x8b, 0x47, 0x47, 0x07, 0x29, 0x82, 0xca, 0x93, 0x69, 0x2f, 0x3a, 0x64, 0xc6, 0xcb, 0x23,
  },
  {
    0xa2, 0xcb, 0x2d, 0x02, 0x5d, 0x30, 0x9f, 0x32, 0xf5, 0xc5, 0x13, 0xff, 0xfc, 0xe2, 0xfb, 0x26,
    0x3b, 0x3b, 0xaf, 0xa4, 0x37, 0x6d, 0x45, 0xbf, 0xdb, 0xb9, 0xee, 0xec, 0x92, 0xa5, 0x1d, 0x0d,
  },
  {
    0xa4, 0xef, 0x08, 0xb7, 0xb4, 0x68, 0x74, 0x93, 0xb2, 0xda, 0xba, 0xe9, 0x05, 0xf5, 0x09, 0xb6,
    0x53, 0xdd, 0x17, 0x60, 0xbb, 0x1e, 0xb0, 0x71, 0xd8, 0x47, 0x85, 0x02, 0x13, 0xbe, 0xa2, 0x67,
  },
  {
    0x31, 0x50, 0x90, 0xb0, 0x83, 0x4a, 0xcf, 0x3f, 0xbe, 0x88, 0x90, 0x4b, 0xe1, 0x9f, 0xe6, 0xd0,
    0xfd, 0x01, 0x8e, 0xfc, 0xc0, 0x8c, 0x2f, 0x9b, 0x48, 0x70, 0x9d, 0x4e, 0x22, 0x21, 0x07, 0x09,
  },
  {
    0x15, 0x9f, 0x37, 0x45, 0x52, 0x99, 0x6e, 0xe9, 0x1a, 0x25, 0x56, 0x0b, 0x19, 0xf1, 0xca, 0x9f,
    0x29, 0xe5, 0x23, 0xa6, 0x0b, 0x94, 0x0a, 0xe3, 0x74, 0xaa, 0xd5, 0x35, 0xaf, 0x6e, 0xb2, 0x24,
  },
  {
    0x68, 0xab, 0xa6, 0x8b, 0x5f, 0xc7, 0x93, 0x1a, 0x06, 0x51, 0x2c, 0x3b, 0xad, 0x44, 0x6b, 0x69,
    0x1a, 0x1d, 0x41, 0xca, 0x8e, 0x59, 0x2c, 0x83, 0x71, 0x48, 0x8c, 0xaf, 0x50, 0x85, 0x00, 0xf3,
  },
  {
    0xe2, 0xa6, 0x38, 0x93, 0xca, 0xe3, 0xd0, 0x36, 0xf4, 0xe9, 0x53, 0xfb, 0xa0, 0xd0, 0x13, 0xd3,
    0x2b, 0x7d, 0x46, 0xc8, 0x8b, 0xc7, 0x8c, 0xca, 0x59, 0xec, 0x66, 0x17, 0x70, 0xbb, 0xf9, 0x92,
  },
  {
    0x89, 0xca, 0x92, 0x19, 0x01, 0xb8, 0x4b, 0x97, 0x06, 0x1a, 0x12, 0x91, 0x72, 0x11, 0xeb, 0x12,
    0x8b, 0x12, 0xd9, 0xdc, 0xc9, 0xb2, 0x37, 0xf8, 0x3e, 0x02, 0x03, 0xbe, 0x45, 0x45, 0xc9, 0x42,
  },
  {
    0x45, 0x2c, 0x80, 0xe1, 0x3a, 0x0a, 0xdf, 0xa3, 0xd2, 0x4a, 0x23, 0x0d, 0x47, 0x0d, 0x49, 0xad,
    0xdf, 0xb0, 0x42, 0xdf, 0x87, 0x85, 0xa6, 0x8f, 0x9f, 0x7e, 0x9b, 0xa4, 0x42, 0x64, 0xcb, 0xfb,
  },
  {
    0xc7, 0x39, 0x26, 0xb1, 0x90, 0x4d, 0xc1, 0x7a, 0xea, 0x31, 0x1b, 0xae, 0x1a, 0x5c, 0x1f, 0x4f,
    0x44, 0x2f, 0x87, 0x08, 0x5d, 0xa6, 0x74, 0xfd, 0xab, 0xb2, 0x4b, 0x01, 0xed, 0xd5, 0x4c, 0xe6,
  },
  {
    0x2a, 0xef, 0xfa, 0x25, 0x3c, 0xd2, 0xc8, 0x08, 0x9c, 0x33, 0x3c, 0x47, 0xb3, 0xb5, 0x44, 0x34,
    0x97, 0xee, 0xe8, 0x52, 0x1c, 0x15, 0xb3, 0xe0, 0xda, 0xef, 0x77, 0xde, 0x15, 0x39, 0x4b, 0x38,
  },
  {
    0x8a, 0x3a, 0x59, 0x61, 0x9d, 0x3e, 0x9b, 0x38, 0xc9, 0x84, 0x80, 0xaf, 0xb4, 0x37, 0x8a, 0x67,
    0x47, 0xc9, 0x6c, 0x72, 0xef, 0x39, 0x50, 0x28, 0x6c, 0x8f, 0xad, 0x09, 0x75, 0x26, 0xc9, 0xa9,
  },
  {
    0x27, 0x1e, 0x8b, 0xf6, 0x6b, 0x56, 0x5d, 0x17, 0x58, 0xac, 0xdf, 0x27, 0xd9, 0x3e, 0x5b, 0xdd,
    0xaf, 0xbc, 0xb7, 0xf9, 0x76, 0x3b, 0x40, 0x06, 0xbc, 0x6e, 0xec, 0xaa, 0xb2, 0xdc, 0x9a, 0x0c,
  },
  {
    0x09, 0x14, 0xef, 0x19, 0xc7, 0x7d, 0xc8, 0xa3, 0xd0, 0xaa, 0x7f, 0x09, 0x18, 0xaf, 0xd3, 0xde,
    0xbf, 0x05, 0xfc, 0xf9, 0xeb, 0xc0, 0x8e, 0xcf, 0xc7, 0x4c, 0x2f, 0x3f, 0xd4, 0x51, 0x41, 0xb2,
  },
  {
    0xb7, 0x33, 0xf3, 0x72, 0x6d, 0x12, 0xc1, 0x5c, 0x5d, 0x81, 0xb3, 0x63, 0x81, 0x50, 0x81, 0xc0,
    0x4a, 0xea, 0x18, 0x7c, 0xa6, 0x2d, 0x23, 0xba, 0x4b, 0xb9, 0x31, 0xd9, 0xab, 0x20, 0x60, 0x77,
  },
  {
    0xbb, 0x1c, 0x50, 0x2d, 0xdc, 0x18, 0x27, 0x98, 0x60, 0xde, 0x17, 0xd9, 0x17, 0x3c, 0xd5, 0x98,
    0xc3, 0x12, 0xfd, 0x8b, 0x25, 0x1e, 0xa5, 0xc1, 0xa8, 0xef, 0xec, 0x05, 0x3e, 0xfc, 0xd1, 0xfc,
  },
  {
    0xe6, 0x3b, 0x9f, 0x33, 0x85, 0xeb, 0x91, 0xd0, 0xad, 0x2f, 0xc2, 0x96, 0x61, 0x64, 0xbc, 0x12,
    0x15, 0x79, 0x65, 0x93, 0xc2, 0x63, 0xa3, 0x27, 0x88, 0x60, 0x39, 0x35, 0x21, 0x05, 0xe9, 0x49,
  },
  {
    0x9b, 0x68, 0xe7, 0xc8, 0xea, 0x0e, 0x5c, 0xa4, 0x03, 0x3a, 0x4e, 0x31, 0xb1, 0x92, 0xad, 0x9d,
    0x7e, 0xb5, 0x93, 0x81, 0xdd, 0x7a, 0xe9, 0xa1, 0x69, 0x28, 0x6a, 0xaf, 0x48, 0x05, 0x94, 0xc0,
  },
  {
    0x66, 0x3d, 0x87, 0xc1, 0x48, 0x9d, 0xdf, 0x99, 0x25, 0xd7, 0xb0, 0xfa, 0x03, 0x8b, 0x62, 0x60,
    0xc5, 0x07, 0x3f, 0xa2, 0xc8, 0xbd, 0x70, 0xdb, 0x40, 0x6c, 0x65, 0xbf, 0x15, 0xfc, 0x1e, 0xc9,
  },
  {
    0x38, 0x9c, 0x1a, 0x5b, 0x4f, 0x84, 0xca, 0xe1, 0x30, 0x6a, 0xf0, 0xb6, 0xf1, 0x61, 0xd3, 0xb0,
    0xa6, 0x6d, 0x0d, 0x11, 0x03, 0xe0, 0xcb, 0x9f, 0xbe, 0x7e, 0xc2, 0x7a, 0x53, 0x9d, 0x39, 0xcb,
  },
  {
    0xf3, 0x47, 0x4a, 0x37, 0xcd, 0x19, 0x27, 0x0f, 0xfb, 0x3f, 0xcb, 0x81, 0x1e, 0x0f, 0xfd, 0x1f,
    0x2e, 0x8d, 0xff, 0xe9, 0x52, 0x8b, 0x8e, 0x52, 0x3c, 0x82, 0xe6, 0x44, 0xf6, 0x92, 0xd4, 0xd4,
  },
  {
    0x3a, 0xe8, 0x4d, 0xcc, 0x4a, 0x0e, 0xaa, 0xf6, 0x32, 0x88, 0x4c, 0xee, 0xaa, 0x9c, 0xeb, 0x59,
    0xb5, 0xb8, 0x06, 0x89, 0x49, 0xc9, 0xa6, 0xf7, 0xa6, 0x14, 0x44, 0x55, 0x5e, 0x3e, 0x86, 0x08,
  },
  {
    0xca, 0x3d, 0x95, 0x21, 0xf3, 0xbb, 0x78, 0x29, 0x6a, 0x38, 0xd3, 0xe4, 0x48, 0x98, 0x6f, 0x0e,
    0xaf, 0x46, 0xa5, 0x02, 0xdd, 0xfb, 0x52, 0x42, 0x9b, 0x69, 0x97, 0xe6, 0x68, 0x21, 0x0d, 0x69,
  },
  {
    0x3a, 0x8a, 0x14, 0x6e, 0xa2, 0x24, 0x8f, 0x89, 0x5e, 0x99, 0x8a, 0x5b, 0x90, 0xb1, 0xf3, 0x64,
    0x4d, 0x10, 0xef, 0x45, 0xa9, 0xfb, 0xbb, 0xc0, 0xf5, 0x66, 0xdf, 0x15, 0xae, 0xd0, 0xd9, 0x56,
  },
  {
    0x62, 0x50, 0x52, 0xb5, 0xb9, 0x76, 0xa7, 0xcb, 0xe6, 0xf7, 0x3a, 0x9f, 0xa4, 0x1e, 0x0a, 0x4d,
    0x88, 0xa4, 0x1c, 0xea, 0x11, 0x8c, 0xfb, 0xbe, 0x70, 0x62, 0xec, 0x4e, 0x00, 0x56, 0x0e, 0xa9,
  },
};

#endif /* SANDYBRIDGE_RAMINIT_PATTERNS_H */
