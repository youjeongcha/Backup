#include<stdio.h>
#include<conio.h>

void ConvertToUppercase(char* str)
{
	while ((*str) != 0) //while ���
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
	for (int i = 0; i < 7; i++) //����
	{
		for (int j = i + 1; j < 8; j++) //i���� �ϳ� ��
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
	printf("1.���ڿ��� �Է��Ͻÿ� :");
	scanf("%s", string);
	printf("�Լ� ȣ�� �� = %s\n", string);
	ConvertToUppercase(string);
	printf("�Լ� ȣ�� �� = %s\n", string);

	int Num1, Num2, BigNum; //
	printf("2.�� ������ �Է��Ͻÿ� : ");
	scanf("%d%d", &Num1, &Num2);
	Big(Num1, Num2, &BigNum); //
	printf("%d��(��)%d�� ū ���� %d\n", Num1, Num2, BigNum);

	int SumNum = 0;
	printf("3.������ �Է��Ͻÿ� : ");
	scanf("%d", &Num1);
	Sum(Num1, &SumNum);
	printf("1 ~ %d �� �� �� : %d\n", Num1, SumNum);

	int arr[8];
	printf("4.�������� ����\n");
	for (int i = 0; i < 8; i++)
	{
		printf("[%d]��° ���� �Է� : ", i);
		scanf("%d", &arr[i]);
	}
	printf("���� �� : ");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");
	Sort(arr);
	printf("���� �� : ");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	getch();
}