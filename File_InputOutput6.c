#include<stdio.h>
//fread["r" 옵션]
//정보 전체를 가져옴
//-> 하지만 쓰레기값이 나온다.
//NULL이 나올때까지 쭉 출력하기 때문에 어디가 끝인지 몰라서 쓰레기값
//그래서 문자열 자체를 널로 초기화시켜서 사용

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
	char buf[256] = {0, }; //띄워쓰기를 포함할 수 있는 거 캐릭터뿐 띄워쓰기 포함가능
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
		fread(buf, sizeof(buf), 1, f); //변수명, 저장 크기, ,어디서 들고 올건가.
		printf("%s\n", buf);
	}
	fclose(f);
};