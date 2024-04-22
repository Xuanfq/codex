#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>


extern struct bus_type xbus;

char *name = "xdrv";

// Ensure that the prefix of the store and show functions is consistent with the driver properties file, 
//   and that the prefix of drvname_show() is consistent with drvname
ssize_t drvname_show(struct device_driver *drv, char *buf)
{
    return sprintf(buf, "%s\n", name);
}

//DRIVER_ATTR_RO defines a drvname property file
DRIVER_ATTR_RO(drvname);

int xdrv_probe(struct device *dev)
{
    printk("%s-%s\n", __FILE__, __func__);
    return 0;
}

int xdrv_remove(struct device *dev)
{
    printk("%s-%s\n", __FILE__, __func__);
    return 0;
}

// A driver structure xdrv has been defined, 
//   and the name must be the same as the device name, 
//   otherwise it cannot be successfully matched
static struct device_driver xdrv = {
    .name = "xdev",
    // The driver is mounted on a registered bus xbus.
    .bus = &xbus,
    // After the driver and device are successfully matched, the probe function of the driver will be executed
    .probe = xdrv_probe,
    // When logging out the driver, it is necessary to disable certain functions of the physical device, etc
    .remove = xdrv_remove,
};

// Register our driver and driver properties file by calling 
//   the driver_register function and driveer_create_file function
static __init int xdrv_init(void)
{
    printk("xdrv init\n");
    driver_register(&xdrv);
    driver_create_file(&xdrv, &driver_attr_drvname);
    return 0;
}

module_init(xdrv_init);

// Unregister drivers and driver attribute files
static __exit void xdrv_exit(void)
{
    printk("xdrv exit\n");
    driver_remove_file(&xdrv, &driver_attr_drvname);
    driver_unregister(&xdrv);
}

module_exit(xdrv_exit);

MODULE_AUTHOR("Xuanfq");
MODULE_LICENSE("GPL");