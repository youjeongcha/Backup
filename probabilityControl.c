#include <stdio.h>
#include <stdlib.h> //rand srand�Լ�
#include <time.h>
#include <Windows.h>

#define TRUE 1
#define FALSE 0

void Menu()
{
	system("cls");
	printf("====�̱� ����====\n");
	printf("\t1.1ȸ �̱�\n");
	printf("\t2.10+1ȸ �̱�\n");
	printf("\t3.����\n");
}

void Gacha()
{
	int Num = rand() % 100; //0~99
	if (Num >= 0 && Num <  60)
		printf("N���..\n");
	else if (Num >= 60 && Num < 80)
		printf("R���!\n");
	else if (Num >= 80 && Num < 90)
		printf("SR���!!\n");
	else if (Num >= 90 && Num < 95)
		printf("��SSR��ޡ�\n");
	else if (Num >= 95 && Num < 98)
		printf("�١�!SSSR���!�ڡ�\n");
	else //98~99
	{
		printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١�\n");
		printf("�١ڡ١��� �� �ڡ١ڡ١�\n");
		printf("�١ڡ١�  U R  �١ڡ١�\n");
		printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١�\n");
	}
}

void main()
{
	int Exit = FALSE;
	int select;
	srand(time(NULL));
	while (!Exit)
	{
		Menu();
		scanf("%d", &select);
		switch (select)
		{
		case 1: //1ȸ
			Gacha();
			break;
		case 2:	//10+1ȸ
			for (int i = 0; i < 11; i++)
			{
				Gacha();
			}
			break;
		case 3: //����
			Exit = TRUE;
		}
		system("pause");
	}
}