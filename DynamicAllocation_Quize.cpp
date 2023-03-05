#include<iostream>
#include<string>
//#include<vector>
//오름차순 병합 정렬로
using namespace std;


//Q3
//동적할당하면 길이 구하는 방법 반복 하나하나 돌리나?
//>(입력받은 값) 할당된 크기를 저장해두는 수밖에 없다. 주소의 크기만 나온다.

void Print(string display, int* num, int input)
{
	cout << display;
	for (int i = 0; i < input; i++)
	{
		//cout << num + i << " "; //주소
		//cout << *(num + i) << " "; //값
		cout << num[i] << " "; //값
	}
}

void Merge(int* num, int left, int mid, int right)
{
	int leftIndex = left, rightIndex = mid + 1;
	int index = 0;
	int* tmp;
	tmp = new int[right - left + 1];

	while (leftIndex <= mid && rightIndex <= right)
	{//비교대상 한 쪽이 끝나기까지
		if (num[leftIndex] < num[rightIndex])
			tmp[index++] = num[leftIndex++];
		else
			tmp[index++] = num[rightIndex++];
	}
	while (leftIndex <= mid || rightIndex <= right)
	{//비교대상이 한 쪽만 남으면
		if (leftIndex > mid) //left가 먼저 끝나면
			tmp[index++] = num[rightIndex++];
		else//right가 먼저 끝나면
			tmp[index++] = num[leftIndex++];
	}
	for (int i = 0; i < index; i++)
		num[left++] = tmp[i];
}


//Q1
//기존 함수 사용할때 값을 바로 넘기지 않았나
//왜 동적할당은 주소를 넘겨서 얕은 복사? 원리
//> 함수 호출에서 num인 주소르 받아서, *num으로 주소로 받는다.
//---------  중요  ---------------
//>>int* a = &b 로 선언했을 때 포인터 변수a는 변수b의 주소를 값으로 가지며 *a는 변수 b가 가진 값을 가리키는 것입니다. 
//int* a;
//a = &b; 와 같은 것
//-----------
//a는 주소를 저장하는 거.
//거기에 *쓰면 따라가는 거.
//---------------------------------
//int a = 3;
//int* b = &a;
//형을 따라가야 하는 이유 >> byte 크기때문?
//malloc(sizeof(int))로 주소값 byte를 지정하지 않나
void Sort(int* num, int left, int right)//*는 num의 값이 가리키는 주소로 num(주소) 받아 온다
{

	cout << "이거 뭔지 확인 num > " << num << endl;
	cout << "이거 뭔지 확인 *num > " << *num << endl;
	if (left != right)
	{
		int mid = (left + right) / 2;
		Sort(num, left, mid);
		Sort(num, mid + 1, right);
		Merge(num, left, mid, right);
	}
}

void main()
{
	int* num;
	int input;

	cout << "정수 동적할당할 수량 입력(5) >> ";
	cin >> input;
	cout << endl;

	num = new int[input]; //주소 지정하는 코드에서 크기 지정

	//Q2
	//vector<int*> sortlist;//vector로 만들거면 동적할당 필요?
	//vector사용이 가능한지, 이점이 있는지
	//vector사용하면 자동으로 동적할당을 해주는 거?

	for (int i = 0; i < input; i++)
	{
		cout << "정수 입력 : ";
		cin >> *(num + i);
	}

	cout << endl;
	Print("입력 받은 정수 : ", num, input);
	cout << endl;

	//오름차순 병합정렬
	Sort(num, 0, input - 1); //주소 넘겨줌
	Print("정렬한 정수 : ", num, input);

	delete[]num;
}