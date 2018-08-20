#!/bin/bash
OVMF_PATH=Build/OvmfX64/RELEASE_GCC5/FV
git submodule update -i

if [ ! -e image/EFI/BOOT ]; then
  mkdir -p image/EFI/BOOT
fi

cd edk2
git checkout xv6_uefiloader
source edksetup.sh
if [ ! -e $OVMF_PATH/OVMF_CODE.fd -o ! -e $OVMF_PATH/OVMF_VARS.fd ]; then
        make -C BaseTools/Source/C
        build -p OvmfPkg/OvmfPkgX64.dsc
fi
build -p xv6_bootloader/xv6_bootloader.dsc

cd ../xv6_public
git checkout uefi
make kernelmemfs
cp kernelmemfs ../image/kernel

