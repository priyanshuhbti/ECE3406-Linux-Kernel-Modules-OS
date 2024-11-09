/* 
 *   ComKernel.c : A simple Character Device Driver.
 */

/*Priyanshu Yadav RollNO-220105038*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/stat.h>
#include <asm/uaccess.h>

// Constants
#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

// Module Info ( displayed by 'modinfo' )
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple Character Device Driver.");

// Function Prototypes
static int __init chardev_init(void);
static void __exit chardev_exit(void);
static int device_open(struct inode*, struct file*);
static int device_release(struct inode*, struct file*);
static ssize_t device_read(struct file*, char*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char*, size_t, loff_t*);

/*  Global Variables 
 */

static int Major;               // Major number assigned to the deivce driver.
static int Device_Open = 0;     //Is the device open?

static char msg[BUF_LEN];
static char* msg_Ptr;

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

static int __init chardev_init(void){
    
    Major = register_chrdev(0,DEVICE_NAME,&fops);

    if(Major < 0){
        printk(KERN_ALERT"Register Char Device failed with %d\n", Major);
        return Major;
    }

    printk(KERN_INFO"I was assigned major number %d. To talk to\n",Major);
    printk(KERN_INFO"the driver, create a dev file with\n");
    printk(KERN_INFO"'mknod /dev/%s c %d 0'.\n",DEVICE_NAME,Major);
    printk(KERN_INFO"Try the various minor numbers. Try cat and echo to\n");
    printk(KERN_INFO"the device file.\n");
    printk(KERN_INFO"Remove the Device File and Module when done.\n");

    return SUCCESS;
}

static void __exit chardev_exit(void){
    unregister_chrdev(Major,DEVICE_NAME);
}

/*
        Called when the process tries to open the device file.
 */

 static int device_open(struct inode* inode,struct file* file){
     static int counter=0;
     if (Device_Open)
        return -EBUSY;

    Device_Open++;
    sprintf(msg,"I already told you Hello World %d times!",counter++);
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);

    return SUCCESS;
 }

 /* 
    Called when a process closes the device file.
  */
  static int device_release(struct inode* inode, struct file* file){
      Device_Open--;
      module_put(THIS_MODULE);

      return 0;
  }

static ssize_t device_read(struct file* filp, char* buffer, size_t length, loff_t* offset){
    int bytes_read = 0;

    if(*msg_Ptr == 0)
        return 0;

    while(length && *msg_Ptr){
        put_user(*(msg_Ptr++),buffer++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

/* Called when a process writes to dev file. 
 */

 static ssize_t device_write(struct file* filp, const char* buff, size_t len, loff_t* off){
     printk(KERN_ALERT"Sorry, this operation isn't supported.\n");
     return -EINVAL;
 }

module_init(chardev_init);
module_exit(chardev_exit);


