#include "Input.h"

int Input::MainSelect()
{
	int input;

	//�Էµ� Ű�� ������ �о�� ��� getch()�� ����Ѵ�.
	while (true)
	{
		MapDraw::DrawPoint("���� :     ", 0, 5);

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
			MapDraw::DrawPoint("�߸� �Է� �ϼ̽��ϴ�.", 0, 6);
			MapDraw::DrawPoint("                     ", 0, 6); //
			break;
		}
	}
}

std::string Input::InputCustomerName()
{
	std::string name;

	std::cout << "������ �̸��� �Է��Ͻÿ� : " << std::endl;
	MapDraw::gotoxy(29, 6);
	std::cin >> name;

	return name;
}

std::string Input::InputNewNews()
{
	//cin �� �Է��� �ް� �ش� ������ ������ �Ѱ��ٶ� ������ 
	//�ι��� '\n' �� ���ۿ� ���ܵ� ä�� ���α� ������ �ش� ���۸� ����� �ʿ䰡 �ִ�.
	std::string sNews;

	std::cout << "���ο� ��� ������ �Է� �Ͻÿ�" << std::endl;
	std::cin.ignore(); //���ۿ� �ܿ� \n���� �����ͼ� ���� ����
	std::getline(std::cin, sNews);
	//std::cin.ignore(); //�� �ڵ� �ۼ����� �� �۵� �Ǵ� �� ��? ����
	//string ���̺귯���� �����ִ�. ���ڿ� ũ�� ����X cin�� �־� ǥ���Է����� ���, �ι�° ���� ������ ������. ����°���� ������ Ȥ�� ������ ����Ʈ'\n'
	
	return sNews;

	//char sNews[1000];
	//std::cin.ignore(); //���ۿ� �ܿ� \n���� �����ͼ� ���� ����
	//std::cin.getline(sNews, 1000, '\n'); //'\n' ���� //������ ���ۿ� ���Ͱ� ���´�.
}