#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowHelp()
{
	puts("Usage");
}

int main (int argc, char * argv[])
{
	if (argc>1)
	{
		if (strcmp(argv[1],"-h")==0)
		{
			Help();
			return 0;
		}
		else 
		{
			puts("Error. Improper parameter.");
			return 0;
		}
	}

	return EXIT_SUCCESS;
}