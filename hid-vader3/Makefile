KERNEL_SOURCE_DIR ?= /lib/modules/$(shell uname -r)/build
LD := ld.bfd

all: modules

.INTERMEDIATE: ../VERSION

../VERSION:
	git describe --tags --dirty >$@

clean modules modules_install: ../VERSION
	$(MAKE) -C $(KERNEL_SOURCE_DIR) INSTALL_MOD_DIR="kernel/drivers/hid" LD=$(LD) M=$(shell pwd)/src VERSION="$(shell cat ../VERSION)" $@

reinstall: modules
	sudo make modules_install
	sudo rmmod hid-vader3 || true
	sudo modprobe hid-vader3 $(MOD_PARAMS)
