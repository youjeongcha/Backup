#include<stdio.h>
#include<string.h>
void Strcpy(char* str, char* str2)
{
	int i; //i를 밖에 빼서 사용★
	for (i = 0; str2[i] != 0; i++)
		str[i] = str2[i];
	str[i] = 0;
}

void main()
{
	char Name[20];
	char My_Name[20];
	printf("(최대 19글자)이름 입력 : ");
	scanf("%s", My_Name);

	Strcpy(Name, My_Name);
	printf("Name : %s\n", Name);
	printf("My_Name : %s\n", My_Name);
}