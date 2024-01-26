#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

static char *new_hostname;
module_param(new_hostname, charp, 0644);

int __read_file(const char *filename)
{
    struct file *filp;
    struct inode *inode;
    mm_segment_t old_fs;
    off_t fsize;
    char *buf;
    ssize_t flag;

    filp = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(filp))
    {
        printk(KERN_ALERT "<-1>Cannot open %s\n", filename);
        return 1;
    }
    if (!filp)
    {
        printk(KERN_ALERT "<-1>Filp is null\n");
        return 1;
    }

    inode = filp->f_path.dentry->d_inode;
    fsize = inode->i_size;
    printk("<1>File size:%i \n", (int)fsize);
    buf = (char *)kmalloc(fsize + 1, GFP_KERNEL);
    if (IS_ERR(buf))
    {
        printk(KERN_ALERT "<-1>Kmalloc cause failure\n");
        filp_close(filp, NULL);
        return 1;
    }
    if (!buf)
    {
        printk(KERN_ALERT "<-1>Buf is null\n");
        filp_close(filp, NULL);
        return 1;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    flag = kernel_read(filp, buf, (size_t)fsize, &(filp->f_pos));
    set_fs(old_fs);
    filp_close(filp, NULL);
    if (flag < 1)
    {
        printk(KERN_ALERT "<-1>Flag lt 1\n");
        return 1;
    }

    buf[fsize] = '\0';
    printk("<1>The file Content is:\n");
    printk("<1>%s\n", buf);
    kfree(buf);
    printk("<1>read over\n");
    return 0;
}

int __write_file(char *filename, char *data)
{
    struct file *filp;
    mm_segment_t old_fs;
    ssize_t flag;

    if (!data)
    {
        printk(KERN_ALERT "<-1>Data is null\n");
        return 1;
    }

    filp = filp_open(filename, O_RDWR | O_TRUNC | O_CREAT, 0);
    if (IS_ERR(filp))
    {
        printk(KERN_ALERT "<-1>Cannot open %s\n", filename);
        return 1;
    }
    if (!filp)
    {
        printk(KERN_ALERT "<-1>Filp is null\n");
        return 1;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    flag = kernel_write(filp, data, strlen(data), &(filp->f_pos));
    if (flag < 1)
    {
        printk(KERN_ALERT "<-1>Flag lt 1\n");
        set_fs(old_fs);
        filp_close(filp, NULL);
        return 1;
    }
    flag = kernel_write(filp, "\n", sizeof(char), &(filp->f_pos));
    set_fs(old_fs);
    filp_close(filp, NULL);
    if (flag < 1)
    {
        printk(KERN_ALERT "<-1>Flag lt 1\n");
        return 1;
    }

    printk("<1>write over\n");
    return 0;
}

static int __init init_my_mh(void)
{
    char *filename = "/etc/hostname";
    int flag;

    printk("<0>new hostname will be: %s\n", new_hostname);
    flag = __read_file(filename);
    if (flag)
    {
        printk(KERN_ALERT "<-1>Some error happen.Pass read and keep init..\n");
    }
    flag = __write_file(filename, new_hostname);
    if (flag)
    {
        printk(KERN_ALERT "<-1>Some error happen.Give up init..\n");
        return 1;
    }
    return 0;
}

static void __exit exit_my_mh(void)
{
    char *filename = "/etc/hostname";
    int flag;
    flag = __read_file(filename);
    if (flag)
    {
        printk(KERN_ALERT "<-1>Some error happen.Exit..\n");
        return;
    }
    printk("<0>Goodbye\n");
}

module_init(init_my_mh);
module_exit(exit_my_mh);
MODULE_LICENSE("GPL");
