#include <linux/module.h>
#include <linux/kernel.h>

int hello_init(void);
void hello_exit(void);
/*  Priyanshu Yadav */
int hello_init(){
    printk(KERN_INFO"Hello From the Linux Kernel Module!!");
    return 0;
}

void hello_exit(){
    printk(KERN_INFO"Ok Bye... Leaving The Kernel...");
}

module_init(hello_init);
module_exit(hello_exit);