#include <stdio.h>

void main()
{
	int Num;
	int *pNum = &Num;
	*pNum = 10;
	//* 2���� �ǹ� ������ �ڿ� ���̸� ������ ����
	//�ִ� ���� �տ� ���̸� �ش� ������ �ּҿ� ���� ���� ����
	printf("Num�� �ּ� = %p\n", &Num);
	printf("pNum�� ������ �ִ� �� =  %p\n", pNum);
	printf("Num = %d\n", Num);
	printf("pNum =  %d\n", *pNum);
	printf("pNum�� �ּ� =  %p\n", &pNum);

}