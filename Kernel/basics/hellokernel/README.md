
## Build the kernel object  
hellokernel.c -> hellokernel.o -> hellokernel.ko  
run make clean  
run make  

## insert module, remove module to the kernel
sudo insmod hellokernel.ko   
sudo rmmod hellokernel.ko  

## To see the modules loaded in the kernel:
#### To see the modules already loaded
dmesg 
OR

#### To see the modules being loaded in real time
gnome-terminal & disown      //open another terminal to do insmod and rmmod   
 
sudo tail -f /var/log/syslog //for displaying the recent modules    

## Makefiles
target … : prerequisites …
        recipe
        …
        …

# Note:
M=$(PWD) //pick up the makefile from the present working directory (/lib/modules/$(KVERSION)/build)

# References
1. https://www.youtube.com/watch?v=IiHrZcZrT64&list=PL2GL6HVUQAuksbptmKC7X4zruZlIl59is&index=2
2. https://www.kernel.org/doc/Documentation/kbuild/modules.txt

#### Makefile which does out of source-tree builds for out of kernel-tree modules
https://stackoverflow.com/questions/5718899/building-an-out-of-tree-linux-kernel-module-in-a-separate-object-directory
