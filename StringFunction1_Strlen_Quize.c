#include <stdio.h>
#include <string.h>//���ڿ��� ���ϴ� ������� ������ �� �ֵ��� �����ִ� �Լ�
//�ʿ� ������� = <string.h>

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
	printf("%s ���ڿ��� ���� : %d\n", str, Strlen(str));
}