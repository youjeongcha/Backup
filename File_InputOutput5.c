#include<stdio.h>
//fgets["r" �ɼ�]
//���� ������ ������ ������

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
	char buf[256]; //������⸦ ������ �� �ִ� �� ĳ���ͻ� ������� ���԰���
	fprintf(f, "�̸� : %s ���� : %d\n", P1.Name, P1.Age);
	fprintf(f, "�޴�����ȣ : %s", P1.PhonNumber);
	fclose(f);
	f = fopen("People.txt", "r");
	if (f == NULL)
	{
		printf("�ش� �̸��� ������ �����ϴ�.");
	}
	else
	{
		while (!feof(f))
		{
			fgets(buf, sizeof(buf), f); //������, ���� ũ��. ��� ��� �ðǰ�.
			printf("%s\n", buf);
		}
		fclose(f);
	}
};