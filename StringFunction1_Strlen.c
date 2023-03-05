//문자열 함수
//Strlen

#include <stdio.h>
#include <string.h>

void main()
{
	char str[10] = "Hello";
	printf("%s 문자열의 길이 : %d\n", str, strlen(str)); //시작주소롤 str을 보내서 NULL이 나올때까지
}