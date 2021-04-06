#include <stdio.h>
#include <stdlib.h>
#include <time.h>


main()
{
	unsigned long i,j,k;
	time_t start,end;
	unsigned long x,y,z;

	start = time(NULL);


	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000L;j++)
		{
			for(k=0;k<50;k++)
            ;
		//	x = 2;
		//	x += i;
		//	z = 100;
		//	y = x*z*i;
		}
	}

	end = time(NULL);

	printf("\n%f",difftime(end,start));

}