#include<stdio.h>
//���� ���� ���� �̸�.Ȯ��� file* f�� f�� ����
//���ٰ� ���� �� ���� f,
//���� �ݱ�

void main()
{
	FILE* f = fopen("GoGoDan.txt", "w");
	for (int i = 2; i <= 9; i++)
	{
		fprintf(f, "========%d��========\n", i);
		for (int j = 1; j <= 9; j++)
		{
			int num = i * j;
			fprintf(f, "%d x %d = %d\n", i, j, num);
		}
		fprintf(f, "===================\n\n");

	}
	fclose(f);
}