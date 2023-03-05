#include<stdio.h>

#define MAX 10
#define EVEN 0
#define ODD 1

void arrPrint(int arr[], int isLeap);
int odd_evenNumer(int arr[], int sumArry[], int count, int i);
int hap(int sumArry[], int count);

void arrPrint(int arr[], int isLeap)
{
	int invert_arry[MAX] = { 0 };

	for (int i = 0; i < MAX; i++)
	{
		if (isLeap == 1)
		{
			printf("%d,", arr[i]);
		}
		else
		{
			invert_arry[i] = arr[MAX - 1 - i];
			printf("%d,", invert_arry[i]);
		}
	}
	printf("\b \n");
}

int odd_evenNumer(int arr[], int sumArry[], int count, int i)
{
	for (int j = 0; i < MAX; i += 2, j++)
	{
		printf("%d,", arr[i]);
		sumArry[j] = arr[i];
		count++;
	}

	return count;
}

int hap(int sumArry[], int count) 
{
	int sum = 0;

	for (int i = 0; i < count; i++)
	{
		sum += sumArry[i];
	}

	return sum;
}

int main() {
	int arr[MAX] = {10, 17, 3, 9, 37, 10, 8, 9, 13, 21};
	int sumArry[MAX] = { 0 };
	int count = 0, temp, isLeap = 1;
	int sort_Arr[MAX] = { 0 };

	// 1�� ����__________________________________________________
	printf("1�� ����\n");

	arrPrint(arr, isLeap);


	// 2�� ����__________________________________________________
	printf("\n2�� ����");

	printf("\ninvert_arry : ");
	isLeap = 0;
	arrPrint(arr, isLeap);
	printf("\b");
	isLeap = 1;
	printf("arr : ");
	arrPrint(arr, isLeap);


	// 3�� ����__________________________________________________
	printf("\n3�� ����");

	printf("\nȦ�� ��° ���� : ");
	count = odd_evenNumer(arr, sumArry, count, ODD); //1
	printf("\b ");
	printf("\nȦ�� ��° ���� : %d", hap(sumArry,count));

	count = 0;
	printf("\n¦�� ��° ���� : ");
	//	for (int i = 0; i < MAX; i+2) ���ѹݺ�
	count = odd_evenNumer(arr, sumArry, count, EVEN); //0
	printf("\b ");
	printf("\n¦�� ��° ���� : %d", hap(sumArry, count));


	// 4�� ����__________________________________________________
	printf("\n\n4�� ����\n");

	printf("arr : ");
	arrPrint(arr, isLeap);

	printf("sort_Arr : ");
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (arr[j] > sort_Arr[i]) {
				temp = arr[j];
				arr[j] = sort_Arr[i];
				sort_Arr[i] = temp;
			}
		}
	}
	arrPrint(sort_Arr, isLeap);

	return 0;
}