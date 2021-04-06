#include<stdio.h>
#include<stdlib.h>
#include<io.h>
#include<dos.h>
#include<conio.h>

#define LPT_PORT 0x378 /* this is LPT's base address. 3b7,3f7 are all possible. */
#define LPT_BUSY  0x80
#define OUTPUT_SYNC 0x10

void LPTinit(void)
{
	outportb(LPT_PORT, 0);
}

unsigned char LPTgetC(void)
{
	/*
	//
	// main concept is: we got 2 register,say,378 and 379.
	//
	//	378 : outpot     	378 : output
	//			X
	//	379 : input		379 : input
	//      ---------------        ------------------
	//
	// every write to host's 378 can be read from remote's 379.
	// and the format is:
	//
	//  378(host)                            379(remote)
	//   +-------------+-------+-------+      +----------+-------+---+
	//   |don't care(3)|SYNC(1)|DATA(4)|  ==> |!(SYNC(1))|DATA(4)|111|
	//   +-------------+-------+-------+      +----------+-------+---+
	//
	// sync bit is used to sync remote and host.
	//
	*/

	unsigned char a,b,c;
	int d;

	while(1)
	{
	   while(1)
	   {
		/* double read and compare to ensure data is correct */
		a = inportb(LPT_PORT+1);
		for(d=0;d<10;d++);
		b = inportb(LPT_PORT+1);
		if(a==b)
			break;
	   }

	   if ((a&LPT_BUSY)==0)
		   break;
	}
	outportb(LPT_PORT,0x10);
	c = (a>>3) & 0x0f;

	while(1)
	{
	   while(1)
	   {
		a = inportb(LPT_PORT+1);
		for(d=0;d<10;d++);
		b = inportb(LPT_PORT+1);
		if(a==b)
			break;
	   }

	  if ((a&LPT_BUSY)!=0)
		 break;
	}
	outportb(LPT_PORT, 0);
	c |= (a<<1)&0xf0;

	return c;
}
void main()
{
	char data;
	unsigned long dataSize,i,j,checksum,remoteChecksum;
	FILE *fp;
	char fileName[20];

	checksum = 0;

	/*
	//
	// wait for 12 character file name(before that,many zero will be
	// received to sync)
	//
	*/
	LPTinit();
	while((data = LPTgetC()) == 0);

	fileName[0] = data;
	for(i=1;i<12;i++)
		fileName[i] = LPTgetC();

	fileName[12] = 0;

	fp = fopen(fileName,"w+b");
	if(fp == NULL)
	{
		printf("\n Cannot open file");
		exit(0);
	}
	/*
	//
	// receive 4 bytes as file length
	//
	*/
	dataSize = 0;
	dataSize = LPTgetC();
	dataSize |= ((unsigned long)(LPTgetC()))<<8;
	dataSize |= ((unsigned long)(LPTgetC()))<<16;
	dataSize |= ((unsigned long)(LPTgetC()))<<24;

	printf("\n Starting receiving file %s in bytes %lu\n",fileName,dataSize);
	for(i=0;i<dataSize;i++)
	{
		char c;

		c=LPTgetC();
		fwrite(&c,1,1,fp);
		checksum = checksum + c;
		if(i % 1024 == 0)
			printf("\r%lu bytes received",i);
	}
	printf("\r%lu bytes received",i);
	/*
	//
	// receive 4 bytes as remote checksum and compare them
	//
	*/
	remoteChecksum = 0;
	remoteChecksum = LPTgetC();
	remoteChecksum |= ((unsigned long)(LPTgetC()))<<8;
	remoteChecksum |= ((unsigned long)(LPTgetC()))<<16;
	remoteChecksum |= ((unsigned long)(LPTgetC()))<<24;

	if(remoteChecksum == checksum)
		printf("\n Transfer Complete.Checksum: remote [%lx],local [%lx]",checksum,remoteChecksum);
	else
		printf("\n Checksum error! File is not usable!");

	fclose(fp);
}
