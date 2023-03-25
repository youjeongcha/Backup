#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_scene = SCENE_MENU;
}


GameManager::~GameManager()
{
	//������ ������ ��������
	DeleteDC(m_backDC);
	ReleaseDC(m_HWND, m_frontDC);
}

void GameManager::init(HWND hWnd)
{
	RECT clientRect;

	m_HWND = hWnd;
	m_frontDC = GetDC(m_HWND);
	m_backDC = CreateCompatibleDC(m_frontDC);
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	GetClientRect(m_HWND, &clientRect); //�������� Ŭ���̾�Ʈ�� ������ �˷��ش�.
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
		if (m_UI.UpdateMenu(deltaTime)) //���� ������ �� ��ȯ //�Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
			m_scene = SCENE_GAME;

		break;
	case SCENE_GAME:
		
		m_UI.UpdateGame(deltaTime);

		thisTurn_MoveDistance = character.Update(deltaTime);

		//if (thisTurn_MoveDistance != 0) //ĳ���� ��ǥ
		{
			//TODO::Goal�� Ư�� ��ǥ�� ���� �������� ����� �����δ�.(�ڷΰ��� ���� �־����� �ٽ� ��� �̵����� ��ȯ�Ѵ�.)
			m_Draw.UpdateBack(deltaTime, thisTurn_MoveDistance); //back ����+�ڳ��� ���� ��ȸ
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



/*GM�� Draw���� backDC�� ��Ʈ���� ������ �����ؼ�
MapDraw�� UI���� backDC�� backBitmap�� �׸���.(backDC�� ��)
BitMap���� memDC(�̹��� �ϳ��ϳ������� ��)*/
void GameManager::Draw()
{
	//���� ���۸�
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_Widht_Height.x, m_Widht_Height.y);

	SelectObject(m_backDC, backBitmap);

	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_backDC);
		break;
	case SCENE_GAME:
		m_Draw.DrawMap(m_backDC);	//���
		m_UI.DrawGame(m_backDC);	//UI
		character.Draw(m_backDC);	//ĳ����
		break;
	default:
		break;
	}

	//���� ���۸�
	BitBlt(m_frontDC, 0, 0, m_Widht_Height.x, m_Widht_Height.y, m_backDC, 0, 0, SRCCOPY);
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