#include <stdio.h>
//����Լ� ���� 1,2
//int�� �ҰŸ� if�� else �Ѵ� return ���� �� �ְ� //�Լ��� ������ ������ ���� X

int While(int n)
{//int �Լ����� return ���� ������ �޾ƾ��Ѵ�
	if (n <= 0)
	{
		return 0;
	}
	//�ڱͿ��� �� �߿�
	return n + While(n - 1);
	// While(n-1)�� 0���� �ؼ� ����/ while�� return ���� �ٽ� return���� �̾���
}

void Binary(int n)
{
	int i;
	if (n < 2)
	{
		printf("%d", n);
		return;
	}
	else
	{
		//i = n % 2;
		//n /= 2;
		//Binary(n);
		//printf("%d", i);

		//n /= 2;	<-	�̰� ���� ���� �������� n%2 ��� �Ұ��� �̾�����
		Binary(n / 2);
		printf("%d", n % 2);
	}
}

void main()
{
	int input;
	printf("1. ���� �Է� : ");
	scanf("%d", &input);
	printf("1 ~ %d : %d\n", input, While(input));

	//------------
	printf("\n2. ���� �Է� : ");
	scanf("%d", &input);
	printf("%d -> ", input);
	Binary(input);

	return;
}