#include <stdio.h>

void main()
{
	char buf[40];
	int age = 20;
	char Name[10] = "차유정";
	sprintf(buf, "%s님의 나이는 %d살입니다.", Name, age);
	//sprintf와 printf의 차이점
	//sprintf 조합후 문자열 저장
	printf("%s", buf);

}