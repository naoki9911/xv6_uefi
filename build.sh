#!/bin/bash

if [ -e edk2 ]; then
        git submodule update -i
fi

if [ -e image/EFI/BOOT ]; then
  mkdir -p image/EFI/BOOT
fi

cd edk2
git checkout xv6_uefiloader
source edksetup.sh
if [ -e edk2/Build/OvmfX64/RELEASE_GCC5/FV ]; then
        make -C edk2/BaseTools/Source/C
        build -p OvmfPkg/OvmfPkgX64.dsc
fi
build

cd ../xv6_public
git checkout xv6
make kernelmemfs
cp kernelmemfs ../image/kernel

