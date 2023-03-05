#include <stdio.h>
#include <Windows.h>

//Sleep 함수
//응용 프로그램을 Millisecond 단위로 잠시 멈춘다.
//필요 헤더파일 <Windows.h>
int main()
{
	while (1)
	{
		system("cls");
		printf("전화 거는중 ☎");
		for (int i = 0; i < 3; i++)
		{
			Sleep(1000);
			printf(".");
		}
		Sleep(1000);
	}

	return 0;
}