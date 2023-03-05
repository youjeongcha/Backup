#include <stdio.h>
#include <string.h>

void main()
{
	char Name[10];
	char My_Name[10] = "JungHo";
	
	//복사할 공간 / 복사할 내용
	strcpy(Name, My_Name); //앞 변수에 뒷 변수의 문자열을 복사
	printf("Name : %s\n", Name);
	printf("My_Name : %s\n", My_Name);
}