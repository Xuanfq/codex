/* xbus.c */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>


// The function is responsible for device and driver matching under the bus
int xbus_match(struct device *dev, struct device_driver *drv)
{
    printk("%s-%s\n", __FILE__, __func__);
    if (!strncmp(dev_name(dev), drv->name, strlen(drv->name)))
    {
        printk("dev & drv match\n");
        return 1;
    }
    return 0;
}

// Defined a busname variable that stores the name of the bus
static char *bus_name = "xbus";

// Provide a show callback function so that users can query the name of the bus through the `cat` command
ssize_t xbus_test_show(const struct bus_type *bus, char *buf)
{
    return sprintf(buf, "%s\n", bus_name);
}
// Set the file permissions for this file to be readable by the file owner
BUS_ATTR_RO(xbus_test);

// A new bus named xbus has been defined, and the most important member of the bus structure is the match callback function
static struct bus_type xbus = {
    .name = "xbus",
    .match = &xbus_match,
};
// EXPORT_SYMBOL(xbus);  // only cancle comment while building in linux kernel module

// Register Bus
static __init int xbus_init(void)
{
    printk("xbus init\n");

    bus_register(&xbus);
    bus_create_file(&xbus, &bus_attr_xbus_test);
    return 0;
}
module_init(xbus_init);

// Unregister Bus
static __exit void xbus_exit(void)
{
    printk("xbus exit\n");
    bus_remove_file(&xbus, &bus_attr_xbus_test);
    bus_unregister(&xbus);
}
module_exit(xbus_exit);

MODULE_AUTHOR("Xuanfq");
MODULE_LICENSE("GPL");

/*
root@dev-server:/sys/bus/xbus# ll
total 0
drwxr-xr-x  4 root root    0 Apr 20 22:07 ./
drwxr-xr-x 54 root root    0 Apr 20 10:09 ../
drwxr-xr-x  2 root root    0 Apr 20 22:08 devices/
drwxr-xr-x  2 root root    0 Apr 20 22:08 drivers/
-rw-r--r--  1 root root 4096 Apr 20 22:08 drivers_autoprobe
--w-------  1 root root 4096 Apr 20 22:08 drivers_probe
--w-------  1 root root 4096 Apr 20 22:07 uevent
-r--r--r--  1 root root 4096 Apr 20 22:08 xbus_test
root@dev-server:/sys/bus/xbus#
*/
