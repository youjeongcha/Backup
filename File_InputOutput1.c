#include<stdio.h>
//내가 열고 싶은 이름.확장명 file* f에 f가 변수
//어디다가 저장 할 건지 f,
//파일 닫기
void main()
{
	FILE* f = fopen("Test.txt", "w");
	int Num = 123;
	fprintf(f, "덮어 쓰기 모드 %d", Num);
	fclose(f);
}