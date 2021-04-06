#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

setTimer(int timer,unsigned count,int mode)
{
	unsigned char data;

	data = timer << 6;
	data |= 0x30;
	mode <<= 1;
	data |= (unsigned char)mode;

	outportb(0x43,data);

	outportb(0x40+timer,(unsigned char)(count & 0x00ff));
	outportb(0x40+timer,(unsigned char)(count >> 8));
} 

unsigned readTimer(int timer)
{
	unsigned char data;
	unsigned retVal1,retVal2;
	int i;

	data = 2<<timer;
	data |= 0xd0;
	outportb(0x43,data);

	retVal1 = inport(0x40+timer);
	retVal2 = inport(0x40+timer);
	retVal2 <<= 8;
	retVal2 |= retVal1;

	data = 2<<timer;
	data |= 0xf0;
	outportb(0x43,data);

	return retVal2;
}

main()
{
	unsigned long x,i;

	clrscr();

	setTimer(2,0xffff,4);


	for(i=0;i<=10;i++)
	{
		x=readTimer(2);

		printf("\n %luth peek: %lu",i,x);

		for(x=0;x<1000L;x++)
		{
			x+=20;
			x-=20;
		}
	}
}