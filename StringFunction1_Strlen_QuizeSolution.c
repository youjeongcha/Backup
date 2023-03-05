#include<stdio.h>
#include<string.h>

int Strlen(char* str)
{
	int i;
	for (i = 0; str[i] != 0; i++); //널이 아닌동안 계속 반복
	return i;
}

void main()
{
	char str[20];
	printf("(최대 19글자)문자열 입력 : ");
	scanf("%s", str);
	printf("%s문자열의 길이 : %d", str, Strlen(str));
}