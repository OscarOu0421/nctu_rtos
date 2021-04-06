#include<stdio.h>
#include<stdlib.h>
#include<dos.h>

void main()
{
	outportb(0x378,0);
    printf("asdas");
	while(1)
	{
		char x;

		printf("asas");
		x=inport(0x379);
		x&= 0x78;
		x>>=3;
		printf("\n[%x][%x]",(inportb(0x379)&0x78)>>3,inportb(0x379));
		outport(0x378,0x10);
		printf("\n[%x][%x]",(inportb(0x379)&0x78)>>3,inportb(0x379));
		outport(0x378,0x00);
	}


}