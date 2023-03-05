#include<stdio.h>
#include<list>//Linked Type List
#include<vector>//Array Type List
#include<algorithm>//알고리즘 vector에서 사용

//생성빈도와 접근빈도

//list
//장점 : 데이터의 추가 제거가 자유롭다.
//단점 : 특정 데이터의 접근속도가 느리다.
//--계속 추가가 되는 경우

//vector 가변배열
//장점 : 특정 데이터의 접근속도가 빠르다. > 주소가 연속적으로 나열되어있다.
//단점 : 데이터의 추가 제거가 자유롭지 못하다. > ㅋ배열 크기+1 더 만들어서 복사하고 추가
//-- 데이터 세팅 한번 해두고 접근 속도 빠르게 할때

void PrintList(std::vector<int> iList)
{//iterator 각각의 데이터를 가리키는 포인터 변수 같은 역할
	//begin()제일 처음 저장한 데이터를 가리키는 포인터 같은 느낌//그렇다고 포인터는 아님
	//end() 마지막 다음 데이터 널과 같은 느낌 //마지막 데이터는 vack
	//for (std::vector<int>::iterator iter = iList.begin(); iter != iList.end(); iter++)
	for (int i = 0; i < iList.size(); i++)
		printf("%d ", iList[i]);//포인터와 비슷한 느낌 저장한 주소를 따라가라 같은
	printf("\n");
}

std::vector<int>::iterator Search(std::vector<int>* iList, int Data)
{
	for (std::vector<int>::iterator iter = iList->begin(); iter != iList->end(); iter++)
	{
		if (*iter == Data)
			return iter;
	}
	return iList->end();
}

void SearchData(std::vector<int> iList, int Data)
{
	//std::vector<int>::iterator iter = Search(&iList, Data);
	std::vector<int>::iterator iter = std::find(iList.begin(), iList.end(), Data); //정확하게 어떤걸로 할지 아는 상황 ex>구조체같은 건 불가 C++로 가능
	if (iter == iList.end())
		printf("데이터 %d를 찾지못했습니다.\n", Data);
	else
		printf("데이터 %d를 찾았습니다.\n", Data);
}

void Add(std::vector<int>* iList, int Data, int AddData)
{
	std::vector<int>::iterator iter = Search(iList, Data);
	if(iter == iList->end())
		printf("데이터 %d를 찾지못했습니다.\n", Data);
	else
	{
		//어디다가 추가할 거냐. 뭘 추가할 거냐 순서
		iList->insert(iter, AddData);
	}
}

void Modify(std::vector<int>* iList, int Data, int ModifyData)
{
	std::vector<int>::iterator iter = Search(iList, Data);
	if (iter == iList->end())
		printf("데이터 %d를 찾지못했습니다.\n", Data);
	else
	{
		*iter = ModifyData;
	}
}

void Delete(std::vector<int>* iList, int Data)
{
	std::vector<int>::iterator iter = Search(iList, Data);
	if (iter == iList->end())
		printf("데이터 %d를 찾지못했습니다.\n", Data);
	else
	{
		iList->erase(iter);
	}
}

void main()
{
	//저장, 출력, 검색, 추가, 수정, 삭제
	std::vector<int> iList;
	
	for (int i = 1; i <= 10; i++) 
		iList.push_back(i); //뒤에 넣음

	///iList.push_front(11); //앞에 넣음
	PrintList(iList);

	SearchData(iList, 5);
	SearchData(iList, 25);

	Add(&iList, 5, 25);
	PrintList(iList);

	Modify(&iList, 7, 77);
	PrintList(iList);

	iList.pop_back(); //vector에는 pop_back push_back은 다 된다
	PrintList(iList);

	///iList.pop_front();
	PrintList(iList);

	Delete(&iList, 77);
	PrintList(iList);

	//front
	//back은 Queue와 동일
	//empty 비어있는거 확인하는

	iList.clear();//전체삭제
	///iList.sort();//오름차순 정렬
	//vector 정렬
	std::sort(iList.begin(), iList.end());//오름차순
	std::sort(iList.begin(), iList.end(),std::greater<int>());//내림차순
	///iList.reverse();//데이터 역순
	//별도의 내림차순 존재 X > sort()하고 reverse()
}