#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_scene = SCENE_MENU;
}

GameManager::~GameManager()
{
	//�ڻ����� ������ ��������
	DeleteDC(m_bDC);
	ReleaseDC(m_HWND, m_fDC);
}

void GameManager::init(HWND hWnd)
{
	m_HWND = hWnd;
	m_fDC = GetDC(m_HWND);
	m_bDC = CreateCompatibleDC(m_fDC);
	//CreateCompatibleDC �Լ��� ����ؼ� DC�� �����ϸ� �� DC�� ����� ��Ʈ�� ��ü���� �׸��� �׷������� ȭ�鿡�� ����� ���� �ʴ´�.
	//CreateCompatibleDC �Լ��� ������� DC�� 'Memory DC'��� �θ���.
	GetClientRect(m_HWND, &m_clientRect); //�������� Ŭ���̾�Ʈ�� ������ �˷��ش�.

	BitMapMgr->Init(hWnd);
}

void GameManager::Update(float deltaTime)
{
	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.UpdateStarFlow(deltaTime); //�޴��� �� ������ ��ȸ
		m_UI.UpdateFlickering(deltaTime); //���õǾ��ִ� �׸� �����Ÿ�����(���� �̹����� ������� ������ �����Ѵ�.

		//���Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
		if (m_UI.KeyState_PointEnter()) //���� ������ �� ��ȯ
			m_scene = SCENE_GAME;

		break;
	case SCENE_GAME:
		m_Draw.UpdateBack(deltaTime); //back ����+�ڳ��� ���� ��ȸ

		//��TODO::ĳ���� �ȿ��� �����Ѵ�
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{

		}
		break;
	default:
		break;
	}
}

/*GM�� Draw���� backDC�� ��Ʈ���� ������ �����ؼ�
MapDraw�� UI���� backDC�� backBitmap�� �׸���.(backDC�� ��)
BitMap���� memDC(�̹��� �ϳ��ϳ������� ��)*/
void GameManager::Draw()
{
	//���� ���۸�
	HBITMAP backBitmap = MyCreateDIBSection(m_fDC, m_clientRect.right + 1, m_clientRect.bottom + 1);
	SelectObject(m_bDC, backBitmap);

	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_bDC);
		break;
	case SCENE_GAME:
		//�ܵ�
		m_Draw.DrawGrass(m_bDC);
		//���� + �ڳ���
		m_Draw.DrawBack(m_bDC);
		//��� UI
		m_UI.DrawScoreSpace(m_bDC);
		break;
	default:
		break;
	}


	//���� ���۸�
	BitBlt(m_fDC, 0, 0, m_clientRect.right + 1, m_clientRect.bottom + 1, m_bDC, 0, 0, SRCCOPY);
	DeleteObject(backBitmap);
}

////Ű ����
//void GameManager::KeyState()
//{
//	switch (m_scene)
//	{
//	case SCENE_MENU:
//		//space Ű ������ ���� ���� GGGG...GGGGetKeyState ���� �̵�
//		//&0x80 �߰� GetAsyncKeyState�� ������ �������� ���̰� �ȴ�. GetAsyncKeyState�� ������� �������� �ȴ�
//		//��TODO::�Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
//		if (GetAsyncKeyState(VK_RETURN) & 0x8000) //���� ������ �� ��ȯ
//			m_scene = SCENE_GAME;
//		else
//			m_UI.KeyStatePoint();
//
//
//		//if (GetAsyncKeyState(VK_UP) & 0x8000)
//		//	m_UI.KeyStatePoint(-IMG_POINT_H);
//		//else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
//		//	m_UI.KeyStatePoint(+IMG_POINT_H);
//		//else if (GetAsyncKeyState(VK_RETURN) & 0x8000) //���� ������ �� ��ȯ
//		//	m_scene = SCENE_GAME;
//		break;
//	case SCENE_GAME:
//		//��TODO::ĳ���� �ȿ��� �����Ѵ�
//		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
//		{
//
//		}
//		break;
//	default:
//		break;
//	}
//
//}


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