#include<stdio.h>
#include<string.h>

void Strcat(char* str1, char* str2)
{
	int index;
	for (index = 0; str1[index] != 0; index++);//그냥 반복문만 돌려서 null의 인덱스 번호 찾아냄
	for (int i = 0; str2[i] != 0; i++, index++) //추가할 내용 null 앞까지 for문 돌려서 기존 문자열에 추가
		str1[index] = str2[i];
	str1[index] = 0; //반복문 벗어나고 마지막에 null추가
}

void main()
{
	char str1[20], str2[20];
	printf("(최대 19글자)문자열 입력 : ");
	scanf("%s", str1);
	printf("(최대 19글자)추가 문자열 입력 : ");
	scanf("%s", str2);
	Strcat(str1, str2);
	printf("%s\n", str1);
}