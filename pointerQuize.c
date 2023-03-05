#include <stdio.h>

#define NULL 0
#define LEN 100
#define EIGHT 8

void CapitalTransform(char* input)
{
	for (int i = 0; input[i] != NULL; i++) //null�������� ����
	{
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			input[i] -= 32;
		}
	}
}
//---------------
void Bigger(int* num1, int num2)
{
	int temp;
	if (*num1 < num2)
	{
		temp = num2;
		num2 = *num1;
		*num1 = temp;
	}
}
//---------------
void Sum(int* num)
{
	int temp = *num;
	for (int i = 1; i < temp; i++)
	{
		*num += i;
	}
}
//---------------
void ClimbingOrder(int* arr) //�Ű����� * or  []
{
	int temp;
	for (int i = 0; i < EIGHT; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[i] < arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main()
{
	////1�� �빮�ڷ� ����
	char input[LEN];
	printf("1. ���ڿ��� �Է��Ͻÿ� : ");
	scanf("%s", input); //&���� �ʿ� x ���� �ּҺ��� ���� ���� //91��°�� � ���̰� �ִ��� ���� ���
	printf("�Լ� ȣ�� �� = %s", input);
	CapitalTransform(input);
	printf("\n�Լ� ȣ�� �� = %s", input);
	printf("\n\n");

	////2�� ū �� ���ϱ�
	int num1, num2;
	printf("2. �� ������ �Է��Ͻÿ� : ");
	scanf("%d", &num1);
	scanf("%d", &num2);
	printf("%d ��(��) %d�� ū ���� : ", num1, num2);
	Bigger(&num1, num2);
	printf("%d", num1);
	printf("\n\n");

	//3�� 1~���� �հ�
	int num;
	printf("3. ������ �Է��Ͻÿ� : ");
	scanf("%d", &num);
	printf("1 ~ %d �� ���� : ", num);
	Sum(&num); //pNum�� �� �ּҰ��� �ִ�. �̰� &�� ������ �ּҰ��� ���� �ּҰ�
	printf("%d", num);
	printf("\n\n");

	//4�� 8�� ��������
	int arr[EIGHT] = {0, };
	printf("4. �������� ����\n");
	for (int i = 0; i < EIGHT; i++)
	{
		printf("[%d]��° ���� �Է� : ", i+1);
		scanf("%d", &arr[i]);
	}
	printf("���� �� : ");
	for (int i = 0; i < EIGHT; i++)
	{
		printf("%d ", arr[i]);
	}
	ClimbingOrder(arr);
	printf("\n���� �� : ");
	for (int i = 0; i < EIGHT; i++)
	{
		printf("%d ", arr[i]);
	}
}