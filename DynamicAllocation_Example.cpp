#include<iostream>
#include<string>
#include<Windows.h>
#include<vector>
using namespace std;

#define STUDENTMAX 50

void main()
{
	int Select;
	vector<string*> ptrStringList; //동적할당도 자료형 가능 //string의 주소값이 vector에 주소를 가진 백터
	string* studentTmp;
	while (1)
	{
		system("cls");
		cout << "===학생정보관리===(학생수 : " << ptrStringList.size() << "명)" << endl;
		cout << "   1.학생등록" << endl;
		cout << "   2.학생정보 보기" << endl;
		cout << "   3.종료" << endl;
		cout << " 입력 : " << endl;
		cin >> Select;
		switch (Select)
		{
		case 1:
			if (ptrStringList.size() < STUDENTMAX)
			{
				studentTmp = new string; //동적할당 주소 전달
				cout << ptrStringList.size() + 1 << "번 학생 이름 : ";
				cin >> *studentTmp; //값 받기
				ptrStringList.push_back(studentTmp);
			}
			break;
		case 2:
			for (int i = 0; i < ptrStringList.size(); i++)
				cout << i + 1 << "번 학생 : " << *(ptrStringList[i]) << endl; //*ptrStringList[i] 
																		 //ptrStringList[i]는 주소를 가진 배열
																		//*를 붙여서 값을 가리킨다
			system("pause");
			break;
		case 3:
			for (int i = 0; i < ptrStringList.size(); i++)
			{
				cout << *ptrStringList[i] << "학생" << endl;
				delete ptrStringList[i];
				cout << "할당 해제 완료" << endl;
			}
			ptrStringList.clear(); //clear()하는 이유 계속 써야하면 clear
			system("pause");
			return;
		}
	}
}


