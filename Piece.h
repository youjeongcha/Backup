#pragma once
#include "BitMapManager.h"
#include <vector>

enum ONELINE_MAXCOUNT
{//�� ���⿡�� ������ �ִ� Rect ��
	PAWN_LINE_COUNT = 1, //���� + �밢��
	PAWN_LINE_MAX_COUNT = 2, //ù��° ���� �̵�
	ROOK_LINE_COUNT = 7, //�� �� 7(���� ��ġ ����)
	KNIGHT_LINE_COUNT = 1, //����, ����, ����, ����, �ϵ�, �ϼ�, ����, ���� 1����
	BISHOP_LINE_COUNT = 7, //�밢�� �ִ� 7
	QUEEN_LINE_COUNT = 7, //������ �밢�� ��� 7
	KING_LINE_COUNT = 1, //�ڱ� �ֺ� 1
};

enum CAMP
{
	CAMP_NONE = -1,
	CAMP_BLACK,
	CAMP_WHITE,
	CAMP_COUNT,

	CAMP_PIECE_COUNT = 16,
};

//enum MOVESTATE
//{
//	CAN_FIRSTMOVE, //�ش� ���� ù��° �������� �ߴ��� �ľ�(��, ��(ĳ����))
//	ENPASSANT, //���Ļ��� ������ �� �ִ�(������ �ִ�) ����
//	//KING_CASTLING, //ĳ������ ������ �� �ִ�(ŷ�� ����)
//	NONE,
//
//	//FISTMOVE���� �⹰�� ������ ���� ENPASSANT�̳� KING_CATLEING�� ��ġ�� ��� �⹰���� NONE�� �����Ѵ�.
//};

class Piece
{
private:
protected: //private ���� �ϸ� �ڽĿ��� ���� �Ұ� > protected
	BitMap* m_pBitMap;
	BitMap* m_pBitMap_Move; //�̵� ǥ��
	bool m_moveCheck; //�̵� ǥ�� üũ ��û�� ���Դ���
	RECT m_BitMapRect;
	RECT m_moveRect; //�̵� ��ų rect �ӽ� �����
	std::vector<RECT> m_BitMapRect_MoveList;
	int m_iX; //map������ �ε���
	int m_iY;
	int move_iY; //BW �� �̵� ���� ����
	IMG m_Piece; //�ش� �⹰�� enum;
	CAMP m_CampColor; //�ش� �⹰�� ����
	bool firstMoveCheck; //ù��° �̵����� Ȯ��
	//MOVESTATE m_MoveState; //�̵� ��� ���� Ȯ��, ù��° �̵�, ���Ļ�, ĳ����, ��

public:
	Piece(const Piece& piece);
	Piece(BitMapManager& BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y);
	~Piece();

	//void Init(BitMapManager* BitMapMgr_Main, CAMP _campColor, IMG _Index, int _X, int _Y);
	//�̵� ������ ���� Ŭ���� ��� �Ǵ�
	bool ColliderCheck_Piece(POINT point);
	//�̵� ������ ĭ�� ��Ÿ�� �̹����� Ŭ���� ���
	bool ColliderCheck_Moveable(POINT point);

	//�̵� ������ ĭ���� �׸���.
	virtual void SetMoveableRect();
	void DrawMoveable(HDC hdc);
	//�⹰�� ���� �̵�
	void Move();
	void Draw(HDC hdc);


	void Set_XY(int _X, int _Y) { m_iX = _X; m_iY = _Y; }
	void Set_Inactive() {
		m_iX = -1; m_iY = -1; //ȭ��� ���� �ʵ���
		m_BitMapRect = { -1, -1, -1, -1 }; //Ŭ�� colliderCheck �ν�X�ϵ���
	}
	//�����¿� �� �� ���̽��� Rect��  m_BitMapRect_MoveList�� push
	void Set_Rect(CAMP map[][8], int move_iX, int move_iY, int count);

	bool Get_MoveCheck() { return m_moveCheck; }
	RECT Get_moveRect() { return m_moveRect; } //�� �� ������ ��ġ �ľ�
	RECT Get_BitMapRect() { return m_BitMapRect; } //�� �� ������ ��ġ �ľ�
	CAMP Get_CampColor() { return m_CampColor; }
	IMG Get_PieceType() { return m_Piece; } //�⹰�� ������ �Ǵ��ϱ� ����
	int Get_iX() { return m_iX; }
	int Get_iY() { return m_iY; }
};

