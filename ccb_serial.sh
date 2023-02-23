#!/bin/bash

# Demo script to enable/disable serial on an image
#
# This is all a terrible hack, of course. Done properly we would:
#
# - have a defined section for runtime config
# - support reading/writing it in cbfstool, e.g.:
#
#       cbfstool <image> ccb write silent-console 1   (or 0)
#
# Using bash so it could potentially go in an ebuild in the interim
#
# Usage: ccb_serial.sh <silent | noisy>
#

board=brya
model=felwinter

if [ "$1" == "silent" ]; then
	value=1
elif [ "$1" == "noisy" ]; then
	value=0
else
	echo "Usage: $0 <silent | noisy>"
	exit 1
fi

set -e

# Get filename: we assume that the original image has been processed with:
# sudo ifdtool -p adl --em100 ${image}
# which produces the .new file
boarddir="/build/${board}"
image="${boarddir}/firmware/image-${model}.serial.bin.new"
cbdir="${boarddir}/firmware/${model}/coreboot_serial"

# Length of bootblock header (hex)
bbhdrlen=40

# Read COREBOOT section
cbfstool "${image}" read -f cb

# Find offset of COREBOOT region within image (decimal!)
# 'COREBOOT' (CBFS, size 7909376, offset 25645056)
coreboot_offset_dec=$(cbfstool ${image} layout | grep COREBOOT |\
	sed -r 's/.*offset ([0-9]*)\)/\1/')
coreboot_offset=$(printf %x ${coreboot_offset_dec})

# Find offset of bootblock within region
# bootblock                      0x770d80   bootblock      107072 none
bboffset=$(cbfstool "${image}" print |grep bootblock | awk '{print substr($2, 3)}')

# Find offset of the bootblock binary within the bootblock (+0x20)
bbbinoffset="$(printf %x $((0x${bboffset}+0x${bbhdrlen})))"

# Get offset of ccb within bootblock
ccb=$(nm "${cbdir}/bootblock.debug" |grep -w ccb | awk '{print $1}')
base=$(nm "${cbdir}/bootblock.debug" |grep -w _text | awk '{printf $1}')
ccboffset="$(printf %x $((0x${ccb}-0x${base})))"

# Get offset within entire image
offset="$(printf %x $((0x${coreboot_offset}+0x${bbbinoffset}+0x${ccboffset})))"

printf "coreboot_offset %8s\n" ${coreboot_offset}
printf "bbinoffset      %8s\n" ${bbbinoffset}
printf "ccboffset       %8s\n" ${ccboffset}

echo "Image: ${image}"
echo "Writing flag to offset ${offset} ${ccboffset} within bootblock"

# write flag
if [ "${value}" == "1" ]; then
	printf '\x01' | sudo dd of="${image}" bs=1 seek=$((0x${offset})) conv=notrunc
else
	printf '\x02' | sudo dd of="${image}" bs=1 seek=$((0x${offset})) conv=notrunc
fi
