obj-m +=hellokernel.o

KDIR ?= /lib/modules/$(shell uname -r)/build
BUILD_DIR ?= $(PWD)/build
BUILD_DIR_MAKEFILE ?= $(PWD)/build/Makefile

default: $(BUILD_DIR_MAKEFILE)
	$(MAKE) -C $(KDIR) M=$(BUILD_DIR) src=$(PWD) modules

$(BUILD_DIR):
	mkdir -p "$@"

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	touch "$@"

clean:
	make -C $(KDIR) M=$(BUILD_DIR) src=$(PWD) clean

# Build the kernel object, hellokernel.c -> hellokernel.o -> hellokernel.ko
# run make clean
# run make

# insert module, remove module to the kernel
# sudo insmod hellokernel.ko 
# sudo rmmod hellokernel.ko

# To see the modules loaded in the kernel:
# ls /var/log/syslog
# gnome-terminal & disown
# tail -f /var/log/syslog #for displaying the recent modules

# Note:
# M=$(PWD) //pick up the makefile from the present working directory (/lib/modules/$(KVERSION)/build)