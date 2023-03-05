#include <stdio.h>
#include <Windows.h>
#include <time.h>
//clock[] 함수
//응용 프로그램이 실행한 뒤 경과된 시간을 돌려주는 함수 <time.h
//sleep 은 프로그램 자체를 멈춰버려서 시간체크만 가능

#define SEC 1000

int main()
{
	printf("전화 거는중 ☎");
	int oldClock = clock(); //프로그램을 실행한 시점부터 초를 세기 시작한다.
							//clock()으로 리턴을 받아서
	int count = 0; 
	while (count <= 3)
	{
		if (clock() - oldClock >= SEC) //위의 clock보다 무조건 크고 
									   //oldClock이 1이라면 clock()이 1001이 되었을 시점에 실행
		{
			count++;
			printf(".");
			oldClock = clock(); //if문이 실행된 시점으로부터 다시 기준이 되어서
		}
	}
	return 0;
}