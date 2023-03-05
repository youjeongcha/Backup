//STL:Standard Template Library
//Container : STL 자료구조 라이브러리
//확장명.cpp로 사용

//Container만 C언어로 이용

//.h 붙으면 c 안붙으면 c++
//스택 라이브러리
#include<stdio.h>
#include<stack>

void main()
{
	std::stack<int> iStack; //<자료형>
	for (int i = 1; i <= 5; i++)
	{
		iStack.push(i);
		printf("Top : %d\n", iStack.top());
	}

	printf("\nsize : %d\n\n", iStack.size());

	while (!iStack.empty())//안비어 있을 때 돌리는 거
	{
		printf("Top : %d\n", iStack.top());
		iStack.pop();
	}
}