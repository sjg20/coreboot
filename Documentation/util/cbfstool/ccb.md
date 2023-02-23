# Managing the coreboot Control Block

The coreboot Control Block (CCB) is a small area of the bootblock which holds
settings for coreboot, such as whether to silence the console or not. These can
be changed without rebuilding coreboot, thus avoiding the need for multiple
images for minor differences.

You can use 'cbfstool configure' to change these settings.

Use `-n` to specify the setting to change and `-V` to specify its new value.

To check the setting, use 'cbfstool configure-get'.

```eval_rst
See
:doc:`../../technotes/ccb`
for more information.
```
