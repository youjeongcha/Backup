#include "GameManager.h"

GameManager* GameManager::m_pInstance = NULL;

GameManager::GameManager()
{
	m_scene = SCENE_MENU;
}

GameManager::~GameManager()
{
	ReleaseDC(m_HWND, m_fDC);
	ReleaseDC(m_HWND, m_bDC);
}

void GameManager::init(HWND hWnd)
{
	m_HWND = hWnd;
	m_fDC = GetDC(m_HWND);
	m_bDC = GetDC(m_HWND);

	BitMapMgr->Init(hWnd);
}

void GameManager::Update(float deltaTime)
{
	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.UpdateStarFlow(deltaTime); //�޴��� �� ������ ��ȸ
		break;
	case SCENE_GAME:
		m_Draw.UpdateBack(deltaTime); //back ����+�ڳ��� ���� ��ȸ
		break;
	default:
		break;
	}
}

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
		break;
	default:
		break;
	}


	//���� ���۸�
	BitBlt(m_fDC, 0, 0, m_clientRect.right + 1, m_clientRect.bottom + 1, m_bDC, 0, 0, SRCCOPY);
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