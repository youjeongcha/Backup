#include<stdio.h>
#include<string.h>

void Strcat(char* str1, char* str2)
{
	int index;
	for (index = 0; str1[index] != 0; index++);//�׳� �ݺ����� ������ null�� �ε��� ��ȣ ã�Ƴ�
	for (int i = 0; str2[i] != 0; i++, index++) //�߰��� ���� null �ձ��� for�� ������ ���� ���ڿ��� �߰�
		str1[index] = str2[i];
	str1[index] = 0; //�ݺ��� ����� �������� null�߰�
}

void main()
{
	char str1[20], str2[20];
	printf("(�ִ� 19����)���ڿ� �Է� : ");
	scanf("%s", str1);
	printf("(�ִ� 19����)�߰� ���ڿ� �Է� : ");
	scanf("%s", str2);
	Strcat(str1, str2);
	printf("%s\n", str1);
}