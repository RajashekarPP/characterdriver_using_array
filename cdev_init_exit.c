#include"headers.h"
#include"declarations.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJA SHEKAR");
MODULE_DESCRIPTION("cdev in simple way"):

extern int mm1;
extern int device_count;
static struct file_operations	 fops =
					{
					open:opendev;
					read:readdev;
					write:writedev;
					};
int majorno = 0;
int minorno = 0;
dev_t dev_id = 0 ;
int device_count = DEVICE_COUNT;

static __init cdev_init(void)
{
	struct myDev *mydevices;
	struct myQset *qset;
	int i ,err ;
	printk(KERN_INFO "Init func started\n");

	if(alloc_chrdev_region(&dev_id , majorno , device_count , &fops) <0)
	{
		printk(KERN_INFO "allocation of dev_id failed\n");
		return FAIL;
	}

	majorno = MAJOR(dev_id);
	minorno = MINOR(dev_id);

	printk( KERN_INFO  "majorno = %d\t minorno = %d\n ",majorno , minorno );
	mydevices = kmalloc ( device_count*sizeof(struct(myDev)) ,  GFP_KERNEL);
	if(!mydevices)
	{
		printk(KERN_INFO "memory allocation failed\n");
		goto end;
	}

	memset(mydevices , 0 , sizeof(struct myDev)*device_count);

	for ( i=0 ;i<device_count ; i++)
	{
		cdev_init(&mydevices[i].cdev ,&fops);
		mydevices[i].cdev.ops = &fops;
		dev_id = MKDEV(majorno , i);
		err = cdev_add(&mydevices[i].cedv , dev_id , 1);

		if(err)
		{
			printk(KERN_INFO "error in adding scull %d\n",i);
		}
		printk(KERN_INFO "majorno = %ld minorno = %ld \n",MAJOR(dev_id) , MINOR(dev_id) );
	}

	printk(KERN_INFO "init func ended\n");
	return SUCESS;
end :
	deletemydevices();
	return FAIL;
}


void __exit cdev_exit(void)
{
	printk(KERN_INFO "Exit func started\n");
	deletemydevices();
	printk(KERN_INFO "Exiting exit\n");

}

int deletemydevices()
{
	int i;
	struct myQset *head;
	head =  mydevices->head;
	if( 1 == mm1)
	{
		kfree(head->data);
		kfree(mydevices->data);	
	}
	for(i=0; i<device_count ; i++)
	{
		dev_id = MKDEV(majorno , i);
		printk(KERN_INFO "delete %ld\n" , dev_id);
		cdev_del(&mydevices[i].cdev);
		uregister_chrdev_region(dev_id , 1);  // 1 indicates no of devices to be unregistered		
		printk(KERN_INFO "unregistering has been done \n");
	}
	kfree(mydevices);
	return SUCESS;
}


module_init(cdev_init);
module_exit(cdev_exit);
