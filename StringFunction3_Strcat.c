//문자열 함수 
//Strcat 문자열을 추가해주는 함수
#include <stdio.h>
#include <string.h>

void main()
{
	char str[10] = "Hello";
	printf("%s\n", str);
	strcat(str, "^^");
	printf("%s\n", str);
}