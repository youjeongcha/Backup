#include "UI.h"
#include "GameManager.h"

UI::UI()
{
	IMG sequence = IMG_MENU_TITLE_2;
	POINT star_XY;
	star_XY.x = IMG_STAR_X;
	star_XY.y = IMG_STAR_Y;
	
	//빨->노->파
	for (int count = 0; count < STAR_TOTAL_COUNT; count++)
	{
		//-----------------IMG를 m_StarList--------------------
		//별을 123순으로 받으면 ++로 한줄로 구성
		m_StarIMG_List.push_back(sequence);

		if (sequence == IMG_MENU_TITLE_4)
			sequence = IMG_MENU_TITLE_2;
		else
			sequence = (IMG)(sequence + 1);

		//-----------------POINT를 m_StarXY_List--------------------
		//top,right,bottom,left 배치를 위해서 별 하나하나의 좌표를 조정한다.
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
	m_ScoreTime = 0;
	m_UserLife = LIFE_MAX;
	m_Score = SCORE_START;
	m_Bonus = SCORE_BONUS;

	
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

bool UI::UpdateMenu(float deltaTime)
{
	UpdateStarFlow(deltaTime); //메뉴의 별 오른쪽 순회
	UpdateFlickering(deltaTime); //선택되어있는 항목 깜빡거리도록(검은 이미지를 덧씌우는 간격을 조정한다.

	if (UpdateKeyState_Enter(deltaTime)) //엔터 누르면 씬 전환 //함수를 bool형으로 UI안에서 해결한다.
		return true;
	return false;
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

		//왼쪽으로 순환
		m_StarIMG_List.push_back(m_StarIMG_List.front());
		
		m_StarIMG_List.erase(m_StarIMG_List.begin(), m_StarIMG_List.begin() + 1);
	}

	m_StarTime += deltaTime;
}

void UI::DrawStarFlow(HDC hdc)
{
	//빨->노->파
	for (int i = 0; i < m_StarIMG_List.size(); i++)
		BitMapMgr->GetImage(m_StarIMG_List[i])->DrawTransparent(hdc, m_StarXY_List[i].x, m_StarXY_List[i].y, IMG_STAR_W, IMG_STAR_H);
}

void UI::UpdateFlickering(float deltaTime)
{
	if (m_FlickeringTime >= FLICKERING_SPEED)
	{
		m_FlickeringTime = 0;

		m_NotDrawCheck = !m_NotDrawCheck; //true false 반대로 세팅
	}

	m_FlickeringTime += deltaTime;
}

void UI::DrawSelect(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_SELECT_1)->DrawTransparent(hdc, IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_W, IMG_SELECT_H);

	//1 PLAYER A ~ 2 PLAYERS B
	for (int i = 0; i < SELECT_PLAYER_COUNT; i++)
	{
		//i로 커서 위치와 i가 같고 m_NotDrawCheck가 true면 이번에는 해당 선택지를 그리지 않는다.(깜빡거림으로 나타남)
		if ( ! (i == m_Point_Y && m_NotDrawCheck == false))
			BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
	}
}

void UI::DrawPoint(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_POINT)->DrawTransparent(hdc, IMG_POINT_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * m_Point_Y), IMG_POINT_W, IMG_POINT_H);
}

bool UI::UpdateKeyState_Enter(float deltaTime)
{
	//space 키 누르면 끝도 없이 GGGG...GGGGetKeyState 무한 이동
	//&0x80 추가 GetAsyncKeyState와 동일한 움직임을 보이게 된다. GetAsyncKeyState와 결과값이 같아지게 된다
	
	if (m_PointMoveTime >= POINT_SPEED)
	{
		m_PointMoveTime = 0;

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) //엔터 누르면 씬 전환
			return true;
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
			KeyMoveSelect(MENU_KEY_UP); //m_Point_Y의 단위를 i로 잡는다. 범위 체크도 1~3 같은 식으로
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			KeyMoveSelect(MENU_KEY_DOWN);
	}
	
	m_PointMoveTime += deltaTime;

	return false;
}

void UI::KeyMoveSelect(int move_Y)
{
	m_Point_Y += move_Y;

	if (m_Point_Y < SELECT_PLAYER_1A) //위를 벗어나지 않게
		m_Point_Y = SELECT_PLAYER_1A;
	else if (m_Point_Y > SELECT_PLAYER_2B) //아래를 벗어나지 않게
		m_Point_Y = SELECT_PLAYER_2B;
}

//----------------게임----------------
void UI::DrawGame(HDC hdc)
{
	//상단 UI
	DrawScoreSpace(hdc);
	//score
	DrawScore(hdc);
	//목숨
	DrawLife(hdc);

}

void UI::UpdateGame(float deltaTime)
{
	//보너스 점수
	UpdateBonus(deltaTime);
}


//-----------점수 + 목숨 창------------

void UI::DrawScoreSpace(HDC hdc)
{
	BitMapMgr->GetImage(IMG_INTERFACE_SCORE_OUTLINE)->DrawTransparent(hdc, IMG_SCORE_OUTLINE_X, IMG_SCORE_OUTLINE_Y, IMG_SCORE_OUTLINE_W, IMG_SCORE_OUTLINE_H);
}

void UI::DrawScore(HDC hdc)
{
	std::wstring str;

	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255)); //글자 색 변경(흰색)

	SelectObject(hdc, GMMgr->Get_Font(FONT_STAGE));
	str = L"STAGE-01";
	TextOut(hdc, FONT_STAGE_X, FONT_STAGE_Y, str.c_str(), str.length());

	SelectObject(hdc, GMMgr->Get_Font(FONT_SCORE));
	str = L"SCORE-" + std::to_wstring(m_Score);
	TextOut(hdc, FONT_SCORE_X, FONT_SCORE_Y, str.c_str(), str.length());

	SetTextColor(hdc, RGB(219, 112, 147)); //글자 색 변경(붉은색)
	str = L"BONUS";// - ";// +std::to_wstring(m_Bonus);
	TextOut(hdc, FONT_BONUS_X, FONT_BONUS_Y, str.c_str(), str.length());

	SetTextColor(hdc, RGB(255, 255, 255)); //글자 색 변경(흰색)
	str = L"-" + std::to_wstring(m_Bonus);
	TextOut(hdc, FONT_BONUS_COUNTING_X, FONT_BONUS_Y, str.c_str(), str.length());
}

void UI::DrawLife(HDC hdc)
{
	for (int i = 0; i < m_UserLife; i++)
		BitMapMgr->GetImage(IMG_INTERFACE_LIFE)->DrawTransparent(hdc, IMG_Life_X + (i * IMG_Life_W), IMG_Life_Y, IMG_Life_W, IMG_Life_H);
}





void UI::UpdateBonus(float deltaTime)
{
	if (m_ScoreTime >= BONUS_SPEED)
	{
		m_ScoreTime = 0;
		m_Bonus -= SCORE_BONUS_REDUTION;

		if (m_Bonus <= 0)
			m_Bonus = 0;
	}

	m_ScoreTime += deltaTime;
}

