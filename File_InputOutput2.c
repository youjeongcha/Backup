#include<stdio.h>
//fprintf "a" 옵션
void main()
{
	//FILE* f = fopen("c:\\test\\Test.txt", "a"); 드라이브 자체가 다른 경우
	FILE* f = fopen("Test.txt", "a");
	int Num = 123;
	fprintf(f, "추가 모드 %d", Num);
	fclose(f);

	//경로가 다를 시에는 
}