#include<stdio.h>

void main()
{
	FILE* f = fopen("GoGoDan.txt", "w");
	for (int i = 2; i <= 9; i++)
	{
		fprintf(f, "========%d단========\n", i);
		for (int j = 1; j <= 9; j++)
			fprintf(f, "%d x %d = %d\n", i, j, i * j); //그냥 바로 여기서 계산 넣어버림
		fprintf(f, "=====================\n\n");
	}
	fclose(f);
}