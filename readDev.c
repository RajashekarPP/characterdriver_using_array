#include"headers.h"
#include"declarations.h"

ssize_t readDev(struct file *filep , char __user *buf , size_t count , loff_t *f_pos)
{
	int bytesread=0 , ret;
	struct myDev *device;
	struct myQset *head;
	printk(KERN_INFO "Data read\n");
	device = filep->private_data;
	head = device->data;	
	
	ret = copy_to_user(buf , head->data+bytesread , count);
	if(ret)
	{
		printk(KERN_INFO "Unable to copy data to user\n");
		return -1;
	}
	bytesread += strlen(head->data);
	f_pos += bytesread;
	return bytesread;
}
