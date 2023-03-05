#include "Stone.h"



void Stone::SetPosition(int _ix, int _iy, string _strShape) {
	m_ix = _ix;
	m_iy = _iy;
	m_strShape = _strShape;
}

void Stone::DrawUndoStone()
{//������ �� ǥ��
	if(m_ix != - 1 && m_iy != -1) //���ǽ� ��?
		DrawManager::DrawPoint("��", m_ix, m_iy);
}

void Stone::DrawStone()
{//����. �̷� ���·� �� ���ó ��Ȯ�ϰ� 
	DrawManager::DrawPoint(m_strShape, m_ix, m_iy);
}
void Stone::EraseStone(int _iWidth, int _iHeight)
{
	DrawManager::ErasePanel(m_ix, m_iy,_iWidth,_iHeight);
}


bool Stone::Compare(Stone stone) //�ڱ� class ��ü�� �̿��ϴ� �� ����
{//�� �� �� �ִ��� ������ ��? //���ʵ� -1�� �̿��ϴ� ������ ��Ȱ��ȭ ������ �Ǵ�
	if (m_ix != -1 && m_iy != -1 && m_ix == stone.m_ix && m_iy == stone.m_iy)
	{
		return true;
	}
	else return false;
}

bool Stone::Compare(int _ix, int _iy)
{//��ǥ ��

	if (m_ix != -1 && m_iy != -1 && m_ix == _ix && m_iy == _iy)
	{
		return true;
	}
	else return false;
}

void Stone::Disable(int _iWidth, int _iHeight,bool EraseStatus)
{ //disable�� ���� ��Ȱ��ȭ ��ǥ�� �������� �ʴ� -1��
	if(m_ix != -1 && m_iy != -1 && EraseStatus) // == ������ EraseStatus�� true�� �۵�
		EraseStone(_iWidth, _iHeight);
	m_ix = -1; 
	m_iy = -1; 
}

Stone::Stone()
{
	m_ix = -1;
	m_iy = -1;
}

Stone::Stone(int _ix, int _iy)
{
	m_ix = _ix;
	m_iy = _iy;
}
Stone::~Stone()
{

}