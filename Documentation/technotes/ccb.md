# coreboot Control Block (CCB)

The `coreboot Control Block` (CCB) is a small area of the bootblock which holds
settings for coreboot, such as whether to silence the console or not. These can
be changed without rebuilding coreboot, thus avoiding the need for multiple
images for minor differences.

The CCB is really just a C struct with a magic number at the start, so it can
be easily found in the bootblock binary. It is compiled into the bootblock
just like any other data.

When bootblock starts up it calls `ccb_init()` to find the CCB. The settings are
made available through a simple API defined in ccb_api.h

Bootblock then adds the CCB to cbmem so that it will be available to any future
coreboot stages which are present, including romstage, postcar and ramstage.
Each stage calls `ccb_init()` and uses the same API to access the settings.

## Changing settings

Settings are changed using a special cbfstool subcommand.

```eval_rst
See
:doc:`../util/cbfstool/ccb`
for more information.
```


## Available settings

So far, apart from the magic number, the CCB consists only of a set of flags,
32 bits in length. The default flags value is 0 if the CCB is not present.

## Extending CCB

New flags can be added to `enum ccb_flags` as needed. Note that the default
value of the flag should be zero, i.e. the normal state of coreboot is to have
all flags be zero. Flags should be used to change that normal state. Be careful
not to introduce flags which requires a non-zero value for normal operation.

New fields can be added to the CCB by extended `struct ccb`. Examples might
include controlling the log level,

Any new settings should be implemented  to cbfstool as well so that the values
can be read and written.

## Backwards compatibility

The CCB is not intended to be stored or generated outside the coreboot build,
so versioning is not included. In fact, while backwards compatibility should be
maintained where possible, it is not stictly necessary, since the CCB struct
does not have any meaning outside coreboot and all of the coreboot stages are
assumed to be build from the same version of the source code.

Strictly speaking, changing the settings should be done with a cbfstool built
from the same source, although since the CCB will likely change infrequently,
this may not be always be necessary in practice.

## Future extensions

Some boards used a signed bootblock which cannot easily be modified after
building, since it requires resigning parts of the image. To address this, the
CCB could be stored in the romstage instead. This means it is unable to affect
the operation of bootblock, of course. This could be controlled by a new
ROMSTAGE_CCB option.

The CMOS option feature (in `include/option.h`) could be expanded to provide an
API for CCB. Using strings for options might be too inefficient for bootblock,
so an enum could be introduced for common option types, with a lookup table used
to convert between strings and integers.
