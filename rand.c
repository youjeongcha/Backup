#include <stdio.h>
#include <stdlib.h>
//rand�� cpu���� ������ ���ذ��� �������� ������ ��� ��ǻ�Ϳ��� ����, �ٽ� �����ص� ���� ����.
void main()
{
	int RNum;
	while (1)
	{
		system("cls");
		for (int i = 1; i <= 6; i++)
		{
			RNum = rand();
			printf("%d. %d\n", i, RNum);
		}
		system("pause");
	}
}