#include <stdio.h>
#include <stdlib.h> //rand srand함수
#include <time.h>
#include <Windows.h>

#define TRUE 1
#define FALSE 0

void Menu()
{
	system("cls");
	printf("====뽑기 게임====\n");
	printf("\t1.1회 뽑기\n");
	printf("\t2.10+1회 뽑기\n");
	printf("\t3.종료\n");
}

void Gacha()
{
	int Num = rand() % 100; //0~99
	if (Num >= 0 && Num <  60)
		printf("N등급..\n");
	else if (Num >= 60 && Num < 80)
		printf("R등급!\n");
	else if (Num >= 80 && Num < 90)
		printf("SR등급!!\n");
	else if (Num >= 90 && Num < 95)
		printf("☆SSR등급☆\n");
	else if (Num >= 95 && Num < 98)
		printf("☆★!SSSR등급!★☆\n");
	else //98~99
	{
		printf("☆★☆★☆★☆★☆★☆★\n");
		printf("☆★☆★초 대 박☆★☆★\n");
		printf("☆★☆★  U R  ☆★☆★\n");
		printf("☆★☆★☆★☆★☆★☆★\n");
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
		case 1: //1회
			Gacha();
			break;
		case 2:	//10+1회
			for (int i = 0; i < 11; i++)
			{
				Gacha();
			}
			break;
		case 3: //종료
			Exit = TRUE;
		}
		system("pause");
	}
}