#include<stdio.h>
//fscanf["r"�ɼ�]
//���� �Ǵ� ���� ������ ������ ������

void main()
{
	FILE* f = fopen("Test.txt", "w");
	int Num;
	fprintf(f, "1 2 3 4");
	fclose(f);
	f = fopen("Test.txt", "r");
	if (f == NULL)
	{
		printf("�ش� �̸��� ������ �����ϴ�.");
	}
	else
	{
		while (!feof(f)) //feof�� ������ ������. file end of // !������ ���� �� �Լ� �ݺ�
		{
			fscanf(f, "%d", &Num); //fscnaf�� �����̽��� ���͸� �����Ѵ�.
			printf("%d", Num);
		}
		fclose(f);
	}
}