#include<stdio.h>
#include<stdlib.h>
#include<Windows.h> //Sleep �Լ� //system("cls")
#include<time.h>

#define GAMESTART 1
#define MAXORMIN 1
#define SETTING 2
#define MAXTURN 2
#define EXIT 3


int GameMenu()
{
	int Select;
	system("cls");
	printf("=========UpDown=========\n");
	printf("\t1.���ӽ���\n");
	printf("\t2.��������\n");
	printf("\t3.����\n");
	printf("�Է� : ");
	scanf("%d", &Select);
	return Select;
}

void GamePlay(int Max, int Min, int MaxTurn)
{
	int RandomNum = (rand() % ((Max + 1) - Min)) + Min;
	int Num, Turn = 0;
	while (Turn < MaxTurn)
	{
		Turn++;
		system("cls");
		printf("����  : %d ~ %d\n", Min, Max);
		printf("���� Turn : %d\n", MaxTurn);
		printf("========%d��========\n", Turn);
		printf("�Է� : ");
		scanf("%d", &Num);
		if (Num > RandomNum)
			printf("Down!!\n");
		else if (Num < RandomNum)
			printf("Up!!\n");
		else
		{
			system("cls");
			printf("����!!\t�ϼ� : %d\n", Turn);
			system("pause");
			return;
		}
		system("pause");
	}
	system("cls");	//�ݺ��� �ۿ� ������ �ڿ������� �� �� �ʰ� ���� ����
	printf("GameOver : Trun�� �ʰ�!!\n");
	system("pause");
	return;
}

int SetMin(int Min)
{
	printf(" (���� : %d)�ּ� �� ���� : ", Min);
	scanf("%d", &Min);
	return Min;
}
int SetMax(int Max, int Min)
{
	printf(" (���� : %d)�ִ� �� ���� : ", Max);
	scanf("%d", &Max);
	if (Max <= Min) //�ּҰ� �ִ뺸�� Ŭ ���
	{
		return -1;
	}
	return Max;
}

int SetMaxTurn(int MaxTurn)
{
	printf(" (���� : %d)�ִ� Turn �� ���� : ", MaxTurn);
	scanf("%d", &MaxTurn);
	if (MaxTurn <= 0) //�ϰ� �ּ�ġ�� �����ص״�
		return 0;
	return MaxTurn;
}

void main()
{
	int Max = 100, TmpMax;
	int Min = 1, TmpMin;
	int MaxTurn = 10, TmpMaxTurn;
	int Select;
	int SetState = 1;
	srand(time(NULL));
	while (1)
	{
		switch (GameMenu()) //����
		{
		case GAMESTART:
			GamePlay(Max, Min, MaxTurn);
			break;
		case SETTING:
			SetState = 1;
			while (SetState)
			{
				system("cls");
				printf("=======���� ����=======\n");
				printf("  1.�ִ�,�ּҹ��� ����\n");
				printf("  2.�ִ� Turn�� ����\n");
				printf("  3.���ư���\n");
				printf("�Է� : ");
				scanf("%d", &Select);
				switch (Select)
				{
				case MAXORMIN:
					while (1)
					{
						system("cls");
						TmpMin = SetMin(Min);
						TmpMax = SetMax(Max, TmpMin);
						if (TmpMax == -1) //�ּҰ� �� Ŭ ��� ���� ǥ�õ�
							printf("���� : �ּҰ��� �ִ밪 ���� Ů�ϴ� �ٽ� �Է��ϼ���.\n");
						else
						{
							Max = TmpMax;
							Min = TmpMin;
							break;
						}
						system("pause");
					}
					break;
				case MAXTURN:
					while (1)
					{
						system("cls");
						TmpMaxTurn = SetMaxTurn(MaxTurn);
						if (TmpMaxTurn != 0)
						{
							MaxTurn = TmpMaxTurn;
							break;
						}
						printf("���� : �ִ� �ϼ��� 0���� �۰ų� �����ϴ� �ٽ��Է��ϼ���.\n");
						system("pause");
					}
					break;
				case EXIT:
					SetState = 0; //�ݺ����� ������ �ǵ鿩 ���������� ���
					break;
				}
			}
			break;
		case EXIT:
			return;
		}
	}
}