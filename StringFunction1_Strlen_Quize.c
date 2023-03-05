#include <stdio.h>
#include <string.h>//문자열을 원하는 방법으로 제어할 수 있도록 도와주는 함수
//필요 헤더파일 = <string.h>

int Strlen(char str[])
{
	int len = 0;
	while(1)
	{
		len++;
		if (str[len] == NULL)
		{
			return len;
		}
	}
}

void main()
{
	char str[10] = "Hello";
	printf("%s 문자열의 길이 : %d\n", str, Strlen(str));
}