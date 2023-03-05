#include <stdio.h>

void ConvertToUppercase(char* str)
{
	if ((*str) >= 'a' && (*str) <= 'z')
	{
		(*str) -= 32;
	}
}

void main()
{
	char string[] = "string";
	printf("함수 호출 전 = %s\n", string);
	ConvertToUppercase(string);
	printf("함수 호출 후 = %s\n", string);
}