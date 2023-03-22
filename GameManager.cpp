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
	m_HWND = hWnd;
	m_frontDC = GetDC(m_HWND);
	m_backDC = CreateCompatibleDC(m_frontDC);
	//CreateCompatibleDC 함수를 사용해서 DC를 생성하면 이 DC와 연결된 비트맵 객체에는 그림이 그려지지만 화면에는 출력이 되지 않는다.
	//CreateCompatibleDC 함수로 만들어진 DC를 'Memory DC'라고 부른다.
	GetClientRect(m_HWND, &m_clientRect); //윈도우의 클라이언트의 영역을 알려준다.

	BitMapMgr->Init(hWnd);
}

void GameManager::Update(float deltaTime)
{
	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.UpdateStarFlow(deltaTime); //메뉴의 별 오른쪽 순회
		m_UI.UpdateFlickering(deltaTime); //선택되어있는 항목 깜빡거리도록(검은 이미지를 덧씌우는 간격을 조정한다.

		if (m_UI.KeyState_PointEnter()) //엔터 누르면 씬 전환 //함수를 bool형으로 UI안에서 해결한다.
			m_scene = SCENE_GAME;

		break;
	case SCENE_GAME:
		m_Draw.UpdateBack(deltaTime); //back 관중+코끼리 왼쪽 순회
		character.UpdateIMG(deltaTime); //캐릭터 IMG
		character.Update_XY(deltaTime); //캐릭터 좌표

		//★TODO::캐릭터 안에서 조정한다
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{

		}
		break;
	default:
		break;
	}
}

/*GM의 Draw에서 backDC에 비트맵의 정보를 지정해서
MapDraw나 UI에서 backDC로 backBitmap에 그린다.(backDC는 붓)
BitMap에서 memDC(이미지 하나하나마다의 붓)*/
void GameManager::Draw()
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_clientRect.right + 1, m_clientRect.bottom + 1);
	SelectObject(m_backDC, backBitmap);

	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_backDC);
		break;
	case SCENE_GAME:
		//잔디
		m_Draw.DrawGrass(m_backDC);
		//관중 + 코끼리
		m_Draw.DrawBack(m_backDC);
		//상단 UI
		m_UI.DrawScoreSpace(m_backDC);
		//목숨
		m_UI.DrawLife(m_backDC);

		//캐릭터
		character.Draw(m_backDC);
		break;
	default:
		break;
	}

	//더블 버퍼링
	BitBlt(m_frontDC, 0, 0, m_clientRect.right + 1, m_clientRect.bottom + 1, m_backDC, 0, 0, SRCCOPY);
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