#include <stdio.h>
//����Լ� - ���� ���� ȣ���Ѵ�

void While(int n)
{
	printf("%d\n", n);
	if (n <= 0)
		return;
	else
		While(n - 1);//�߰�ȣ ���̳� ������ ������ �Լ��� ����ȴ�
	printf("%d\n", n);
}

void main()
{
	While(10);	//�ش� �Լ��� ȣ���ϴ� ������ 
				//�ش� �Լ��� ����ϴ� �޸� �Ҵ�
	return;
}