#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

typedef struct
{
	unsigned long hi,lo;
}TSC;

TSC readTSC()
{
	TSC retVal;

	asm	{
		db 0x0f, 0x31 			// RDTSC
		mov retVal.lo,eax   // read faster low part first
		mov retVal.hi,edx   // then slower high part--> more accure!!
	}

	return retVal;
}

TSC subTSC(TSC left,TSC right)
{
	TSC retVal;

	retVal.hi = left.hi - right.hi;

	if(left.lo < right.lo)
	{
		retVal.lo = 0xffffffff - right.lo;
		retVal.lo += left.lo + 1;
		retVal.hi --;
	}
	else
	{
		retVal.lo = left.lo - right.lo;
	}

	return retVal;
}




TSC addTSC(TSC left,TSC right)
{
	TSC retVal;

	retVal.hi = left.hi + right.hi;
	retVal.lo = left.lo + right.lo;

	asm{
		mov eax,left.lo
		mov	retVal.lo,eax
		mov eax,right.lo
		add retVal.lo,eax
		jnc addTSCnotCarry
	}
	//
	// carry
	//
	retVal.hi++;
addTSCnotCarry:
	return retVal;
}






main()
{
	TSC oldTSC,newTSC;
	unsigned long cpus,i;

	TSC a={0,0},b={0,0};

	printf("\n Wait 2 sec for system shettle down...");
	sleep(2);
	oldTSC = readTSC();
	delay(500);
	newTSC = readTSC();

	printf("\n OLD[%lu][%lu] NEW[%lu][%lu]",
			oldTSC.hi,oldTSC.lo,
			newTSC.hi,newTSC.lo);

	if(oldTSC.hi == newTSC.hi)
	{
		cpus = (newTSC.lo-oldTSC.lo)/500000;
		printf("\n CPUS:[%lu]",cpus);
	}


	oldTSC = readTSC();
	for(i=0;i<1000;i++);
	newTSC = readTSC();

	if(oldTSC.hi == newTSC.hi)
		printf("\n Diff [%lu]",newTSC.lo-oldTSC.lo);



}