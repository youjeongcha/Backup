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

	printf("�̸��� �Է��Ͻʽÿ� : ");
	scanf("%s", My_Name);

	//strcpy(Name, My_Name); //�� ������ �� ������ ���ڿ��� ����
	Strpy(My_Name, Name);
	
	printf("Name : %s\n", Name);
	printf("My_Name : %s\n", My_Name);
}