#include <stdio.h>
#include <string.h>
//strcmp 문자열 비교 함수

void main()
{
	char Name1[10] = "ABC";
	char Name2[10] = "BCA";
	char Name3[10] = "ABC";
	printf("Name1 == Name2 : %d\n", strcmp(Name1, Name2)); //다르면 -1 또는 1
	printf("Name1 == Name3 : %d\n", strcmp(Name1, Name3)); //같으면 0
}