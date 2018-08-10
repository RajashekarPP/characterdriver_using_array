#include"cheaders.h"

int main(int argc , char **argv)
{
	int fd , bytes;
	char buf[100]= "hello raja welcome" , rbuf[100];
	printf("entering main function\n");
	puts("opening the file");
	fd = open("./MyCharDev",O_WRONLY);
	perror("open");
	printf("fd = %d\n",fd);
	puts("data is written");
	write(fd , buf , strlen(buf));
	close(fd);
	sleep(1);
	fd = open("./MyCharDev",O_RDONLY);
	perror("open");
	printf("fd = %d\n",fd);
	//read(fd, rbuf ,100);
	read(fd, rbuf ,10);
	close(fd);
	puts("Data read is");
	printf("%s\n",rbuf);
	strcpy(buf , "Path Partner wishes u good luck");
	puts("********* opening the file again *******");
	fd = open("./MyCharDev",O_WRONLY);
	perror("open");
	printf("fd = %d\n",fd);
	puts("data is written");
	write(fd , buf , strlen(buf));
	close(fd);
	sleep(1);
	fd = open("./MyCharDev",O_RDONLY);
	printf("fd = %d\n",fd);
	read(fd, rbuf ,100);
	close(fd);
	puts("Data read is");
	printf("%s\n",rbuf);
	
	return 0;
}
