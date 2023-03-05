#include <stdio.h>
#include <Windows.h>
#include <time.h>
//clock[] 함수
//응용 프로그램이 실행한 뒤 경과된 시간을 돌려주는 함수 <time.h>
//sleep 은 프로그램 자체를 멈춰버려서 시간체크만 가능

#define SEC 1000
#define MAX_COUNT 3

int main()
{
	printf("전화 거는중 ☎");
	int oldClock = clock();
	int count = 0;
	while (count <= MAX_COUNT)
	{
		if (clock() - oldClock >= SEC)
		{
			count++;
			if (count > MAX_COUNT)
			{
				count = 0;
				system("cls");
				printf("전화 거는중 ☎");
			}
			else
			{
				printf(".");
			}
			oldClock = clock();
		}
	}
}