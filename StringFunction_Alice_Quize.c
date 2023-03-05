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
	{	//파일 없을 경우 예외처리
		printf("해당 이름의 파일이 없습니다.");
	}
	else
	{
		fread(story, sizeof(story), 1, f);
		printf("\n");
		printf("%s", story);
		//printf("\n>>> %d\n", strlen(story)); //동적할당은 해제한 후 사용 불가
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
					break; //주의 - 뒤에 필요 없으므로 반복문 하나 벗어남
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
		printf("해당 이름의 파일이 없습니다.");
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