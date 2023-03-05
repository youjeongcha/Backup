#include <stdio.h>
#include <string.h>
//strcmp : 문자열을 비교해주는 함수
//같으면 0
//1번 문자열이 2번 문자열 보다 더 크면 1 출력
//1번 문자열이 2번 문자열 보다 더 작으면 -1 출력

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