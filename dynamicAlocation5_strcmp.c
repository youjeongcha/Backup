#include <stdio.h>
#include <string.h>
//strcmp ���ڿ� �� �Լ�

void main()
{
	char Name1[10] = "ABC";
	char Name2[10] = "BCA";
	char Name3[10] = "ABC";
	printf("Name1 == Name2 : %d\n", strcmp(Name1, Name2)); //�ٸ��� -1 �Ǵ� 1
	printf("Name1 == Name3 : %d\n", strcmp(Name1, Name3)); //������ 0
}