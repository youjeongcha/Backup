#include <stdio.h>
#include <stdlib.h>

void main()
{
	int* pNum = (int*)malloc(sizeof(int));
	*pNum = 10;
	printf("pNum�ּ� = %p\npNum�� = %d", pNum, *pNum);
	free(pNum);
	//*pNum = 20;
	pNum = NULL;
	printf("\npNum�ּ� = %p\npNum�� = %d", pNum, *pNum);
	//������ �����ϸ� �ȵȴ�.

	//���� �Ҵ��� �޸𸮰� �ִ� �Ϳ��� ���°�
	//��ī�� �÷��� �޸𸮿��� �Ҵ��� �ϴµ�
	//���� ���� ���� ��������� ��Ƽ ���μ��� ������ ���α׷��� ���� �� �ִµ�
	//Ư�� ���α׷� ���� �޸𸮸� a ���� �̾����� �ٸ� ���α׷��� a�� ���ڴٰ� �ϸ� ������ ����Ƿ�
	//���α׷� ������ �ؾ� �� Ư�� �޸𸮿� ���� ������ �Ҵ� �޾ƾ�.
	//�ش� �޸𸮿� ���� ������ �ݳ� �ϴ� ����. free()
}