#include<iostream>
#include<Windows.h>
#include"Figure.h"
#include"Triangle.h"
#include"circle.h"
#include"Quadrangle.h"
using namespace std;

Figure* SelectFigure() //포인터 사용은 => 자식의 주소를 부모 포인터로 업캐스팅 을 해서 리턴을 하겠다
{
	system("cls");
	int select;
	Figure* tmp;//자식의 주소를 부모로 업캐스팅?
	cout << "=== 도형 선택 ===" << endl;
	cout << "  1. 일반 도형" << endl;
	cout << "  2. 삼각형" << endl;
	cout << "  3. 사각형" << endl;
	cout << "  4. 원형" << endl;
	cin >> select;

	switch (select)
	{
	case 1:
		tmp = new Figure;
		break;
	case 2:
		tmp = new Triangle;
		break;
	case 3:
		tmp = new Quadrangle;
	case 4:
		tmp = new circle;
		break;
	}
	tmp->SetSize();//오버라이딩
	return tmp;
}

void Show_Figure(Figure* figure_list[]) //도형 전체 그리는 코드
{
	int i;
	for (i = 0; figure_list[i] != NULL; i++)
		figure_list[i]->Draw(); //오버라이딩
	if (i == 0)
		cout << " 등록된 도형이 없습니다." << endl;
	system("pause");
}

void Exit() //5초 맞춰서 종료하는 코드
{
	for (int i = 5; i >= 0; i--)
	{
		system("cls");
		cout << "종료 합니다." << endl;
		cout << i << "초전" << endl;
		Sleep(1000);
	}
	exit(1); //강제 종료
}

void main()
{
	Figure* figure_list[50] = { NULL };
	int select;
	while (1)
	{
		system("cls");
		cout << "=== 도형 그리기 ===" << endl;
		cout << "  1. 도형 추가" << endl;
		cout << "  2. 도형 전체 그리기" << endl;
		cout << "  3. 종료 " << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			int i;
			for (i = 0; i < 50; i++)
			{
				if (figure_list[i] == NULL) //리스트 크기만큼 반복문 돌게끔
					break;
			}
			figure_list[i] = SelectFigure();
			break;
		case 2:
			Show_Figure(figure_list);
			break;
		case 3: //도형은 figure_list가 비기 전까지 전부 삭제
			for (i = 0; i < 50; i++)
			{
				if (figure_list[i] != NULL)
					delete figure_list[i];
			}
			Exit(); //5초 맞춰서 종료하는 코드
			break;
		default:
			break;
		}
	}
}