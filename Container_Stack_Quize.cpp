//STL:Standard Template Library
//Container : STL �ڷᱸ�� ���̺귯��

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
	printf("�Է� : ");
	scanf("%d", &input);
	return input;
}
//���� �ּҸ� �����ϴ� ����ü�� �����Ҵ� �ʿ�X
//stack���� ���� �̷������
void main()
{
	std::stack<int> iStack; //<�ڷ���> ���� �ȿ� ����
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
				printf("������ �����Ͱ� �����ϴ�.\n");
				break;
			}
			printf("Top : %d\n", iStack.top());
			iStack.pop();
			break;
		case 3:
			while (!iStack.empty())//�� ��� ���� �� ������
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