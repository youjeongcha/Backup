#include "UI.h"
#include "GameManager.h"

UI::UI()
{
	IMG sequence = IMG_MENU_TITLE_2;

	//��->��->��
	for (int count = 0; count < STAR_TOTAL_COUNT; count++)
	{
		//��TODO::123������ ������ ++�� ���� �ڵ� �����ϴ�
		m_StarList.push_back(sequence);

		//switch (sequence)
		//{
		//case STAR_RED:
		//	m_StarList.push_back(IMG_MENU_TITLE_2);
		//	break;
		//case STAR_YELLOW:
		//	m_StarList.push_back(IMG_MENU_TITLE_3);
		//	break;
		//case STAR_BLUE:
		//	m_StarList.push_back(IMG_MENU_TITLE_4);
		//	break;
		//}

		if (sequence == IMG_MENU_TITLE_4)
			sequence = IMG_MENU_TITLE_2;
		else
			sequence = (IMG)(sequence + 1);
	}

	m_Point_Y = SELECT_PLAYER_1A;
	m_NotDrawCheck = false;
	m_StarTime = 0;
	m_FlickeringTime = 0;

}

UI::~UI()
{
}

void UI::DrawMenu(HDC hdc)
{
	DrawTitle(hdc);
	DrawStarFlow(hdc);
	DrawSelect(hdc);
	//flickeringCheck �� �̿��ؼ� ������ ����
	//��TODO::�������� Draw�� ���� �ʴ� ������ �ذ��Ѵ�.
	//if (m_FlickeringCheck == true)
	//	DrawSelectBlack(hdc);
	DrawPoint(hdc);
}

void UI::DrawTitle(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_TITLE_START)->DrawTransparent(hdc, IMG_TITLE_X, IMG_TITLE_Y, IMG_TITLE_W, IMG_TITLE_H);
}

void UI::UpdateStarFlow(float deltaTime)
{
	if (m_StarTime >= STAR_SPEED)
	{
		m_StarTime = 0;

		//���������� ��ȯ
		m_StarList.push_front(m_StarList.back());
		m_StarList.pop_back();
	}

	m_StarTime += deltaTime;
}

void UI::DrawStarFlow(HDC hdc)
{
	float x = IMG_STAR_X;
	float y = IMG_STAR_Y;
	int count = 0;

	for (auto img : m_StarList)
	{
		//top,right,bottom,left ��ġ�� ���ؼ� �� �ϳ��ϳ��� ��ǥ�� �����Ѵ�.
		if (count < STAR_TOP)
		{
			x += IMG_STAR_W;
		}
		else if (count < STAR_RIGHT)
		{
			if (count == STAR_TOP)
			{
				x += IMG_STAR_W;
				y += IMG_STAR_H;
			}
			else
				y += IMG_STAR_H;
		}
		else if (count < STAR_BOTTOM)
		{
			if (count == STAR_RIGHT)
			{
				x -= IMG_STAR_W;
				y += IMG_STAR_H;
			}
			else
				x -= IMG_STAR_W;
		}
		else
		{
			if (count == STAR_BOTTOM)
			{
				x -= IMG_STAR_W;
				y -= IMG_STAR_H;
			}
			else
				y -= IMG_STAR_W;
		}

		//��->��->��
		BitMapMgr->GetImage(img)->DrawTransparent(hdc, x, y, IMG_STAR_W, IMG_STAR_H);

		count++;
	}
}

void UI::UpdateFlickering(float deltaTime)
{
	if (m_FlickeringTime >= FLICKERING_SPEED)
	{
		m_FlickeringTime = 0;

		m_NotDrawCheck = !m_NotDrawCheck; //true false �ݴ�� ����
	}

	m_FlickeringTime += deltaTime;
}

void UI::DrawSelect(HDC hdc)
{
	//PLAY SELECT
	BitMapMgr->GetImage(IMG_MENU_SELECT_1)->DrawTransparent(hdc, IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_W, IMG_SELECT_H);

	//1 PLAYER A ~ 2 PLAYERS B
	for (int i = 0; i < SELECT_PLAYER_COUNT; i++)
	{
		//��TODO::i�� Ŀ�� ��ġ�� i�� ������ �׸����� boolüũ �� �����̱�
		if ( ! (i == m_Point_Y && m_NotDrawCheck == false)) //TODO::��Ī ����
			BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
		//{
		//	if (m_FlickeringCheck == false) //TODO::��Ī ����
		//	{
		//		//��TODO::i�� Ŀ�� ��ġ�� i�� ������ �׸����� boolüũ �� �����̱�
		//		BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
		//	}
		//}
		//else
		//	BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
	}
}

//void UI::DrawSelectBlack(HDC hdc)
//{//��TODO::m_Point_Y�� i����. ���� ������ �ٲ㼭 �ʱ���ġy + ��³��� * i�� �ذ��Ѵ�.
//	BitMapMgr->GetImage(IMG_MENU_SELECT_6)->Draw(hdc, IMG_SELECT_PLAYER_X, m_Point_Y, IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
//}

void UI::DrawPoint(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_POINT)->DrawTransparent(hdc, IMG_POINT_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * m_Point_Y), IMG_POINT_W, IMG_POINT_H);
}

bool UI::KeyState_PointEnter()
{//�ڰ���
	//space Ű ������ ���� ���� GGGG...GGGGetKeyState ���� �̵�
	//&0x80 �߰� GetAsyncKeyState�� ������ �������� ���̰� �ȴ�. GetAsyncKeyState�� ������� �������� �ȴ�

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) //���� ������ �� ��ȯ
		return true;
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
		KeyMove(MENU_KEY_UP);
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		KeyMove(MENU_KEY_DOWN);

	return false;
}

void UI::KeyMove(int move_Y)
{//��TODO::m_Point_Y�� ������ i�� ��´�. ���� üũ�� 1~3 ���� ������
	m_Point_Y += move_Y;

	if (m_Point_Y < SELECT_PLAYER_1A) //���� ����� �ʰ�
		m_Point_Y = SELECT_PLAYER_1A;
	else if (m_Point_Y > SELECT_PLAYER_2B) //�Ʒ��� ����� �ʰ�
		m_Point_Y = SELECT_PLAYER_2B;
}



//-----------���� + ��� â----------------------------

void UI::DrawScoreSpace(HDC hdc)
{
	BitMapMgr->GetImage(IMG_INTERFACE_SCORE_OUTLINE)->DrawTransparent(hdc, IMG_SCORE_OUTLINE_X, IMG_SCORE_OUTLINE_Y, IMG_SCORE_OUTLINE_W, IMG_SCORE_OUTLINE_H);
}

void UI::DrawScore(HDC hdc)
{
}

void UI::DrawBonus(HDC hdc)
{
}

void UI::DrawLife(HDC hdc)
{
}

void UI::DrawStage(HDC hdc)
{
}
