#include <stdio.h>
//재귀함수 - 내가 나를 호출한다

void While(int n)
{
	printf("%d\n", n);
	if (n <= 0)
		return;
	else
		While(n - 1);//중괄호 끝이나 리턴을 만나면 함수는 종료된다
	printf("%d\n", n);
}

void main()
{
	While(10);	//해당 함수를 호출하는 시점에 
				//해당 함수가 사용하는 메모리 할당
	return;
}