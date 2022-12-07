# coreboot kconfig

This is coreboot's copy of kconfig which tracks Linux as upstream but comes
with a few patches for portability but also a few semantic changes.

The patches that lead to this tree can be found in the patches/ subdirectory
in a [quilt](http://savannah.nongnu.org/projects/quilt) friendly format that
is also simple enough to manage manually with Unix tooling.

## Updating kconfig

The first step is to unapply the patches. This can either be done with quilt
in an already-configured tree (`quilt pop -a` should cleanly unapply them all)
or manually if quilt doesn't have its tracking metadata around yet:

    $ for i in `ls patches/*.patch | tac`; do patch -p1 -R -i "$i"; done

The result should be a subtree that, apart from a few coreboot specific
files on our side (e.g. documentation, integration in our build system)
and a few files on the upstream end that we don't carry (e.g. the tests),
is identical to the scripts/kconfig/ directory of Linux as of the most recent
uprev we did. Check the uprev version by looking through
`git log util/kconfig` output in our tree.

Assuming that you want to uprev from Linux 5.13 to 5.14, with a Linux git tree
available in ~/linux,

    $ cd util/kconfig && (cd ~/linux/ && git diff v5.13..v5.14 scripts/kconfig) | patch -p2`

applies the changes to your local tree.

Then reapply our patch train, which might be as simple as
`quilt push -a --refresh` but might also require some meddling with the
patches to make them apply again with the changes you just imported from
Linux.

Check that kconfig still works, `git add` and `git commit` the changes and
write a meaningful commit message that documents what Linux kconfig version
the tree has been upreved to.

## Adding a new patch
The format of the patches to kconfig is a mix of the headers produced by `git
format-patch` and the patch format of quilt. However neither git nor quilt
seems to have any functionality to directly produce a file in such a format

To add a patch in this format:
1. Add your changes to the sources and `git commit` them
2. Generate a git patch for the commit:

    $ git format-patch HEAD~

3. Reverse apply the newly created patch file to restore the tree back to the
   state quilt thinks it is in:

    $ git apply -R <the patch file>

4. Import the patch info quilt:

    $ quilt import <the patch file>

5. Force push the change to the top of quilt's patch stack (quilt won't like
   the git diff style and would normally refuse to apply the patch):

    $ quilt push -f <the patch file>

6. Add the changed files to be tracked against the quilt:

    $ quilt add <the files you changed>

7. Re-apply your changes from the patch file:

    $ git apply <the patch file>

8. Add the changes to quilt to regenerate the patch file in a quilt compatible
   format while keeping the git header:

    $ quilt refresh

9. The new patch file and updated patches/series files can now be added to the
   git commit
