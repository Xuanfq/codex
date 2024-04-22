#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kstrtox.h>


// depend on EXPORT_SYMBOL(xbus); 
extern struct bus_type xbus;

void xdev_release(struct device *dev)
{
    printk("%s-%s\n", __FILE__, __func__);
}

unsigned long id = 0;

// In the show callback function, directly copy the value of the id into buf through the sprintf function.
ssize_t xdev_id_show(struct device *dev, struct device_attribute *attr,
                     char *buf)
{
    return sprintf(buf, "%ld\n", id);
}


/**
 * The store callback function utilizes the kstrtool function.
 * This function has three parameters, the second of which is in decimal format. 
 * Here, we pass in 10, which means that the content in buf will be converted to a decimal number and passed to the id, 
 *   achieving the purpose of modifying the driver through sysfs.
 */
ssize_t xdev_id_store(struct device *dev, struct device_attribute *attr,
                      const char *buf, size_t count)
{
    kstrtoul(buf, 10, &id);
    return count;
}

// The DEVICE_ATTR macro defines xdev_id, 
//   which sets the file permissions to be readable and writable by the file owner, 
//   and non operable by group members and other members
DEVICE_ATTR(xdev_id, S_IRUSR | S_IWUSR, xdev_id_show, xdev_id_store);

static struct device xdev = {
    .init_name = "xdev",
    .bus = &xbus,
    .release = xdev_release,
};

// Register device structure and property file structure
static __init int xdev_init(void)
{
    printk("xdev init\n");
    device_register(&xdev);
    device_create_file(&xdev, &dev_attr_xdev_id);
    return 0;
}
module_init(xdev_init);

// Unregister device structure and property file structure
static __exit void xdev_exit(void)
{
    printk("xdev exit\n");
    device_remove_file(&xdev, &dev_attr_xdev_id);
    device_unregister(&xdev);
}
module_exit(xdev_exit);

MODULE_AUTHOR("Xuanfq");
MODULE_LICENSE("GPL");
