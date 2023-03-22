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
	m_HWND = hWnd;
	m_frontDC = GetDC(m_HWND);
	m_backDC = CreateCompatibleDC(m_frontDC);
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

		if (m_UI.KeyState_PointEnter()) //���� ������ �� ��ȯ //�Լ��� bool������ UI�ȿ��� �ذ��Ѵ�.
			m_scene = SCENE_GAME;

		break;
	case SCENE_GAME:
		m_Draw.UpdateBack(deltaTime); //back ����+�ڳ��� ���� ��ȸ
		character.UpdateIMG(deltaTime); //ĳ���� IMG
		character.Update_XY(deltaTime); //ĳ���� ��ǥ

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
	HBITMAP backBitmap = MyCreateDIBSection(m_frontDC, m_clientRect.right + 1, m_clientRect.bottom + 1);
	SelectObject(m_backDC, backBitmap);

	switch (m_scene)
	{
	case SCENE_MENU:
		m_UI.DrawMenu(m_backDC);
		break;
	case SCENE_GAME:
		//�ܵ�
		m_Draw.DrawGrass(m_backDC);
		//���� + �ڳ���
		m_Draw.DrawBack(m_backDC);
		//��� UI
		m_UI.DrawScoreSpace(m_backDC);
		//���
		m_UI.DrawLife(m_backDC);

		//ĳ����
		character.Draw(m_backDC);
		break;
	default:
		break;
	}

	//���� ���۸�
	BitBlt(m_frontDC, 0, 0, m_clientRect.right + 1, m_clientRect.bottom + 1, m_backDC, 0, 0, SRCCOPY);
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