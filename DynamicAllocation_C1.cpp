#include <stdio.h>
#include <stdlib.h>

void main()
{
	int* ptr;
	ptr = (int*)malloc(sizeof(int));

	*ptr = 10;
	printf("%d", *ptr);
	free(ptr);
}