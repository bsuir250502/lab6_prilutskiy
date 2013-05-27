#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Help()
{
	puts("Usage");
	puts("1. Type numbers to write into text file\n2. Type numbers to write into binary file\n3. Press {2} to delete repeating numbers from binary file\n");
}

void GetString(char * string)
{
	fgets(string,20,stdin);
}

int GetInt(int * number)
{
	char buffer[20];
	fgets(buffer,20,stdin);
	*number = atoi(buffer);
	return strlen(buffer)>5?0:1;
}

void CreateFiles(FILE * txtHandle, FILE * binaryHandle, int * txt_numbers, int * bin_numbers)
{
	//text
	txtHandle = fopen("text_file.txt","w+");
	int inp = -2;
	while (1)
	{
		puts("Type numbers to write in text file (-1 for interruption):");
		if (!GetInt(&inp))
		{
			puts("Input error. Try again");
			continue;
		}
		if (inp == -1)
			break;
		fprintf(txtHandle, "%d ", inp);
		(*txt_numbers)++;
	}
	fclose(txtHandle);
	//binary
	binaryHandle = fopen("bin_file.bin","w+b");
	while (1)
	{
		puts("Type numbers to write in binary file (-1 for interruption):");
		if (!GetInt(&inp))
		{
			puts("Input error. Try again");
			continue;
		}
		if (inp == -1)
			break;
		fwrite(&inp, sizeof(int), 1, binaryHandle);
		(*bin_numbers)++;
	}
	fclose(binaryHandle);
}

void PerformDelete(int * bin_array, int  * bin_length, int * text_array, int * text_length)
{
	for (int i = 0; i < (*text_length); i++)
		for (int j = 0; j < (*bin_length); j++)
			if (text_array[i] == bin_array[j])
			{
				for (int k = j; k < (*bin_length) - 1; k++)
					bin_array[k] = bin_array[k + 1];
				(*bin_length)--;
			}
}

void DeleteOperations(FILE * txtHandle, FILE * binaryHandle, int txt_numbers, int bin_numbers)
{
	//reading from txt
	txtHandle = fopen("text_file.txt", "r");
	int * text_array = (int *)calloc(txt_numbers, sizeof(int));
	for (int i = 0; i < txt_numbers; i++)
	{
		fscanf(txtHandle, "%d", &text_array[i]);
		if (feof(txtHandle))
			break;
	}
	fclose(txtHandle);
	//reading from binary
	binaryHandle = fopen("bin_file.bin", "rb");
	int * bin_array = (int *)calloc(bin_numbers, sizeof(int));
	for (int i = 0; i < bin_numbers; i++)
	{
		fread(&bin_array[i], sizeof(int), 1, binaryHandle);
		if (feof(binaryHandle))
			break;
	}
	fclose(binaryHandle);
	puts("Initial text file:");
	for (int i = 0; i< txt_numbers; i++)
		printf("%d ", text_array[i]);
	puts("");
	puts("Initial binary file:");
	for (int i = 0; i< bin_numbers; i++)
		printf("%d ", bin_array[i]);
	puts("");

	PerformDelete(bin_array, &bin_numbers, text_array, &txt_numbers);
	puts("Final binary file:");
	for (int i = 0; i < bin_numbers; i++)
		printf("%d ", bin_array[i]);
	puts("");
	binaryHandle = fopen("bin_file.bin", "w+b");
	for (int i = 0; i < bin_numbers; i++)		
		fwrite(&bin_array[i], sizeof(int), 1, binaryHandle);
	fclose(binaryHandle);
	free(text_array);
	free(bin_array);
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
	FILE * binFile = NULL, * txtFile = NULL;
	int bin_numbers = 0;
	int txt_numbers = 0;
	while (1)
	{
		puts("1 - Create both files\n2 - Perform delete operations\n0 - Exit");
		int inp; if (!GetInt(&inp)) 
		{
			puts("Input error. Try again");
			continue;
		}
		switch (inp)
		{
			default:
			puts("Input error. Try again");
			continue;
			case 0:
			return EXIT_SUCCESS;
			case 1: 
			CreateFiles(txtFile, binFile, &txt_numbers, &bin_numbers);
			break;
			case 2:
			DeleteOperations(binFile, txtFile, txt_numbers, bin_numbers);
			break;
		}
	}
}