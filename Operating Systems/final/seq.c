#include <linux/ctype.h>
#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>  	
#include <linux/slab.h>
#include <linux/fs.h>       		
#include <linux/errno.h>  
#include <linux/types.h> 
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#include "seq.h"

#define MY_MODULE "seq"

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "SMM" );

int seq_open( struct inode *inode, struct file *filp );
int seq_release( struct inode *inode, struct file *filp );
ssize_t seq_read( struct file *filp, char *buf, size_t count, loff_t *f_pos );
ssize_t seq_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
int seq_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);
loff_t seq_llseek (struct file *, loff_t, int);

 
int seq_devices = 0;
MODULE_PARM( seq_devices, "i" );

/* globals */
int my_major = 0; 			/* will hold the major # of my device driver */


//<sequence_device>
#define MOD_NUM 256

typedef int SeqType;

typedef struct SeqDevice{
	int cur_val;
	int d;
	int q;
	int last_written_cur_val;
	SeqType type;
} SeqDevice;

struct file_operations seq_fops = {
	.open=		seq_open,
	.release=	seq_release,
	.read=		seq_read,
	.write=		seq_write,
	.llseek=	seq_llseek,
	.ioctl=		seq_ioctl,
	.owner=		THIS_MODULE,
};
//</sequence_device>


int init_module( void ) 
{
	my_major = register_chrdev( my_major, MY_MODULE, &seq_fops );
	if( my_major < 0 ) 
	{
		printk( KERN_WARNING "can't get dynamic major\n" );
		return my_major;
	}
	
	SET_MODULE_OWNER(&seq_fops);

	return 0;
}


void cleanup_module( void )
{
	
	unregister_chrdev( my_major, MY_MODULE);

    //do clean_up();

	return;
}


int seq_open( struct inode *inode, struct file *filp ) 
{	
	SeqDevice* seq_device;
/*	
	if ( MINOR(inode->i_rdev) >= 0 && MINOR(inode->i_rdev) <= 255)
	{
		return -ENODEV;
	}
*/
	filp->private_data = (void*)kmalloc(sizeof(SeqDevice), GFP_KERNEL);
	
	seq_device = ((SeqDevice*)(filp->private_data));

	seq_device->cur_val					= 0;
	seq_device->d						= 1;
	seq_device->q						= 2;
	seq_device->last_written_cur_val	= 0;	//for IOCTL function
	seq_device->type					= ARITH_MODE;
	
	return 0;
}


int seq_release( struct inode *inode, struct file *filp ) 
{	
	kfree(filp->private_data);

	return 0;
}


ssize_t seq_read( struct file *filp, char *buf, size_t sz, loff_t *f_pos ) 
{
	SeqDevice* seq_device = ((SeqDevice*)(filp->private_data));
	int i;

	//<read>
	int* read_array = (int*) kmalloc(sz, GFP_KERNEL);

	for (i = 0 ; i < sz/sizeof(int); i++)
	{
		read_array[i] = seq_device->cur_val;

		if(seq_device->type == ARITH_MODE)
		{
			seq_device->cur_val =  (seq_device->cur_val + seq_device->d) % MOD_NUM;
		}
		else if(seq_device->type == GEOM_MODE)
		{	
			seq_device->cur_val = (seq_device->q * seq_device->cur_val) % MOD_NUM;
		}
	}
	kfree(read_array);
	//</read>
	
	int cp_result = copy_to_user(buf, read_array, sz);
	if(cp_result < 0)
	{
		return -EFAULT;
	}
   
	return sz;
}


ssize_t seq_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos) 
{    
	unsigned int new_cur_val = 0;
	SeqDevice* seq_device = ((SeqDevice*)(filp->private_data));

	
	if(count != 4)
	{
		return -EINVAL;
	}

	int result = copy_from_user(&new_cur_val, buf, sizeof(new_cur_val));
	if(result < 0)
	{
		return -EFAULT;
	}
	
	//<write>	
	seq_device->cur_val				 		 = new_cur_val % MOD_NUM;
	seq_device->last_written_cur_val 		 = new_cur_val % MOD_NUM;
	//</write>

    return sizeof(buf);
}


int seq_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg) 
{
	SeqDevice* seq_device = ((SeqDevice*)(filp->private_data));

	switch( cmd ) 
	{
		case SEQ_RESET:
			seq_device->cur_val =  seq_device->last_written_cur_val;
			return seq_device->cur_val;
			break;
	
		case SEQ_SWCH_MOD:
			if(seq_device->type == ARITH_MODE) seq_device->type = GEOM_MODE;
			else if(seq_device->type == GEOM_MODE) seq_device->type = ARITH_MODE;
			break;

		case SEQ_CHG_MOD:
			if(arg != 1 && arg != 2) return -1;
			seq_device->type = arg;
			break;
		
		case SEQ_CHG_D:
			if(arg < 0 || arg > 255) return -1;
			seq_device->d = arg;
			break;
			
		case SEQ_GET_D:
			return seq_device->d;
			break;
		
		case SEQ_CHG_Q:
			if(arg < 0 || arg > 255) return -1;
			seq_device->q = arg;
			break;
			
		case SEQ_GET_Q:
			return seq_device->q;
			break;
			
		default: return -ENOTTY;
	}
	return 0;
}


loff_t seq_llseek (struct file * barham, loff_t zoabi, int mansour)
{
	return -ENOSYS;
}
