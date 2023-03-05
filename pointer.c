#include <stdio.h>

void main()
{
	int Num;
	int *pNum = &Num;
	*pNum = 10;
	//* 2가지 의미 변수명 뒤에 붙이면 포인터 선언
	//있는 변수 앞에 붙이면 해당 변수의 주소에 들어가는 값을 설정
	printf("Num의 주소 = %p\n", &Num);
	printf("pNum이 가지고 있는 값 =  %p\n", pNum);
	printf("Num = %d\n", Num);
	printf("pNum =  %d\n", *pNum);
	printf("pNum의 주소 =  %p\n", &pNum);

}