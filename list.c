#include <stdio.h>

void main()
{
	char str[5];
	for (int i = 0; i < 5; i++)
	{
		printf("%d��° ���� �� :", i + 1);
		scanf_s("%c", &str[i]);
		//�Է¹��� : scanf�� ���⼭ ��� 
		scanf_s("%*c");
	}
	for (int i = 0; i < 5; i++)
	{
		printf("%c", str[i]);
	}
}