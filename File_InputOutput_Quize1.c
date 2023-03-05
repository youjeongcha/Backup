#include<stdio.h>
//내가 열고 싶은 이름.확장명 file* f에 f가 변수
//어디다가 저장 할 건지 f,
//파일 닫기

void main()
{
	FILE* f = fopen("GoGoDan.txt", "w");
	for (int i = 2; i <= 9; i++)
	{
		fprintf(f, "========%d단========\n", i);
		for (int j = 1; j <= 9; j++)
		{
			int num = i * j;
			fprintf(f, "%d x %d = %d\n", i, j, num);
		}
		fprintf(f, "===================\n\n");

	}
	fclose(f);
}