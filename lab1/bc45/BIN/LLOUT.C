#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<string.h>
#include<io.h>

#define LPT_PORT 0x3bc
#define LPT_BUSY 0x80
#define OUTPUT_SYNC 0x10

void LPTinit(void)
{
	outportb(LPT_PORT, 0);
}

void LPTputC(unsigned char c)
{
	int i;
	unsigned char a;

	while(1)
	{
	   a = inportb(LPT_PORT+1);
	   if ((a&LPT_BUSY)!=0)
		   break;
	}

	outportb(LPT_PORT, (c&0xf)|OUTPUT_SYNC);

	while(1)
	{
	  a = inportb(LPT_PORT+1);
	  if ((a&LPT_BUSY)==0)
		 break;
	}

	outportb(LPT_PORT, c>>4);
}


main(int argc,char **argv)
{
	unsigned long i,j,checksum;
	FILE *fp;
	char noChar;

	checksum = 0;

	if(argc != 2)
	{
		printf("\nInvalud argument.");
		exit(0);
	}
	fp = fopen(*(argv+1),"r+b");
	if(fp == NULL)
	{
		printf("\nCannot open file %s",*(argv+1));
		exit(0);
	}
	i=filelength(fileno(fp));
	printf("\nTransfer file name %s in %lu bytes",*(argv+1),i);
	/* output some zero to sync...*/
	LPTinit();
	LPTputC(0);
	LPTputC(0);
	LPTputC(0);
	LPTputC(0);
	/* output 12 bytes as filename */
	noChar = 0;
	for(j=0;j<12;j++)
	{
		unsigned char c = *((*(argv+1)) + j);
		if(  c == NULL)
			noChar = 1;

		if(noChar == 1)
			LPTputC(' ');
		else
			LPTputC(c);
	}
	/* output fileLength */
	LPTputC((i&0x000000ff));
	LPTputC((i&0x0000ff00)>>8);
	LPTputC((i&0x00ff0000)>>16);
	LPTputC((i&0xff000000)>>24);
	printf("\n");
	/* output file */
	for(j=0;j<i;j++)
	{
		char data;

		fread(&data,1,1,fp);
		LPTputC(data);

		checksum = checksum+data;

		if(j % 1024 == 0)
			printf("\r %lu sent",j);
	}
	printf("\r %lu sent",j);
	fclose(fp);
	/* output checksum */
	LPTputC((checksum&0x000000ff));
	LPTputC((checksum&0x0000ff00)>>8);
	LPTputC((checksum&0x00ff0000)>>16);
	LPTputC((checksum&0xff000000)>>24);

	printf("\nTransfer Complete.CheckSum [%lx]",checksum);
}