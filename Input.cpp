#include "Input.h"

int Input::MainSelect()
{
	int input;

	//입력된 키의 정보를 읽어올 경우 getch()를 사용한다.
	while (true)
	{
		MapDraw::DrawPoint("선택 :     ", 0, 5);

		MapDraw::gotoxy(7, 5);
		std::cin >> input;

		switch (input)
		{
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		default:
			MapDraw::DrawPoint("잘못 입력 하셨습니다.", 0, 6);
			MapDraw::DrawPoint("                     ", 0, 6); //
			break;
		}
	}
}

std::string Input::InputCustomerName()
{
	std::string name;

	std::cout << "고객님의 이름을 입력하시오 : " << std::endl;
	MapDraw::gotoxy(29, 6);
	std::cin >> name;

	return name;
}

std::string Input::InputNewNews()
{
	//cin 은 입력을 받고 해당 값들을 변수에 넘겨줄때 마지막 
	//널문자 '\n' 는 버퍼에 남겨둔 채로 놔두기 때문에 해당 버퍼를 비워줄 필요가 있다.
	std::string sNews;

	std::cout << "새로운 기사 내용을 입력 하시오" << std::endl;
	std::cin.ignore(); //버퍼에 잔여 \n까지 가져와서 버퍼 비우기
	std::getline(std::cin, sNews);
	//std::cin.ignore(); //이 코드 작성했을 때 작동 되는 거 왜? 질문
	//string 라이브러리에 속해있다. 문자열 크기 지정X cin을 넣어 표준입력으로 사용, 두번째 인자 변수의 시작점. 세번째인자 제한자 혹은 구분자 디폴트'\n'
	
	return sNews;

	//char sNews[1000];
	//std::cin.ignore(); //버퍼에 잔여 \n까지 가져와서 버퍼 비우기
	//std::cin.getline(sNews, 1000, '\n'); //'\n' 엔터 //끝내고 버퍼에 엔터가 남는다.
}