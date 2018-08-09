#include "headers.h"
#include "declarations.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAJA SHEKAR");
MODULE_DESCRIPTION("MY CHARACTER DEVICE DRIVER");

dev_t Dev_Id = 0;
int majorno = MAJORNO;
int minorno = 0 ;     // default we will assign 0 as minor number
int deviceno = DEVICE_COUNT;
//volatile int etx_value=0;

struct myDev *myDevices;        
//struct kobject *kobj_ref;
struct proc_dir_entry *proc_entry=NULL;

/*
static ssize_t sysfs_show(struct kobject *kobj,struct kobj_attribute *attr, char *buf)
{
        printk(KERN_INFO "Sysfs - Read!!!\n");
        return sprintf(buf, "%d", etx_value);
}
static ssize_t sysfs_store(struct kobject *kobj,struct kobj_attribute *attr, char *buf, size_t count)
{
        printk(KERN_INFO "Sysfs - Write!!!\n");
        sscanf(buf,"%d",&etx_value);
        return count;
}

struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);

struct kobj_attribute
{
	struct attribute attr;
	size_t (*show)(struct kobject *kobj , struct kobj_attribute *attr , char *buf);
	size_t (*store)(struct kobject *kobj , struct kobj_attribute *attr , const char *buf ,size_t count);
};
*/
static struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.open = openDev,
	.read = readDev,
	.write = writeDev,
};

static int __init MyCharDev_init(void)
{
	int ret , err=0, i;
	printk(KERN_INFO "character device driver init started\n");
	/*
	//This is the old method of  registering of the device

	majorno = register_chrdev(majorno , DEVICE_NAME ,&fops )   //it returns 0 on sucess

	printk(KERN_ALERT "NOT registered\n");
	printk(KERN_INFO "Major NO = %d \n",MAJOR(Dev_Id) );
	 */

	if(alloc_chrdev_region(&Dev_Id , 0 , deviceno , DEVICE_NAME ) < 0)
	{
		return FAIL;
	}

	majorno = MAJOR(Dev_Id);
	minorno = MINOR(Dev_Id);
	printk(KERN_INFO "Major no = %d\tMinor No = %d\n",majorno,minorno);

	myDevices = kmalloc(deviceno*sizeof(struct myDev) , GFP_KERNEL );
	// If No memory is allocated for the device structure
	if(!myDevices)
	{
		ret = -1;
		goto fail;
	}

	memset(myDevices , 0 , deviceno*sizeof(struct myDev) );

//	kobj_ref = kobject_create_add("Mycdevsyfs",kernel_kobj);   // /sys/kernel/Mycdevsyfs will be created

	proc_entry = proc_create(DEVICE_NAME , 0 ,NULL ,&proc_fops);

	if(proc_entry == NULL)
	{	
		ret=-1;
		printk(KERN_INFO "proc creation failed\n");goto fail;
	}
	
	for(i=0 ; i<deviceno ; i++)
	{
		cdev_init(&myDevices[i].cdev , &proc_fops);
		myDevices[i].cdev.ops = &proc_fops;
		Dev_Id = MKDEV(majorno, i);
		err = cdev_add (&myDevices[i].cdev, Dev_Id, 1);

		if (err)
			printk(KERN_NOTICE "Error %d adding scull %d", err, i);
		printk(KERN_INFO "majorno:%d minorno:%d\n",MAJOR(Dev_Id) , MINOR(Dev_Id));
	}

/*	kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);
	if(sysfs_create_file(kobj_ref,&etx_attr.attr))
	{
		printk(KERN_INFO"Cannot create sysfs file......\n");
		goto fail;
	}
*/
	return SUCESS;
fail :
//	kobject_put(kobj_ref); 
//        sysfs_remove_file(kernel_kobj, &etx_attr.attr);	
	deletemydevices();
	return ret;
}

module_init(MyCharDev_init);

