#!/bin/bash

cd edk2
source edksetup.sh
build -a X64

cd ../xv6_public
make kernelmemfs
cp kernelmemfs ../image/kernel

