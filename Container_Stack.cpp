//STL:Standard Template Library
//Container : STL �ڷᱸ�� ���̺귯��
//Ȯ���.cpp�� ���

//Container�� C���� �̿�

//.h ������ c �Ⱥ����� c++
//���� ���̺귯��
#include<stdio.h>
#include<stack>

void main()
{
	std::stack<int> iStack; //<�ڷ���>
	for (int i = 1; i <= 5; i++)
	{
		iStack.push(i);
		printf("Top : %d\n", iStack.top());
	}

	printf("\nsize : %d\n\n", iStack.size());

	while (!iStack.empty())//�Ⱥ�� ���� �� ������ ��
	{
		printf("Top : %d\n", iStack.top());
		iStack.pop();
	}
}