#include "News.h"
#include "Interface.h"
#include "Person.h"

#define stdMgr News::Get_Instance()

void main()
{
	Interface UI;

	while (true)
	{
		system("cls");

		switch (UI.MainMenu())
		{
		case 1: //고객 등록
			stdMgr->Observer_Add(new Person(UI.CustomerRegister())); //옵저버 추가 함수 
			//복사 생성자를 지정해둬서 string만 받아서 Observer를 상속받은 객체를 만들 수 있다.
			break;
		case 2: //News 전송(고객 News 시청)
			stdMgr->Observer_InfoUpdate(); //옵저버 정보 업데이트 함수
			break;
		case 3: //News 업데이트
			stdMgr->NewsUpdate(UI.NewsUpdate()); //News 정보 업데이트 함수
			break;
		case 4: //News 시청(고객 시청 기록 확인)
			stdMgr->Observer_InfoPrint();
			break;
		}
		system("pause");
	}
}