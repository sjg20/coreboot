# Managing the Coreboot Control Block

The Coreboot Control Block (CCB) is a small area of the bootblock which holds
settings for coreboot, such as whether to silence the console or not. These can
be changed without rebuilding coreboot, thus avoiding the need for multiple
images for minor differences.

You can use cbfstool to change these settings, for example, this enables
silent console in the bootblock:
```
$ cbfstool coreboot.rom ccb-set -n serial -V silent -v
INFO: Performing operation on 'COREBOOT' region...
serial=normal
```

Use `-n` to specify the setting to change and `-V` to specify its new value.

To check the setting:

```
$ cbfstool coreboot.rom ccb-get -n serial
serial=normal
```

Future work will enable passing the CCB from one coreboot stage to the next,
so as to control the console for all stages.
