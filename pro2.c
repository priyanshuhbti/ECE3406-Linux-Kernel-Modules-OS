// Managing /proc file with Standard File System
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define PROC_ENTRY_FILENAME "buffer2k"
#define PROCFS_MAX_SIZE 2048

MODULE_AUTHOR("Priyanshu Yadav <priyanshs.ece@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("/proc FS using Standard File System");

// Prototypes
static int __init procfs2_init(void);
static void __exit procfs2_exit(void);

/*
    The 2k buffer for this module.
 */

 static char procfs_buffer[PROCFS_MAX_SIZE];

 /*
    The size of the data hold in the buffer.
  */

static unsigned long procfs_buffer_size = 0;

/*
    The structure to keep info about the /proc file
 */

 static struct proc_dir_entry* Our_Proc_File;

/*
    The following function is called when the proc file is read
 */

 static ssize_t procfs_read(struct file* file, char* buffer, size_t length, loff_t* offset)
 {
     static int finished=0;

     if(finished){
        printk(KERN_INFO"procfs_read: END\n");
        finished=0;
        return 0;
     }

     finished=1;

     if(raw_copy_to_user(buffer, procfs_buffer, procfs_buffer_size)){
         return -EFAULT;
     }

     printk(KERN_INFO"procfs_read: read %lu bytes",procfs_buffer_size);

     return procfs_buffer_size;
 }

 /*
    The following function is called when we write to the /proc file.
  */
static ssize_t procfs_write(struct file* file, const char* buffer, size_t len,loff_t* offset)
{
    if(len > PROCFS_MAX_SIZE)
        procfs_buffer_size = PROCFS_MAX_SIZE;
    else
        procfs_buffer_size = len;

    if(raw_copy_from_user(procfs_buffer,buffer,procfs_buffer_size)){
        return -EFAULT;
    }

    printk(KERN_INFO"Wrote %lu bytes \n", procfs_buffer_size);
    return procfs_buffer_size;
}

/*
    Function to decide whether to allow an operation.
 */

/* static int module_permission(struct inode* inode, int op, struct nameidata* foo)
{
        Allow everyone to read from our module,
        but ony root will be able to write to it. 
     
    if(op==4 || (op==2 && current->euid==0))
        return 0;

    return -EACCESS;
}
 */

/*
    File open & close Handlers
 */

int procfs_open(struct inode* inode, struct file* file)
{
    try_module_get(THIS_MODULE);
    return 0;
}

int procfs_close(struct inode* inode, struct file* file)
{
    module_put(THIS_MODULE);
    return 0;
}

static struct file_operations File_Ops_4_Our_Proc_File = {
    .read = procfs_read,
    .write = procfs_write,
    .open = procfs_open,
    .release = procfs_close
};

// The following method of setting permissions is obsolete and won't work anymore... 
/* static struct inode_operations File_Ops_4_Out_Proc_File = {
    .permission = module_permission,
};
 */
/*
    Module Initialization & Exit Functions.
 */
static int __init procfs2_init(void)
{
    Our_Proc_File = proc_create(PROC_ENTRY_FILENAME,0666,NULL,&File_Ops_4_Our_Proc_File);
    if(!Our_Proc_File)
    {
        printk(KERN_ALERT"Error: Could not initialize /proc/%s \n",PROC_ENTRY_FILENAME);
        return -ENOMEM;
    }

    printk(KERN_INFO"/proc/%s created!",PROC_ENTRY_FILENAME);
    return 0;
}

static void __exit procfs2_exit(void)
{
    proc_remove(Our_Proc_File);
    printk(KERN_INFO"/proc/%s removed!", PROC_ENTRY_FILENAME);
}

module_init(procfs2_init);
module_exit(procfs2_exit);