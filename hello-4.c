#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define DRIVER_AUTHOR "Arna Maity <arnamaity6230@gmail.com>"
#define MODULE_DESC "Hello World Module."

static int __init hello_4_init(void);
static void __exit hello_4_exit(void);

static int __init hello_4_init(void){
    printk(KERN_INFO"Hello!... Just Entered the Kernel!");
    return 0;
}

static void __exit hello_4_exit(void){
    printk(KERN_INFO"Bye... Leaving the Kernel!");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(MODULE_DESC);

module_init(hello_4_init);
module_exit(hello_4_exit);