/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2020 Intel Corporation.
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

Scope (\_SB.PCI0.IPU0)
{
	Name (_DSD, Package (0x02)
	{
		ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package (0x02)
		{
			Package (0x02)
			{
				"port0",
				"PRT0"
			},

			Package (0x02)
			{
				"port1",
				"PRT1"
			}
		}
	})

	Name (PRT0, Package (0x04)
	{
		ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package (0x01)
		{
			Package (0x02)
			{
				"port",
				One
			}
		},

		ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package (0x01)
		{
			Package (0x02)
			{
				"endpoint0",
				"EP00"
			}
		}
	})

	Name (PRT1, Package (0x04)
	{
		ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package (0x01)
		{
			Package (0x02)
			{
				"port",
				2
			}
		},

		ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		Package (0x01)
		{
			Package (0x02)
			{
				"endpoint0",
				"EP10"
			}
		}
	})
}

Scope (_SB.PCI0.IPU0)
{
	Name (EP00, Package (0x02)
	{
		ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package (0x04)
		{
			Package (0x02)
			{
				"endpoint",
				Zero
			},

			Package (0x02)
			{
				"clock-lanes",
				Zero
			},

			Package (0x02)
			{
				"data-lanes",
				Package (0x04)
				{
					One,
					0x02,
					0x03,
					0x04
				}
			},

			Package (0x02)
			{
				"remote-endpoint",
				Package (0x03)
				{
					^I2C3.CAM0,
					Zero,
					Zero
				}
			}
		}
	})
	Name (EP10, Package (0x02)
	{
		ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package (0x04)
		{
			Package (0x02)
			{
				"endpoint",
				Zero
			},

			Package (0x02)
			{
				"clock-lanes",
				Zero
			},

			Package (0x02)
			{
				"data-lanes",
				Package (0x04)
				{
					One,
					0x02,
					0x03,
					0x04
				}
			},

			Package (0x02)
			{
				"remote-endpoint",
				Package (0x03)
				{
					^I2C5.CAM1,
					Zero,
					Zero
				}
			}
		}
	})
}

Scope (\_SB.PCI0.I2C3)
{
	PowerResource (RCPR, 0x00, 0x0000)
	{
		Name (STA, Zero)
		Method (_ON, 0, Serialized)
		{
			If ((STA == Zero))
			{
				/* Enable CLK0 with 19.2MHz */
				MCCT(0,1,1)
				/* Pull PWREN(GPIO B23) high */
				STXS(GPP_B23)
				Sleep(5)
				/* Pull RST(GPIO C15) low */
				CTXS(GPP_C15)
				Sleep(5)
				/* Pull RST high */
				STXS(GPP_C15)
				Sleep(5)
				Store(1,STA)
			}
		}

		Method (_OFF, 0, Serialized)
		{
			If ((STA == One))
			{
				/* Pull RST low */
				CTXS(GPP_C15)
				/* Pull PWREN low */
				CTXS(GPP_B23)
				/* Disable CLK0 */
				MCCT(0,0,1)
				Store(0,STA)
			}
		}

		Method (_STA, 0, NotSerialized)
		{
			Return (STA)
		}
	}

	Device (CAM0)
	{
		Name (_HID, "OVTI8856")
		Name (_UID, Zero)
		Name (_DDN, "Ov 8856 Camera")
		Method (_STA, 0, NotSerialized)
		{
			Return (0x0F)
		}

		Name (_CRS, ResourceTemplate ()
		{
			I2cSerialBus (0x0010, ControllerInitiated, 0x00061A80,
				AddressingMode7Bit, "\\_SB.PCI0.I2C3",
				0x00, ResourceConsumer, ,
			)
		})

		Name (_PR0, Package (0x01)
		{
			RCPR
		})

		Name (_PR3, Package (0x01)
		{
			RCPR
		})

		Name (_DSD, Package (0x04)
		{
			ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
			Package (0x01)
			{
				Package (0x02)
				{
					"port0",
					"PRT0"
				}
			},

			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x02)
			{
				Package (0x02)
				{
					"clock-frequency",
					0x0124F800
				},
				Package (0x02)
				{
					"lens-focus",
					Package (0x01)
					{
						VCM0
					}
				}
			}
		})

		Name (PRT0, Package (0x04)
		{
			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x01)
			{
				Package (0x02)
				{
					"port",
					Zero
				}
			},

			ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
			Package (0x01)
			{
				Package (0x02)
				{
					"endpoint0",
					"EP00"
				}
			}
		})

		Name (EP00, Package (0x02)
		{
			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x03)
			{
				Package (0x02)
				{
					"endpoint",
					Zero
				},

				Package (0x02)
				{
					"link-frequencies",
					Package (0x01)
					{
						0x325AA000
					}
				},
				Package (0x02)
				{
					"remote-endpoint",
					Package (0x03)
					{
						IPU0,
						Zero,
						Zero
					}
				}
			}
		})
	}

	Device (VCM0)
	{
		Name (_HID, "PRP0001")
		Name (_UID, 0x03)
		Name (_DDN, "DW9714 VCM")
		Method (_STA, 0, NotSerialized)
		{
			Return (0x0F)
		}

		Name (_CRS, ResourceTemplate ()
		{
			I2cSerialBus (0x000C, ControllerInitiated, 0x00061A80,
				AddressingMode7Bit, "\\_SB.PCI0.I2C3",
				0x00, ResourceConsumer, ,
			)
		})
		Name (_DEP, Package (0x01)
		{
			CAM0
		})
		Name (_PR0, Package (0x01)
		{
			RCPR
		})
		Name (_PR3, Package (0x01)
		{
			RCPR
		})
		Name (_DSD, Package (0x02)
		{
			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x01)
			{
				Package (0x02)
				{
					"compatible",
					"dongwoon,dw9714"
				}
			}
		})
	}
}

Scope (\_SB.PCI0.I2C5)
{
	PowerResource (FCPR, 0x00, 0x0000)
	{
		Name (STA, Zero)
		Method (_ON, 0, Serialized)
		{
			If ((STA == Zero))
			{
				/* Enable CLK1 with 19.2MHz */
				MCCT(1,1,1)
				/* Pull PWREN(GPIO R6) high */
				STXS(GPP_R6)
				Sleep(5)
				/* Pull RST(GPIO H12) low */
				CTXS(GPP_H12)
				Sleep(5)
				/* Pull RST high */
				STXS(GPP_H12)
				Sleep(5)
				Store(1,STA)
			}
		}

		Method (_OFF, 0, Serialized)
		{
			If ((STA == One))
			{
				/* Pull RST low */
				CTXS(GPP_H12)
				/* Pull PWREN low */
				CTXS(GPP_R6)
				/* Disable CLK1 */
				MCCT(1,0,1)
				Store(0,STA)
			}
		}

		Method (_STA, 0, NotSerialized)  // _STA: Status
		{
			Return (STA)
		}
	}

	Device (CAM1)
	{
		Name (_HID, "OVTI8856")
		Name (_UID, Zero)
		Name (_DDN, "Ov 8856 Camera")
		Method (_STA, 0, NotSerialized)
		{
			Return (0x0F)
		}

		Name (_CRS, ResourceTemplate ()
		{
			I2cSerialBus (0x0010, ControllerInitiated, 0x00061A80,
				AddressingMode7Bit, "\\_SB.PCI0.I2C5",
				0x00, ResourceConsumer, ,
			)
		})

		Name (_PR0, Package (0x01)
		{
			FCPR
		})

		Name (_PR3, Package (0x01)
		{
			FCPR
		})

		Name (_DSD, Package (0x04)
		{
			ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
			Package (0x01)
			{
				Package (0x02)
				{
					"port0",
					"PRT0"
				}
			},

			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x01)
			{
				Package (0x02)
				{
					"clock-frequency",
					0x0124F800
				}
			}
		})

		Name (PRT0, Package (0x04)
		{
			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x01)
			{
				Package (0x02)
				{
					"port",
					Zero
				}
			},

			ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
			Package (0x01)
			{
				Package (0x02)
				{
					"endpoint0",
					"EP00"
				}
			}
		})

		Name (EP00, Package (0x02)
		{
			ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package (0x03)
			{
				Package (0x02)
				{
					"endpoint",
					Zero
				},

				Package (0x02)
				{
					"link-frequencies",
					Package (0x01)
					{
						0x325AA000
					}
				},
				Package (0x02)
				{
					"remote-endpoint",
					Package (0x03)
					{
						IPU0,
						One,
						Zero
					}
				}
			}
		})
	}
}
