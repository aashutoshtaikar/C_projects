#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int hello_init(void){
    printk(KERN_INFO "hello kernel from %s function\n",__FUNCTION__);
    return 0;
}

static void hello_exit(void)
{
	printk(KERN_INFO "Goodbye kernel from %s function\n",__FUNCTION__);
}

module_init(hello_init); //macro to init the module, invoked by insmod
module_exit(hello_exit); //macro to exit the module, invoked by rmmod 