#include <stdio.h>
#include <stdlib.h>
#include <time.h> // 시간 값 사용하는 헤더파일
/// 반복문 안에 들어가서 srand 면 비슷한 값이 나올 가능성이 커진다.

void main()
{
	int RNum;
	srand(time(NULL)); //srand시드값 들고온다
	while (1)
	{
		system("cls");
		for (int i = 1; i <= 6; i++)
		{
			RNum = rand();
			printf("%d. %d\n", i, RNum);
			system("pause");
		}
	}
}