#include <string.h>
#include <stdio.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>  

#define SEQ_IOC_MAGIC	'D'
#define SEQ_RESET		_IO(SEQ_IOC_MAGIC,0)
#define SEQ_SWCH_MOD		_IO(SEQ_IOC_MAGIC,1)
#define SEQ_CHG_MOD		_IOW(SEQ_IOC_MAGIC,2,1)
#define SEQ_CHG_D		_IOW(SEQ_IOC_MAGIC,3,1)
#define SEQ_GET_D		_IOR(SEQ_IOC_MAGIC,4,1)
#define SEQ_CHG_Q		_IOW(SEQ_IOC_MAGIC,5,1)
#define SEQ_GET_Q		_IOR(SEQ_IOC_MAGIC,6,1)


#define MAX_DEVICE_NAME_LEN 1023
#define MAX_SECRET_LEN 255

int main(int argc, char** argv) 
{
  char device_name[MAX_DEVICE_NAME_LEN+1];
  char secret[MAX_SECRET_LEN+1];
  unsigned max_guesses=0;
  int fd,res,ret;

  if (argc != 2) {
    //fprintf(stderr,"Usage:\n");
    //fprintf(stderr,"hangman_start [device] [secret] [max_guesses]\n");
    return -1;
  }


 /* if (geteuid() != 0)
  {
    fprintf(stderr,"You have to be root to run hangman_start !\n");
    return -1;
  }*/  

  strncpy(device_name,argv[1],MAX_DEVICE_NAME_LEN);
/*
  strncpy(secret,argv[2],MAX_SECRET_LEN);
  if (0 == sscanf(argv[3],"%u",&max_guesses)) {
    fprintf(stderr,"Invalid value for max_guesses\n");
    return -1;
  }*/

  fd = open(device_name,O_RDWR);
  if (fd < 0) {
    perror("Can't open device: ");
    return -1;
  }


  int buf[10];//	= {1,1,1,1,1,1,1,1,1,1};
  unsigned int var = 250;
  write(fd, &var, sizeof(var));  
  read(fd, buf, sizeof(buf));
	int i = 0;
	for(i = 0; i < 10; i++)		printf("the number: %d\n", buf[i]);
 
	printf("*******************************\n");
	res = ioctl(fd,SEQ_CHG_D,4); 
	read(fd, buf, sizeof(buf));
	for(i = 0; i < 10; i++)		printf("the number: %d\n", buf[i]);

	printf("*******************************\n");
	ret = ioctl(fd,SEQ_RESET);	
	printf("the last written value was: %d\n", ret);
	
	printf("*******************************\n");

  int buf1[10] 	= {1,1,1,1,1,1,1,1,1,1};
  var = 100;
  write(fd, &var, sizeof(var));
  read(fd, buf1, sizeof(buf1));
  for(i = 0; i < 10; i++)		printf("the number: %d\n", buf1[i]);
  
printf("*******************************\n");

//seq_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)

	ret = ioctl(fd,SEQ_RESET);	
	printf("the reset curr val: %d\n", ret);

	printf("*******************************\n");

	ioctl(fd,SEQ_SWCH_MOD);
	read(fd, buf1, sizeof(buf1));
	for(i = 0; i < 10; i++)		printf("the number: %d\n", buf1[i]);
	printf("*******************************\n");

	ret = ioctl(fd,SEQ_CHG_Q,10);
	read(fd, buf1, sizeof(buf1));
	for(i = 0; i < 10; i++)		printf("the number: %d\n", buf1[i]);

	printf("*******************************\n");
	
	ret = ioctl(fd,SEQ_GET_Q,10);
	printf("the Q value is: %d\n", ret);
	ret = ioctl(fd,SEQ_GET_D,10);
	printf("the D value is: %d\n", ret);
	
	ret = ioctl(fd,SEQ_CHG_D,300);
	printf("%d\n", errno);
	errno = 0;
	ret = ioctl(fd,SEQ_GET_D,10);
	printf("the D value is: %d\n", ret);
	printf("%d\n", errno);
	errno = 0;

	ret = ioctl(fd,SEQ_CHG_Q,1000);
	printf("%d\n", errno);

  close(fd);
  return 0;
}

