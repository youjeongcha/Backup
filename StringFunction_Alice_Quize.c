#include<stdio.h>
#include<string.h>

#define MAX 50
#define STORY 200000
#define START 0

void ShowStory()
{
	char story[STORY] = { 0, };

	FILE* f = fopen("Alice.txt", "r");
	if (f == NULL)
	{	//���� ���� ��� ����ó��
		printf("�ش� �̸��� ������ �����ϴ�.");
	}
	else
	{
		fread(story, sizeof(story), 1, f);
		printf("\n");
		printf("%s", story);
		//printf("\n>>> %d\n", strlen(story)); //�����Ҵ��� ������ �� ��� �Ұ�
	}
	fclose(f);
}

int Counting(char* word, char* check, int count)
{
	for (int i = 0; check[i] != NULL; i++)
	{
		if (check[i] == word[START])
		{
			int j = 0;
			while (check[i + j] == word[START + j])
			{
				j++;
				if (j == strlen(word))
				{
					count++;
					break; //���� - �ڿ� �ʿ� �����Ƿ� �ݺ��� �ϳ� ���
				}
			}
		}
	}
	return count;
}

void main()
{
	char word[MAX], check[MAX];
	int count = 0;

	ShowStory();
	printf("\n\n");
	printf("Check Word Input : ");
	scanf("%s", word);

	FILE* f = fopen("Alice.txt", "r");
	if (f == NULL)
	{
		printf("�ش� �̸��� ������ �����ϴ�.");
	}
	else
	{
		while (!feof(f))
		{
			fscanf(f, "%s", check);
			count = Counting(word, check, count);
		}
		fclose(f);

		printf("KMP Check most Count : %d", count);
	}
}