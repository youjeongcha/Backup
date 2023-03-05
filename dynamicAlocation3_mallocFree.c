#include <stdio.h>
#include <stdlib.h>

void main()
{
	int* pNumArr;
	int Size;
	printf("할당할 공간의 갯수를 입력하시오 : ");
	scanf("%d", &Size);
	pNumArr = (int*)malloc(sizeof(int) * Size); //곱셈이었다...
	/*int형변환 해주면 메모리 묶어서 이용 가능*/
	for (int i = 0; i < Size; i++)
	{
		pNumArr[i] = i + 1;
	}
	for (int i = 0; i < Size; i++)
	{
		printf("%d = %d\n", i, pNumArr[i]);
	}
	free(pNumArr);
	pNumArr = NULL;
}