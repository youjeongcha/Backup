#include <stdio.h>
#include <string.h>

void Strpy(char* My_Name, char* Name)
{
	int i = 0;
	while (1)
	{
		Name[i] = My_Name[i];
		i++;
		if (My_Name[i] == NULL)
		{
			Name[i] = NULL;
			break;
		}
	}

}

void main()
{
	char Name[10];
	char My_Name[10];

	printf("이름을 입력하십시오 : ");
	scanf("%s", My_Name);

	//strcpy(Name, My_Name); //앞 변수에 뒷 변수의 문자열을 복사
	Strpy(My_Name, Name);
	
	printf("Name : %s\n", Name);
	printf("My_Name : %s\n", My_Name);
}