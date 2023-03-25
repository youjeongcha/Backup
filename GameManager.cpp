#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_scene = SCENE_MENU;
}


GameManager::~GameManager()
{
	//삭제는 생성된 역순으로
	DeleteDC(m_backDC);
	ReleaseDC(m_HWND, m_frontDC);
}

void GameManager::init(HWND hWnd)
{
	RECT clientRect;

	m_HWND = hWnd;
	m_frontDC = GetDC(m_HWND);
	m_backDC = CreateCompatibleDC(m_frontDC);
	//CreateCompatibleDC 함수를 사용해서 DC를 생성하면 이 DC와 연결된 비트맵 객체에는 그림이 그려지지만 화면에는 출력이 되지 않는다.
	//CreateCompatibleDC 함수로 만들어진 DC를 'Memory DC'라고 부른다.
	GetClientRect(m_HWND, &clientRect); //윈도우의 클라이언트의 영역을 알려준다.
	m_Widht_Height.x = clientRect.right - clientRect.left;
	m_Widht_Height.y = clientRect.bottom - clientRect.top;

	BitMapMgr->Init(hWnd);
}

void GameManager::Update(float deltaTime)
{
	float thisTurn_MoveDistance;

	switch (m_scene)
	{
	case SCENE_MENU:
		if (m_UI.UpdateMenu(deltaTime)) //엔터 누르면 씬 전환 //함수를 bool형으로 UI안에서 해결한다.
			m_scene = SCENE_GAME;

		break;
	case SCENE_GAME:
		
		m_UI.UpdateGame(deltaTime);

		thisTurn_MoveDistance = character.Update(deltaTime);

		//if (thisTurn_MoveDistance != 0) //캐릭터 좌표
		{
			//TODO::Goal이 특정 좌표에 오기 전까지는 배경을 움직인다.(뒤로가서 골이 멀어지면 다시 배경 이동으로 전환한다.)
			m_Draw.UpdateBack(deltaTime, thisTurn_MoveDistance); //back 관중+코끼리 왼쪽 순회
		}

		break;
	default:
		break;
	}
}


//bool GameManager::KeyInputCheck()
//{
//	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
//		return true;
//	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//		return true;
//	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//		return true;
//	return false;
//}



/*GM의 Draw에서 backDC에 비트맵의 정보를 지정해서
MapDraw나 UI에서 backDC로 backBitmap에 그린다.(backDC는 붓)
BitMap에서 memDC(이미지 하나하나마다의 붓)*/
void GameManager::Draw()
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Widht_Height.x, m_Widht_Height.y);

	SelectObject(m_backDC, backBitmap);

	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_backDC);
		break;
	case SCENE_GAME:
		m_Draw.DrawMap(m_backDC);	//배경
		m_UI.DrawGame(m_backDC);	//UI
		character.Draw(m_backDC);	//캐릭터
		break;
	default:
		break;
	}

	//더블 버퍼링
	BitBlt(m_frontDC, 0, 0, m_Widht_Height.x, m_Widht_Height.y, m_backDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}



//더블 버퍼링
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //너비, 비트맵의 가로 픽셀 수
	bm_info.bmiHeader.biHeight = height; //높이, 비트맵의 세로 픽셀 수
	bm_info.bmiHeader.biPlanes = 1; //1로 고정, 반드시 1이어야 한다

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}