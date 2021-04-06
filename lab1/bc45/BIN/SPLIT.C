#include "mem.h"
#include "string.h"
#include "stdio.h"

int split(char *filename,char table[20][256])
{
	int i,j,left,right,tableEntry;

	left=0;right=0;tableEntry=0;

	while(filename[right] != 0)
	{
		if(filename[right] == '/')
		{
			memcpy(table[tableEntry],filename+left,right-left+1);
			table[tableEntry][right - left + 1] = 0;
			tableEntry++;
			right++;
			left = right;
		}
		else
			right++;
	}

	memcpy(table[tableEntry],filename+left,right-left+1);
	table[tableEntry][right - left + 1] = 0;
	tableEntry++;
	//
	// truncate '/' for non-root directories
	//
	for(i=0;i<tableEntry;i++)
	{
		j=strlen(table[i]);

		if( (j != 1) && (table[i][j-1] == '/') )
			table[i][j-1] = 0;
	}

	return tableEntry;
}


main()
{
	char buffer[20][256];
	int i,j;

	j=split("/usr/X11R6/lib/libICE.so.6.3",buffer);

	for(i=0;i<j;i++)
		printf("\n%s",buffer[i]);

    return 0;
}