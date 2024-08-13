#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "iter"

MODULE_AUTHOR("Arna Maity <arnamaity6230@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module illustrating the management of procfs using seq_file.");

// Prototypes for Module Entry & Exit functions.
static int __init procfs3_init(void);
static void __exit procfs3_exit(void);

struct proc_dir_entry* entry;

static void* my_seq_start(struct seq_file* s, loff_t* pos)
{
    static unsigned long counter = 0;
    if(*pos == 0)
        return &counter;

    else{
        *pos = 0;
        return NULL;
    }
}

static void* my_seq_next(struct seq_file* s, void* v, loff_t* pos)
{
    unsigned long *tmp_v = (unsigned long*)v;
    (*tmp_v)++;
    (*pos)++;
    return NULL;
}

static void my_seq_stop(struct seq_file* s, void* v)
{

}

static int my_seq_show(struct seq_file* s, void* v)
{
    loff_t* spos = (loff_t*)v;
    seq_printf(s,"%Ld\n",*spos);

    return 0;
}

/*  This Structure gathers "functions" to manage the sequence. 
 */
static struct seq_operations my_seq_ops = {
    .start = my_seq_start,
    .next = my_seq_next,
    .stop = my_seq_stop,
    .show = my_seq_show
};

/*  This function is called when the /proc file is opened. 
 */

static int my_open(struct inode* inode, struct file* file)
{
    return seq_open(file, &my_seq_ops);
}

/*  This structure gathers all the functions to manage the /proc file. 
 */
 static struct file_operations my_file_ops = {
     .owner = THIS_MODULE,
     .open = my_open,
     .read = seq_read,
     .llseek = seq_lseek,
     .release = seq_release
 };

static int __init procfs3_init(void)
{
    entry = proc_create(PROC_NAME,0,NULL,&my_file_ops);
    return 0;
}

static void __exit procfs3_exit(void)
{
    proc_remove(entry);
}

module_init(procfs3_init);
module_exit(procfs3_exit);