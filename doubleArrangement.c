#include <stdio.h>

int main()
{//컴퓨터에게는 일차원
	//[5][5] Null값 존재 x char[]에만 존재
	//가로 세로(몇묶음)
	int arr[5][5] = { 0 };
	arr[2][-1] = 1;	
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			printf("%d", arr[y][x]);
		}
		printf("\n");
	}
	return 0;
}