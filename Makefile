BOOT_LOADER = edk2/xv6_bootloader/build/RELEASE_GCC5/X64/loader.efi
BOOT_IMAGE_PATH = image/EFI/BOOT
OVMF_CODE = edk2/Build/OvmfX64/RELEASE_GCC5/FV/OVMF_CODE.fd
OVMF_VARS = edk2/Build/OvmfX64/RELEASE_GCC5/FV/OVMF_VARS.fd
run:
	./build.sh
	cp -r $(BOOT_LOADER) $(BOOT_IMAGE_PATH)/BOOTX64.efi
	qemu-system-x86_64 \
	-drive if=pflash,format=raw,readonly,file=$(OVMF_CODE) \
	-drive if=pflash,format=raw,file=$(OVMF_VARS) \
	-drive if=ide,file=fat:rw:image,index=0,media=disk \
	-gdb tcp::4321 \
	-m 2048 \
	-smp 4 \
	-nographic
debug:
	./build.sh
	cp -r $(BOOT_LOADER) $(BOOT_IMAGE_PATH)/BOOTX64.efi
	qemu-system-x86_64 \
	-drive if=pflash,format=raw,readonly,file=$(OVMF_CODE) \
	-drive if=pflash,format=raw,file=$(OVMF_VARS) \
	-drive if=ide,file=fat:rw:image,index=0,media=disk \
	-gdb tcp::4321 \
	-m 2048 \
	-smp 4 \
	-monitor stdio \
	-net nic,model=e1000 \
	-net bridge,br=br0
