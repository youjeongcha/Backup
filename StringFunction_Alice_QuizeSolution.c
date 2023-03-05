#pragma warning(disable:4996) //sdl�����ڵ�(scanf_s ��� ���Ϸ���(�ɼǿ��� sdl üũ ������ �Ͱ� ����), ���� �Է� ���� �� ���� ��� ������ �迭 ũ�⺸�� �� ū ũ�⸦ �Է� ������ �޸𸮰� ���� �Ǵµ� �װ��� ���� ���ؼ� sdl������ �ɼǿ��� ����� �ǵ� �̰Ŵ� �׳� �ڵ�� ���������ִ� ��)
#include<stdio.h>
#include<time.h> //�ʿ����
#include<string.h>
//KMP �˰����� ����� ��.
/* KMP �˰���??
* ���ڿ� Ž�� �˰���
*/
int KMPCheck(char buf[], char Check[], int Size)
{
	for (int i = 0; i <= Size / 2; i++)
	{//size �������� �߶� //����� ���� Ȯ���ϱ� �� ��
		if (buf[i] != Check[i] || buf[Size - i] != Check[Size - i])//�� �� ���ÿ� ��ġ ����ġ ã�ƺ���.
			return 0; //����ġ
	}
	return 1; //��ġ
}

int KMPSearch(char buf[], char Check[], int Size)
{//buf�� ���پ� �о�� ���ڿ�
	int count = 0;
	for (int i = 0; buf[i] != NULL; i++)
	{//���ڿ� ���������� ���پ�
		if (Check[0] == buf[i] && Check[Size - 1] == buf[i + Size - 1])
		{//�Է��� ù���ڿ� ������ ���� �ε��� �ȿ� �ִ°� buf �ȿ� �ִ� �Ͱ� ������
			if (KMPCheck(&buf[i + 1], &Check[1], Size - 3) == 1) //��ġ 1
			{
				count++;
				i += (Size - 1); //�Է¹��� ���� ũ�� - 1 //���ڿ� �ΰ��� �������� a+b-1
				//�ش� ���ڿ��� �����ϸ�, �ش� ���ڿ��� �� �ε�����ȣ�� ��ŵ
				//KMPCheck���� �յڷ� �Ǻ��� �ϱ� ������ ��ŵ�ϴ� ��
			}
		}
	}
	return count;
}
void main()
{
	char buf[300000] = { 0 };
	FILE* f = fopen("Alice.txt", "r");
	if (f == NULL)
	{
		printf("�ش� �̸��� ������ �����ϴ�.\n");
		return;
	}
	else
	{
		fread(buf, sizeof(buf), 1, f);
		fclose(f);
		printf("%s", buf);
		char Check[256];
		printf("Check Word Input : ");
		scanf("%s", Check);
		f = fopen("Alice.txt", "r");
		int count = 0;
		while (!feof(f))
		{
			fgets(buf, sizeof(buf), f); //fgets�� ���� ������ ������ ������
			count += KMPSearch(buf, Check, strlen(Check)); //���� ���� ����� �÷���
		}
		printf("KPM Check %s Count : %d\n", Check, count);
	}
}