#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

/*  ECE 1058 CourseWork Priyanshu Yadav RollNo- 220105038*/
static int __hello_init(void);
static void __hello_exit(void);

static int __hello_init(){
    printk(KERN_INFO"Hello From the Linux Kernel Module!! #Priyanshu Yadav");
    return 0;
}

static void __hello_exit(){
    printk(KERN_INFO"Ok Bye... Leaving The Kernel...");
}

module_init(__hello_init);
module_exit(__hello_exit);