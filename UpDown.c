#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> //Sleep �Լ� //system("cls")
//��������x return x ����üx ������x
//�Լ��� ���� ����
//int �Լ��� ���ϵǴ� ���� �־������ ��� //�迭�� int������ ���� ���� �� x

#define MIN 0
#define MAX 1
#define TURN 2


void Gamestart(int element[])
{
	int input;
	int RNum;

	//srand((unsigned)time(NULL));  //unsigned?  ��ȣ�� ���� Ÿ�� ���� ��ȣ�� �����Ƿ� �ʿ� ����.
	srand(time(NULL));
	RNum = rand() % (element[MAX] - element[MIN] + 1) + element[MIN];
	printf("%d\n", RNum);

	for (int i = 1; i <= element[2]; i++)
	{
		printf("���� : %d ~ %d\n", element[MIN], element[MAX]);
		printf("���� Turn : %d\n", element[TURN]);
		printf("==========%d ��==========\n", i);
		printf("�Է� : ");
		scanf_s("%d", &input);

		if (input < RNum)
		{
			printf("Up\n");
		}
		else if (input > RNum)
		{
			printf("Down\n");
		}
		else if (input == RNum)
		{
			system("cls");
			printf("�����Դϴ�  �ϼ� : %d\n", i);
			system("pause");
			break;
		}
		if (i == element[2])
		{
			system("cls");
			printf("GameOver : Trun�� �ʰ�\n");
			system("pause");
			break;
		}
		system("pause");
		system("cls"); //���� ������ â �ʱ�ȭ
	}
	/*	
		system("cls");
		printf("GameOver : Trun�� �ʰ�\n");
		system("pause");
		break;
		*/
}

void SettingRange(int element[])
{ // return �޴� �κ� ����
	int input;

	while (1)
	{
		system("cls");
		printf("==========���� ����==========");
		printf("\n  1. �ִ�, �ּҹ��� ����");
		printf("\n  2. �ִ� Turn�� ����");
		printf("\n  3. ���ư���");
		printf("\n�Է� : ");
		scanf_s("%d", &input);
		system("cls");

		if (input == 1)
		{
			printf(" �ּ� �� ���� <���� : %d> : ", element[MIN]);
			scanf_s("%d", &element[MIN]);
			printf(" �ִ� �� ���� <���� : %d> : ", element[MAX]);
			scanf_s("%d", &element[MAX]);
		}
		else if (input == 2)
		{
			printf(" �ִ� Turn �� ���� <���� : %d> : ", element[TURN]);
			scanf_s("%d", &element[TURN]);
		}
		else if (input == 3)
		{
			break;
		}
	}
}

void main()
{
	int input;
	int element[3] = { 1 ,100, 10 };

	while(1)
	{
		system("cls");
		printf("==========UpDown==========");
		printf("\n	1. ���ӽ���");
		printf("\n	2. ��������");
		printf("\n	3. ����");
		printf("\n�Է� : ");
		scanf_s("%d", &input);
		system("cls");

		switch(input)
		{
		case 1:
			Gamestart(element);
			break;
		case 2:
			SettingRange(element); //�迭 or �׳� ��ü �ڵ�
			break;
		case 3:
			return; //void �� return ����
		}
	}
}
