#include <stdio.h>
#include <stdlib.h>
//rand는 cpu에서 랜덤수 기준값을 가져오기 때문에 모든 컴퓨터에서 같이, 다시 실행해도 같은 수가.
void main()
{
	int RNum;
	while (1)
	{
		system("cls");
		for (int i = 1; i <= 6; i++)
		{
			RNum = rand();
			printf("%d. %d\n", i, RNum);
		}
		system("pause");
	}
}