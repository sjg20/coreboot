/* SPDX-License-Identifier: GPL-2.0-only */

External(\_SB.DDEF, MethodObj)
External(\_SB.DTAB, MethodObj)

Scope (\_SB)
{
    Method (DPTC, 0, Serialized)
    {
        /* If _SB.DDEF is not present, DPTC is not enabled so return early. */
        If (!CondRefOf (\_SB.DDEF))
        {
            Return (Zero)
        }

        If (CondRefOf (\_SB.DTAB) && (\_SB.PCI0.LPCB.EC0.TBMD == One))
        {
            \_SB.DTAB()
            Return (Zero)
        }

        \_SB.DDEF()
        Return (Zero)
    }
}
