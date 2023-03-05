#include<stdio.h>
//fgets["r" 옵션]
//엔터 단위로 정보를 가져옴

typedef struct people
{
	char Name[10];
	int Age;
	char PhonNumber[20];
}People;

void main()
{
	People P1 = { "A", 20, "010-1234-5678" };
	FILE* f = fopen("People.txt", "w");
	char buf[256]; //띄워쓰기를 포함할 수 있는 거 캐릭터뿐 띄워쓰기 포함가능
	fprintf(f, "이름 : %s 나이 : %d\n", P1.Name, P1.Age);
	fprintf(f, "휴대폰번호 : %s", P1.PhonNumber);
	fclose(f);
	f = fopen("People.txt", "r");
	if (f == NULL)
	{
		printf("해당 이름의 파일이 없습니다.");
	}
	else
	{
		while (!feof(f))
		{
			fgets(buf, sizeof(buf), f); //변수명, 저장 크기. 어디서 들고 올건가.
			printf("%s\n", buf);
		}
		fclose(f);
	}
};