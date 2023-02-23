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

## Searching for the CCB

The CCB magic number is chosen so that it is very unlikey to appear in normal
bootblock code. The CCB_MAGIC is never used in the code itself, only in
cbfstool.

## Extending CCB

New flags can be added to `enum ccb_flags` as needed. Flags bits which are not
yet defined default to zero and that the default value should maximise
compatibility. In other words, be careful not to introduce flags which requires
a non-zero value for normal operation.

New fields can be added to the CCB by extending `struct ccb`. Examples might
include controlling the log level.

Any new settings should be implemented  to cbfstool as well so that the values
can be read and written.

## Backwards compatibility

The CCB is not intended to be stored or generated outside the coreboot build,
so versioning is not included. In fact, while backwards compatibility should be
maintained where possible, it is not stictly necessary, since the CCB struct
does not have any meaning outside coreboot and all of the coreboot stages are
assumed to be built from the same version of the source code.

Strictly speaking, changing the settings should be done with a cbfstool built
from the same source, although since the CCB will likely change infrequently,
this may not be always be necessary in practice.

## Implementation notes

Like the timestamp records, the CCB must be available from the start of the
first coreboot stage, right through to ramstage. The technique used by CCB is
largely the same as with timestamps. In bootblock, the CCB is simply a struct
in the data section, which can be updated by cbfstool. Bootblock copies this
struct into a cache defined by the linker script, so that the following pre-RAM
stages can access it. When romstage runs, it copies the CCB out of the cache
and into CBMEM. Thus it can be used by the following stages which don't have
access to the cache.

Some boards use a signed bootblock which cannot easily be modified after
building, since it requires resigning parts of the image. To address this, the
CCB can be stored in CBFS instead, accessed from the romstage. This means it is
unable to affect the operation of bootblock, of course. This is controlled by
the CCB_CBFS option. This applied mostly to AMD, since Intel platforms, do not
have a signed bootblock.

## Future extensions

The CMOS option feature (in `include/option.h`) could be expanded to provide an
API for CCB. Using strings for options might be too inefficient for bootblock,
so an enum could be introduced for common option types, with a lookup table used
to convert between strings and integers.
