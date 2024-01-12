#
# Makefile for the HID driver
#
ccflags-y += -DVERSION=$(VERSION)
obj-m += hid-vader3.o

#FIXME(kakra) Work-around, cleanup after source code split
hid-vader3-y += vader3.o
$(obj)/vader3.c: $(src)/hid-vader3.c
	cp $< $@

# hid-vader3-y += vader3/core.o vader3/consumer.o vader3/keyboard.o
