#include <stdio.h>
#include <string.h>
//strcmp : ���ڿ��� �����ִ� �Լ�
//������ 0
//1�� ���ڿ��� 2�� ���ڿ� ���� �� ũ�� 1 ���
//1�� ���ڿ��� 2�� ���ڿ� ���� �� ������ -1 ���

int Strcmp(char* str1, char* str2)
{
	for (int i = 0, j = 0; str1[i]!= NULL || str2[j] != NULL; i++, j++)
	{
		if (str1[i] > str2[j])
		{
			return 1;
		}
		else if (str1[i] < str2[j])
		{
			return -1;
		}
	}
	return 0;
}

void main()
{
	char str1[10] = "string!!";
	char str2[10] = "string";

	printf("%s == %s : %d\n", str1, str2, Strcmp(str1, str2));
	printf("%s == %s : %d\n", "abc", "abc", Strcmp("abc", "abc"));
	printf("%s == %s : %d\n", "abc", "def", Strcmp("abc", "def"));
}