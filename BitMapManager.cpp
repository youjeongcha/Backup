#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[IMG_COUNT + 1];
}


void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	HDC hdc = GetDC(hWnd);
	int i = 0; //m_parrBitMap�� �����ϱ�����

	//Ÿ��Ʋ
	for (int j = 1; j <= IMG_MENU_TITLE_COUNT; j++)
	{
		sprintf_s(buf, "RES//title_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}

	//�޴�
	for (int j = 1; j <= IMG_MENU_SELECT_COUNT; j++)
	{
		sprintf_s(buf, "RES//menu_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}

	//����Ʈ
	sprintf_s(buf, "RES//point.bmp");
	m_parrBitMap[i++].Init(hdc, buf);

	//���
	for (int j = 1; j <= IMG_BG_COUNT; j++)
	{
		sprintf_s(buf, "RES//back_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}	
	
	//��(���ָӴ�)
	sprintf_s(buf, "RES//cash.bmp");
	m_parrBitMap[i++].Init(hdc, buf);
	
	//������
	sprintf_s(buf, "RES//goal.bmp");
	m_parrBitMap[i++].Init(hdc, buf);
	
	//�׾Ƹ�
	for (int j = 1; j <= IMG_OBJECT_POT_COUNT; j++)
	{
		sprintf_s(buf, "RES//fire_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}	
	
	//��
	for (int j = 1; j <= IMG_OBJECT_RING_COUNT; j++)
	{
		sprintf_s(buf, "RES//ring_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}

	//ĳ����
	for (int j = 1; j <= IMG_CHARACTER_COUNT; j++)
	{
		sprintf_s(buf, "RES//player_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}

	//UI (���� + �Ÿ� + ���)
	for (int j = 1; j <= IMG_INTERFACE_COUNT; j++)
	{
		sprintf_s(buf, "RES//interface_%d.bmp", j);
		m_parrBitMap[i++].Init(hdc, buf);
	}

	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
}