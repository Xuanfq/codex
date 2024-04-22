#include <linux/module.h> 
#include <linux/init.h>   // init&exit相关宏
#include <linux/kernel.h>

// develop base kernel 6.5.0-28-generic


static int __init hello_init(void)
{
      printk(KERN_WARNING "hello world.\n");
      return 0;
}
static void __exit hello_exit(void)
{
      printk(KERN_WARNING "hello exit!\n");
}
 

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xuanfq");
MODULE_DESCRIPTION("hello world module");
 
