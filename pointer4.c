#include<stdio.h>

void main()
{
	int arr[5] = { 10,20,30,40,50 };
	for (int i = 0; i < 5; i++)
	{
		printf("배열원소[%d]의 주소 = %p, 배열원소[%d]의 값 = %d,", i, &arr[i], i, arr[i]);
	}
	printf("\n\n");
	for (int i = 0; i < 5; i++)
	{
		printf("배열원소[%d]의 주소 = %p, 배열원소[%d]의 값 = %d,", i, arr + i, i, *(arr + i));
	}
}