#include <stdio.h>

struct people
{
	char Name[10]; //멤버 변수
	int Age;
	float Height;
};

void main()
{
	struct people P1 = { "최정호",20,185.7f}; //자료형에 별명을 붙여서 쓴다.//소숫점그냥 쓰면 double이 되기 때문에 f붙여줘야 float
	printf("이름 = %s\n나이 = %d\n키 = %.2f\n", P1.Name, P1.Age, P1.Height); //멤버변수 접근 지정자
}