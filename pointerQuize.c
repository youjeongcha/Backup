#include <stdio.h>

#define NULL 0
#define LEN 100
#define EIGHT 8

void CapitalTransform(char* input)
{
	for (int i = 0; input[i] != NULL; i++) //null기준으로 수정
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
void ClimbingOrder(int* arr) //매개변수 * or  []
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
	////1번 대문자로 변경
	char input[LEN];
	printf("1. 문자열을 입력하시오 : ");
	scanf("%s", input); //&붙일 필요 x 시작 주소부터 들어가기 때문 //91번째와 어떤 차이가 있는지 주의 요망
	printf("함수 호출 전 = %s", input);
	CapitalTransform(input);
	printf("\n함수 호출 후 = %s", input);
	printf("\n\n");

	////2번 큰 수 구하기
	int num1, num2;
	printf("2. 두 정수를 입력하시오 : ");
	scanf("%d", &num1);
	scanf("%d", &num2);
	printf("%d 와(과) %d중 큰 수는 : ", num1, num2);
	Bigger(&num1, num2);
	printf("%d", num1);
	printf("\n\n");

	//3번 1~누적 합계
	int num;
	printf("3. 정수를 입력하시오 : ");
	scanf("%d", &num);
	printf("1 ~ %d 의 총합 : ", num);
	Sum(&num); //pNum에 는 주소값이 있다. 이걸 &로 받으면 주소값을 받은 주소값
	printf("%d", num);
	printf("\n\n");

	//4번 8개 오름차순
	int arr[EIGHT] = {0, };
	printf("4. 오름차순 정렬\n");
	for (int i = 0; i < EIGHT; i++)
	{
		printf("[%d]번째 정수 입력 : ", i+1);
		scanf("%d", &arr[i]);
	}
	printf("정렬 전 : ");
	for (int i = 0; i < EIGHT; i++)
	{
		printf("%d ", arr[i]);
	}
	ClimbingOrder(arr);
	printf("\n정렬 후 : ");
	for (int i = 0; i < EIGHT; i++)
	{
		printf("%d ", arr[i]);
	}
}