#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "char_driver"
#define CLASS_NAME  "char_class"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ritesh Jillewad");
MODULE_DESCRIPTION("Custom character device driver for kernel");
MODULE_VERSION("0.1");

static int majorNumber;
static char message[256] = {0};
static size_t size_of_message = 0;
static int numberOfOpens = 0;

static struct class *charClass = NULL;
static struct device *charDevice = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);

static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = dev_open,
  .read = dev_read,
  .write = dev_write,
  .release = dev_release
};


// Like the constructor
static int __init char_init(void)
{
    printk(KERN_INFO "Initializing the custom driver...\n");

    // Register character device driver and obtain a dynamic major number
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);

    if (majorNumber < 0)
    {
        printk(KERN_ALERT "Failed to register major number!\n");
        return majorNumber;
    }

    printk(KERN_INFO "Registered with major number: %d\n", majorNumber);


    /*
    class_create() creates a device class inside /sys/class
    */
    charClass = class_create(CLASS_NAME);

    if (IS_ERR(charClass))
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create class!\n");
        return PTR_ERR(charClass);
    }


    /*
    device_create() creates the device node in /dev
    After this, the device becomes visible as:
    /dev/char_driver
    */
    charDevice = device_create(charClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);

    if (IS_ERR(charDevice))
    {
        class_destroy(charClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create device!\n");
        return PTR_ERR(charDevice);
    }

    printk(KERN_INFO "Device created successfully\n");

    return 0;
}


// This is like destructor
static void __exit char_exit(void)
{
    device_destroy(charClass, MKDEV(majorNumber, 0));
    class_destroy(charClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);

    printk(KERN_INFO "Driver unloaded successfully!\n");
}


// This is the function that will be executed when the user calls open()

/*
We wrote a logic just to count how many times our device opens
*/
static int dev_open(struct inode *inodep, struct file *filep)
{
    numberOfOpens++;

    printk(KERN_INFO "Device opened %d times\n", numberOfOpens);

    return 0;
}


// This is the function that will be executed when the user calls close()
static int dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "Device closed successfully\n");

    return 0;
}


// This is the function that will be called when the user performs write operation
static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset)
{
    if (len > sizeof(message) - 1)
    {
        len = sizeof(message) - 1;
    }

    if (copy_from_user(message, buffer, len) != 0)
    {
        return -EFAULT;
    }

    message[len] = '\0';

    size_of_message = len;

    printk(KERN_INFO "Received %zu characters\n", len);

    return len;
}


// This is the function that will be called when the user performs read operation
static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{

    // This may occur when we first read instead of write
    if (*offset > 0 || size_of_message == 0)
    {
        return 0;
    }

    if (len > size_of_message)
    {
        len = size_of_message;
    }

    if (copy_to_user(buffer, message, len))
    {
        return -EFAULT;
    }

    *offset += len;

    printk(KERN_INFO "Sent %zu characters to user\n", len);

    return len;
}


module_init(char_init);
module_exit(char_exit);
