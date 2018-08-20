#!/bin/bash

git submodule update -i

if [ ! -e image/EFI/BOOT ]; then
  mkdir -p image/EFI/BOOT
fi

cd edk2
git checkout xv6_uefiloader
source edksetup.sh
if [ ! -e Build/OvmfX64 ]; then
        make -C BaseTools/Source/C
        build -p OvmfPkg/OvmfPkgX64.dsc
fi
build -p xv6_bootloader/xv6_bootloader.dsc

cd ../xv6_public
git checkout uefi
make kernelmemfs
cp kernelmemfs ../image/kernel

