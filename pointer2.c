#include <stdio.h>

void main()
{
	int Num = 10, * pNum;
	//int�� 4����Ʈ 4���� �޸� �� ó���� ��ǥ �ּ�
	char Ch = 'a', * pCh;

	pNum = &Num;
	pCh = &Ch;

	printf("pCh-1 = %p���� pCh = %p���� pCh+1 = %p����\n", pCh - 1, pCh, pCh + 1);
	printf("Num-1 = %p���� Num = %p���� Num+1 = %p ����\n", pNum -1, pNum, pNum + 1);
	//�ڷ����� ũ�⸸ŭ �����ų� ��������
}