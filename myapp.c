/*
Author 		: Raja shekar J
File Name 	: myapp.c
Description 	: Final application to read and write data from the character driver(MyCharDev)

*/

#include"cheaders.h"

int main()
{
	int choice ,fdr,fdw, mode ;
	static int readmode , writemode ,writtendata;
	char writebuf[100] = "hello raja thanks for the compliment";
	char readbuf[100]={0}; //making th buffer to be empty

	while(1)
	{
		puts(" enter your choice");
		puts(" 1.open\n 2.read\n 3.write\n 4.close\n 5.exit");
		__fpurge(stdin);
		scanf("%d",&choice);
		switch(choice)
		{
			case 1 :
				puts("In which mode should I open the file");
				puts("enter 1. Read_Mode 2. Write_Mode ");
				__fpurge(stdin);
				scanf("%d",&mode);
				switch(mode)
				{
					case 1:fdr = open("./MyCharDev" , O_RDONLY );
					       perror("open read");
					       printf("%d\n",fdr);
					       readmode = 1;
					       break;
					case 2:fdw = open("./MyCharDev" , O_WRONLY);
					       perror("open write");
					       printf("%d\n",fdw);
					       writemode = 1;
					       break;
					default : puts("Invalid choice file not opened");
				}
				break;
			case 2 :
				if(writtendata == 0)
				{
					puts("No data is written to read form driver");break;
				}
				if( (readmode == 1) && (fdr >0))
				{
					if(read(fdr , readbuf , 100) < 0)
					{	
						puts("unable to read data");break;
					}
					printf("msg read is \n%s\n",readbuf);
				}
				else
				{
					puts("file not opened in readmode");
				}
				break;
			case 3 :
				if( (writemode == 1) && (fdw >0))
				{	
					int byteswritten=0;
					byteswritten = write(fdw , writebuf , strlen(writebuf));
					if(byteswritten < 0)
					{
						puts("unable to write data");break;
					}
					puts("msg has been written");
					writtendata = 1;
				}
				else
				{
					puts("file not opened in writemode");
				}				
				break;
			case 4:
				close(fdr);
				close(fdw);
				printf("closed file fdr = %d\n closed file fdw = %d\n",fdr,fdw);
				readmode=writemode=0;
				break;
			case 5:
				puts("exiting from process");
				exit(0);
			default : puts("Invalid choice"); break;

		}//end of switch case
	}//end of while loop
}//end of main
