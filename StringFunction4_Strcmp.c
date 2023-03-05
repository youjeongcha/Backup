#include <stdio.h>
#include <string.h>
//strcmp : 문자열을 비교해주는 함수

//대소관계 비교해서 다른 인자가 나왔을 때
//(1) str1 < str2 인 경우에는 음수 1 반환
//(2) str1 > str2 인 경우에는 양수 1 반환
//(3) str1 == str2 인 경우에는 0을 반환 합니다.

void main()
{
	char str1[10] = "string!!";
	char str2[10] = "string";

	printf("%s == %s : %d\n", str1, str2, strcmp(str1, str2));
	printf("%s == %s : %d\n", "abc", "abc", strcmp("abc", "abc")); 
	printf("%s == %s : %d\n", "abc", "def", strcmp("abc", "def"));
}