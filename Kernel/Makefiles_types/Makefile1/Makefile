#accessing the 
obj-m +=hellokernel.o

KDIR = /usr/src/linux-headers-4.15.0-48-generic

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 

clean:
	rm -rvf *.o *.ko *.mod *.symvers *.orders *.order *.mod.c .*cache.mk .*.ko.cmd .*.cmd .*tmp_versions


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

