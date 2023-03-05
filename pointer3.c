#include <stdio.h>

void main()
{
	int Num = 10, * pNum;
	//int는 4바이트 4개의 메모리 맨 처음이 대표 주소
	char Ch = 'a', * pCh;

	pNum = &Num;
	pCh = &Ch;

	printf("char 자료형의 크기 = %d\n", sizeof(Ch));//단일문자 1바이트
	printf("int 자료형의 크기 = %d\n", sizeof(Num));
	printf("char* 자료형의 크기 = %d\n", sizeof(pCh));//주소를 표현하려면 4바이트라서
	printf("int* 자료형의 크기 = %d\n", sizeof(pNum));
}

///
//배열의 이름이 주소를 저장한다.
//포인터 주소를 활용하는게 배열
//
//일차원배열
//이차원배열 묶음 기준이 필요하기 때문에 뒤 괄호 입력 받음
//
//주소를 통해 연산으로 접근하기때문에 시작이 0