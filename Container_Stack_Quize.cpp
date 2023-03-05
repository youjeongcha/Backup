//STL:Standard Template Library
//Container : STL 자료구조 라이브러리

#include<stdio.h>
#include<stack>

int Manu()
{
	int input;
	printf("====Stack System====\n");
	printf("1. Push\n");
	printf("2. Pop\n");
	printf("3. Exit\n");
	printf("====================\n");
	printf("입력 : ");
	scanf("%d", &input);
	return input;
}
//다음 주소를 연결하는 구조체나 동적할당 필요X
//stack에서 전부 이루어진다
void main()
{
	std::stack<int> iStack; //<자료형> 메인 안에 선언
	//int count = 0;
	int input;

	while (true)
	{
		switch (Manu())
		{
		case 1:
			printf("Push : ");
			scanf("%d", &input);
			iStack.push(input);
			//printf("Top : %d\n", iStack.top());
			break;
		case 2:
			if (iStack.empty())
			{
				printf("삭제할 데이터가 없습니다.\n");
				break;
			}
			printf("Top : %d\n", iStack.top());
			iStack.pop();
			break;
		case 3:
			while (!iStack.empty())//안 비어 있을 때 돌린다
			{
				printf("Top : %d\n", iStack.top());
				iStack.pop();
			}
			return;
		}
		system("pause");
		system("cls");
	}
}