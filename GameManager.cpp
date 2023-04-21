#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_CreateType = SHAPE_CIRCLE;
	m_CreateTime = 5;
	srand(time(NULL));
}
GameManager::~GameManager()
{
	for (auto cList : m_CircleList)
	{
		delete cList;
	}
}

void GameManager::Init(HWND hWnd, HDC m_frontDC)
{
	RECT clientRect;

	m_HWND = hWnd;
	m_backDC = CreateCompatibleDC(m_frontDC); // 'Memory DC'
	//CreateCompatibleDC 함수를 사용해서 DC를 생성하면 이 DC와 연결된 비트맵 객체에는 그림이 그려지지만 화면에는 출력이 되지 않는다.
	//CreateCompatibleDC 함수로 만들어진 DC를 'Memory DC'라고 부른다.
	GetClientRect(m_HWND, &clientRect); //윈도우의 클라이언트의 영역을 알려준다.
	m_Window_WH.x = clientRect.right - clientRect.left;
	m_Window_WH.y = clientRect.bottom - clientRect.top;


	//도형 초기화
	//m_circle.Init(50, 50, 30);
	m_Box.Init(300, 50, 50, 50); ////////////////////////////
	//중력(아래로만 떨어지고 있기 때문)
	Gravity.y = GRAVITY_VALUE;
}

void GameManager::RandCreateShaoe(float deltaTime)
{
	//5초마다 번갈아가며 도형 생성
	if (m_CreateTime >= 5)
	{
		m_CreateTime = 0;
		int iRand = int(deltaTime) % 100; //맵의 최대 w으로 설정 ////////////////////////////

		switch (m_CreateType)
		{
		case SHAPE_CIRCLE:
		{
			//m_CreateType = SHAPE_BOX;

			Circle* newCircle = new Circle();
			newCircle->Init(50, 50, 30);
			m_CircleList.push_back(newCircle);
			break;
		}
		case SHAPE_BOX:
		{
			m_CreateType = SHAPE_CIRCLE;
			break;
		}
		}
	}
		m_CreateTime += deltaTime;
}


void GameManager::Update(float deltaTime)
{
	//도형 추가
	RandCreateShaoe(deltaTime);
	//Circle* newCircle = new Circle();
	//newCircle->Init(50, 50, 30);
	//m_CircleList.push_back(newCircle);

	//중력 가속도
	Vector2 _Gravity = Gravity * deltaTime;

	for (auto cList : m_CircleList)
	{
		cList->Set_GravityVelocity(_Gravity);
		cList->Update(deltaTime);
	}
	//m_circle.Set_GravityVelocity(_Gravity);
	//m_Box.Set_GravityVelocity(_Gravity);


	//m_circle.Update(deltaTime);
	//m_Box.Update(deltaTime);
}

void GameManager::Draw(HDC m_frontDC)
{
	//더블 버퍼링
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Window_WH.x, m_Window_WH.y); //TODO::임시 W H
	SelectObject(m_backDC, backBitmap);

	//도형 그리기
	for (auto cList : m_CircleList)
	{
		cList->Draw(m_backDC);
	}
	//m_circle.Draw(m_backDC);
	//m_Box.Draw(m_backDC);


	//더블 버퍼링
	BitBlt(m_frontDC, 0, 0, m_Window_WH.x, m_Window_WH.y, m_backDC, 0, 0, SRCCOPY);
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

