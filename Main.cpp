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
		case 1: //�� ���
			stdMgr->Observer_Add(new Person(UI.CustomerRegister())); //������ �߰� �Լ� 
			//���� �����ڸ� �����صּ� string�� �޾Ƽ� Observer�� ��ӹ��� ��ü�� ���� �� �ִ�.
			break;
		case 2: //News ����(�� News ��û)
			stdMgr->Observer_InfoUpdate(); //������ ���� ������Ʈ �Լ�
			break;
		case 3: //News ������Ʈ
			stdMgr->NewsUpdate(UI.NewsUpdate()); //News ���� ������Ʈ �Լ�
			break;
		case 4: //News ��û(�� ��û ��� Ȯ��)
			stdMgr->Observer_InfoPrint();
			break;
		}
		system("pause");
	}
}