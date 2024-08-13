#include <linux/module.h>   // Required for creating a Loadable Kernel Module (LKM)
#include <linux/kernel.h>   // To use the different Kernel Constants viz. KERN_DEBUG, KERN_INFO, KERN_ALERT ...
#include <linux/proc_fs.h>  // To use the /proc filesystem.
#include <asm/uaccess.h>   // for userspace access...

#define PROCFS_NAME "Hello World!"

struct proc_dir_entry* Our_Proc_File;

MODULE_DESCRIPTION("A Simple /proc FS Driver.");
MODULE_AUTHOR("Arna Maity <arnamaity6230@gmail.com>");
MODULE_LICENSE("GPL");

/* create_proc_entry() & remove_proc_entry() are deprecated */

static int __init procfs_init(void);
static void __exit procfs_exit(void);

static ssize_t procfile_read(struct file* file,char __user *ubuf, size_t count, loff_t* ppos){

    printk(KERN_DEBUG"procfile_read ( /proc/%s ) called \n",PROCFS_NAME);
    printk(KERN_INFO"Read Handler Invoked!");
    return 0;
}

static struct file_operations myops = 
{
	.owner = THIS_MODULE,
	.read = procfile_read,
};

static int __init procfs_init(void){
    Our_Proc_File = proc_create(PROCFS_NAME,0644,NULL,&myops);

    if (Our_Proc_File == NULL){
        printk(KERN_ALERT"Error: Could not initialize /proc/%s \n",PROCFS_NAME);
        return -ENOMEM;
    }  

    printk(KERN_INFO"/proc/%s is created. \n",PROCFS_NAME);
    return 0;
}

static void __exit procfs_exit(void){
    proc_remove(Our_Proc_File);
    printk(KERN_INFO"/proc/%s is removed. \n",PROCFS_NAME);
}

module_init(procfs_init);
module_exit(procfs_exit);