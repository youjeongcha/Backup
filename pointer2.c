#include <stdio.h>

void main()
{
	int Num = 10, * pNum;
	//int는 4바이트 4개의 메모리 맨 처음이 대표 주소
	char Ch = 'a', * pCh;

	pNum = &Num;
	pCh = &Ch;

	printf("pCh-1 = %p번지 pCh = %p번지 pCh+1 = %p번지\n", pCh - 1, pCh, pCh + 1);
	printf("Num-1 = %p번지 Num = %p번지 Num+1 = %p 번지\n", pNum -1, pNum, pNum + 1);
	//자료형의 크기만큼 빠지거나 더해진다
}