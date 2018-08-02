#include"headers.h"
#include"declarations.h"

extern dev_t Dev_Id;
extern int majorno;
extern int deviceno;
extern struct myDev *myDevices;
extern int mm1;

void __exit MyCharDev_exit(void)
{	
	printk(KERN_INFO  "Exiting driver\n");
	deletemydevices();
	printk(KERN_INFO "All unregistering has been sucessful\n");
}


int deletemydevices()
{
	int i;

	if(mm1 == 1)
	{
		kfree(myDevices->data);
	}

	for( i=0 ; i<deviceno ; i++)
	{
		Dev_Id=MKDEV(majorno,i);
		printk(KERN_INFO "%d\n",Dev_Id);
		cdev_del(&myDevices[i].cdev);
		unregister_chrdev_region(Dev_Id , 1);
		printk(KERN_INFO "unregistering has been done\n");
	}

	kfree(myDevices);
	return 0;
}

module_exit(MyCharDev_exit);
