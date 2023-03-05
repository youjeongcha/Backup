//문자열 함수 
//Strcat 문자열을 추가해주는 함수
#include <stdio.h>
#include <string.h>

void Strcat(char* str, char* add)
{//for 돌아서 null 끝을 찾고
	//if로  null이면 다른 변수 null또 찾기
	int endStr = 1, endAdd = 1;
	for (int  i = 0; str[i] != NULL; i++)
	{
		if (str[endStr] == NULL)
		{
			for (int j = 0; add[j] != NULL; j++)
			{
				str[endStr + j] = add[j];
				if (add[endAdd] == NULL)
				{
					str[endStr + endAdd] = NULL;
					return;
				}
				endAdd++;
			}
		}
		endStr++;
	}

	//int len = strlen(str);
	//int empty = 0;
	//for (int i = 0; add[i] != NULL; i++)
	//{
	//	str[len + i] = add[i]; 
	//	empty++;
	//}
	//str[len + empty] = NULL; //추가하는 건 변수 둘 중 하나만 인덱스 0을 고려한다

}

void main()
{
	char str[20] = "Hello";
	char add[10] = "^^";
	printf("%s\n", str);
	//strcat(str, "^^");
	Strcat(str, add);
	printf("%s\n", str);
}