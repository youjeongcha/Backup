#include "UI.h"
#include "GameManager.h"

UI::UI()
{
	IMG sequence = IMG_MENU_TITLE_2;
	POINT star_XY;
	star_XY.x = IMG_STAR_X;
	star_XY.y = IMG_STAR_Y;
	
	//��->��->��
	for (int count = 0; count < STAR_TOTAL_COUNT; count++)
	{
		//-----------------IMG�� m_StarList--------------------
		//���� 123������ ������ ++�� ���ٷ� ����
		m_StarIMG_List.push_back(sequence);

		if (sequence == IMG_MENU_TITLE_4)
			sequence = IMG_MENU_TITLE_2;
		else
			sequence = (IMG)(sequence + 1);

		//-----------------POINT�� m_StarXY_List--------------------
		//top,right,bottom,left ��ġ�� ���ؼ� �� �ϳ��ϳ��� ��ǥ�� �����Ѵ�.
		if (count < STAR_TOP)
			star_XY.x += IMG_STAR_W;
		else if (count < STAR_RIGHT)
		{
			if (count == STAR_TOP)
			{
				star_XY.x += IMG_STAR_W;
				star_XY.y += IMG_STAR_H;
			}
			else
				star_XY.y += IMG_STAR_H;
		}
		else if (count < STAR_BOTTOM)
		{
			if (count == STAR_RIGHT)
			{
				star_XY.x -= IMG_STAR_W;
				star_XY.y += IMG_STAR_H;
			}
			else
				star_XY.x -= IMG_STAR_W;
		}
		else
		{
			if (count == STAR_BOTTOM)
			{
				star_XY.x -= IMG_STAR_W;
				star_XY.y -= IMG_STAR_H;
			}
			else
				star_XY.y -= IMG_STAR_W;
		}
		m_StarXY_List.push_back(star_XY);
	}

	m_Point_Y = SELECT_PLAYER_1A;
	m_NotDrawCheck = false;
	m_StarTime = 0;
	m_FlickeringTime = 0;
	m_UserLife = LIFE_MAX;
}

UI::~UI()
{
}

void UI::DrawMenu(HDC hdc)
{
	DrawTitle(hdc);
	DrawStarFlow(hdc);
	DrawSelect(hdc);
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

		//�������� ��ȯ
		m_StarIMG_List.push_back(m_StarIMG_List.front());
		
		m_StarIMG_List.erase(m_StarIMG_List.begin(), m_StarIMG_List.begin() + 1);
	}

	m_StarTime += deltaTime;
}

void UI::DrawStarFlow(HDC hdc)
{
	//��->��->��
	for (int i = 0; i < m_StarIMG_List.size(); i++)
		BitMapMgr->GetImage(m_StarIMG_List[i])->DrawTransparent(hdc, m_StarXY_List[i].x, m_StarXY_List[i].y, IMG_STAR_W, IMG_STAR_H);
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
	BitMapMgr->GetImage(IMG_MENU_SELECT_1)->DrawTransparent(hdc, IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_W, IMG_SELECT_H);

	//1 PLAYER A ~ 2 PLAYERS B
	for (int i = 0; i < SELECT_PLAYER_COUNT; i++)
	{
		//i�� Ŀ�� ��ġ�� i�� ���� m_NotDrawCheck�� true�� �̹����� �ش� �������� �׸��� �ʴ´�.(�����Ÿ����� ��Ÿ��)
		if ( ! (i == m_Point_Y && m_NotDrawCheck == false))
			BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
	}
}

void UI::DrawPoint(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_POINT)->DrawTransparent(hdc, IMG_POINT_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * m_Point_Y), IMG_POINT_W, IMG_POINT_H);
}

bool UI::KeyState_PointEnter(float deltaTime)
{
	//space Ű ������ ���� ���� GGGG...GGGGetKeyState ���� �̵�
	//&0x80 �߰� GetAsyncKeyState�� ������ �������� ���̰� �ȴ�. GetAsyncKeyState�� ������� �������� �ȴ�
	
	if (m_PointMoveTime >= POINT_SPEED)
	{
		m_PointMoveTime = 0;

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) //���� ������ �� ��ȯ
			return true;
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
			KeyMove(MENU_KEY_UP); //m_Point_Y�� ������ i�� ��´�. ���� üũ�� 1~3 ���� ������
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			KeyMove(MENU_KEY_DOWN);
	}
	
	m_PointMoveTime += deltaTime;

	return false;
}

void UI::KeyMove(int move_Y)
{
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
	for (int i = 0; i < m_UserLife; i++)
		BitMapMgr->GetImage(IMG_INTERFACE_LIFE)->DrawTransparent(hdc, IMG_Life_X + (i * IMG_Life_W), IMG_Life_Y, IMG_Life_W, IMG_Life_H);
}