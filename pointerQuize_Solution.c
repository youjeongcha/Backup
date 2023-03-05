#include<stdio.h>
#include<conio.h>

void ConvertToUppercase(char* str)
{
	while ((*str) != 0) //while 사용
	{
		if ((*str) >= 'a' && (*str) <= 'z')
			(*str) -= 32;
		str++; //
	}
}

void Big(int A, int B, int* C)
{
	if (A >= B)
		*C = A;
	else
		*C = B;
}

void Sum(int Num1, int* SumNum)
{
	for (int i = 1; i <= Num1; i++)
		*SumNum += i;
}

void Sort(int* arr)
{
	int tmp;
	for (int i = 0; i < 7; i++) //기준
	{
		for (int j = i + 1; j < 8; j++) //i보다 하나 앞
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void main()
{
	char string[256];
	printf("1.문자열을 입력하시오 :");
	scanf("%s", string);
	printf("함수 호출 전 = %s\n", string);
	ConvertToUppercase(string);
	printf("함수 호출 후 = %s\n", string);

	int Num1, Num2, BigNum; //
	printf("2.두 정수를 입력하시오 : ");
	scanf("%d%d", &Num1, &Num2);
	Big(Num1, Num2, &BigNum); //
	printf("%d와(과)%d중 큰 수는 %d\n", Num1, Num2, BigNum);

	int SumNum = 0;
	printf("3.정수를 입력하시오 : ");
	scanf("%d", &Num1);
	Sum(Num1, &SumNum);
	printf("1 ~ %d 의 총 합 : %d\n", Num1, SumNum);

	int arr[8];
	printf("4.오름차순 정렬\n");
	for (int i = 0; i < 8; i++)
	{
		printf("[%d]번째 정수 입력 : ", i);
		scanf("%d", &arr[i]);
	}
	printf("정렬 전 : ");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");
	Sort(arr);
	printf("정렬 후 : ");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	getch();
}