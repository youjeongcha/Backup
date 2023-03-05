#include<stdio.h>
#include<string.h>
#include<conio.h>

int Strcmp(char* str1, char* str2)
{
	int i = 0; //i가 하나만 있어도 분별 가능하다
	while (1)
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
		else if (str1[i] == NULL && str2[i] == NULL) //
			return 0;
		i++;
	}
}

void main()
{
	char str1[10];
	char str2[10];
	printf("(최대 9글자)비교 문자열 입력 : ");
	scanf("%s", str1);
	printf("(최대 9글자)비교 문자열 입력 : ");
	scanf("%s", str2);
	printf("%s == %s = %d", str1, str2, Strcmp(str1, str2));
	getch();
}


