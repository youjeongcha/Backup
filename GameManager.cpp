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
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	GetClientRect(m_HWND, &clientRect); //�������� Ŭ���̾�Ʈ�� ������ �˷��ش�.
	m_Window_WH.x = clientRect.right - clientRect.left;
	m_Window_WH.y = clientRect.bottom - clientRect.top;


	//���� �ʱ�ȭ
	//m_circle.Init(50, 50, 30);
	m_Box.Init(300, 50, 50, 50); ////////////////////////////
	//�߷�(�Ʒ��θ� �������� �ֱ� ����)
	Gravity.y = GRAVITY_VALUE;
}

void GameManager::RandCreateShaoe(float deltaTime)
{
	//5�ʸ��� �����ư��� ���� ����
	if (m_CreateTime >= 5)
	{
		m_CreateTime = 0;
		int iRand = int(deltaTime) % 100; //���� �ִ� w���� ���� ////////////////////////////

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
	//���� �߰�
	RandCreateShaoe(deltaTime);
	//Circle* newCircle = new Circle();
	//newCircle->Init(50, 50, 30);
	//m_CircleList.push_back(newCircle);

	//�߷� ���ӵ�
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
	//���� ���۸�
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Window_WH.x, m_Window_WH.y); //TODO::�ӽ� W H
	SelectObject(m_backDC, backBitmap);

	//���� �׸���
	for (auto cList : m_CircleList)
	{
		cList->Draw(m_backDC);
	}
	//m_circle.Draw(m_backDC);
	//m_Box.Draw(m_backDC);


	//���� ���۸�
	BitBlt(m_frontDC, 0, 0, m_Window_WH.x, m_Window_WH.y, m_backDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}



//���� ���۸�
HBITMAP GameManager::MyCreateDIBSection(HDC hdc, int width, int height)
{
	BITMAPINFO bm_info;
	ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));

	bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//color bits : 1, 4, 8, 16, 24, 32
	//1:���, 4:16��, 8:256��, 16:2^15��, 24,31:2^24��
	bm_info.bmiHeader.biBitCount = 24;
	bm_info.bmiHeader.biWidth = width; //�ʺ�, ��Ʈ���� ���� �ȼ� ��
	bm_info.bmiHeader.biHeight = height; //����, ��Ʈ���� ���� �ȼ� ��
	bm_info.bmiHeader.biPlanes = 1; //1�� ����, �ݵ�� 1�̾�� �Ѵ�

	LPVOID pBits;
	return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}

