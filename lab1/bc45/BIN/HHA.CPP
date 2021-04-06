#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include<ctype.h>

void main()
{
	outportb(0x378,0);
	char y;

	clrscr();
	printf("\n---------[ LPT Direct Link ]-----------\n");

	while(1)
	{
		char x;
		for(x=inportb(0x379);(!kbhit()) & ((x&0x80)!=0);x=inportb(0x379));
		y = x>>3;
		outport(0x378,0x10);

		for(x=inportb(0x379);(!kbhit()) & ((x&0x80)==0);x=inportb(0x379));
		x = (x<<1) & 0xf0;
		y=x|y;
		outport(0x378,0);

		putc(y,stdout);

		if(kbhit())
			break;
	}
}