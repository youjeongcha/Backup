#include <stdio.h>

void main()
{
	char str[5];
	for (int i = 0; i < 5; i++)
	{
		printf("%d번째 원소 값 :", i + 1);
		scanf_s("%c", &str[i]);
		//입력버퍼 : scanf는 여기서 들고감 
		scanf_s("%*c");
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%c", str[i]);
	}
}