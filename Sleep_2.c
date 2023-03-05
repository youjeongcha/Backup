#include <stdio.h>
#include <Windows.h>

//Sleep 함수
//응용 프로그램을 Millisecond 단위로 잠시 멈춘다.
//필요 헤더파일 <Windows.h>
int main()
{
	printf("전화 거는중 ☎");
	for (int i = 0; i < 3; i++)
	{
		Sleep(1000); //1000이 1초 500이면 0.5초
		printf(".");
	}
	Sleep(1000); //종료되기 전에도 1초

	return 0;
}