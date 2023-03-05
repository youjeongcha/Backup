#include<stdio.h>
//fscanf["r"옵션]
//띄어쓰기 또는 엔터 단위로 정보를 가져옴

void main()
{
	FILE* f = fopen("Test.txt", "w");
	int Num;
	fprintf(f, "1 2 3 4");
	fclose(f);
	f = fopen("Test.txt", "r");
	if (f == NULL)
	{
		printf("해당 이름의 파일이 없습니다.");
	}
	else
	{
		while (!feof(f)) //feof는 파일이 끝날때. file end of // !끝나지 않을 때 게속 반복
		{
			fscanf(f, "%d", &Num); //fscnaf가 스페이스와 엔터를 구분한다.
			printf("%d", Num);
		}
		fclose(f);
	}
}