#pragma once

#include <Windows.h>

#pragma pack(1)

enum PacketType
{
	PacketType_BasePacket, //�⺻
	PacketType_SetTeam, //�� ����
	PacketType_SetTurn, //�� ��ȯ
	PacketType_MoveObject,//�⺻ �̵�
	PacketType_MovePromotionObject,//�� - ���� �� �̵�
	PacketType_Promotion, //����
	PacketType_WinCheck, //�¸� üũ
	
};

enum CAMP
{
	CAMP_NONE = -1,
	CAMP_BLACK,
	CAMP_WHITE,
	CAMP_COUNT,

	CAMP_PIECE_COUNT = 16,
};

enum PROMOTION_RECT
{
	PROMOTION_RECT_L = 0,
	PROMOTION_RECT_T = 25,
	PROMOTION_RECT_R = PROMOTION_RECT_L + 120,
	PROMOTION_RECT_B = PROMOTION_RECT_T + 30,

	PROMOTION_RECT_GAP = 30,


	PROMOTION_ROOK_T = PROMOTION_RECT_T,
	PROMOTION_KNIGHT_T = PROMOTION_ROOK_T + PROMOTION_RECT_GAP,
	PROMOTION_BISHOP_T = PROMOTION_KNIGHT_T + PROMOTION_RECT_GAP,
	PROMOTION_QUEEN_T = PROMOTION_BISHOP_T + PROMOTION_RECT_GAP,

	PROMOTION_FONTSIZE = 11,
};


struct BASEPACKET
{
	PacketType packetType = PacketType_BasePacket;
	int packetSize;


	//BASEPACKET(PacketType type) : packetType(type) {}
};

struct SETTEAMPACKET : BASEPACKET
{
	CAMP playerTeam;


	//�̷��� �� ���� �ִµ� ��õ���� ����
	// ��Ŷ �����Ҷ����� ���� �ʱ�ȭ���ִ� ���� ������̰� ����
	//BASEPACKET�� �����ڿ��� ���ڷ� ���޹��� ���� ����Ͽ� packetType�� ����
	//SETTEAM() : BASEPACKET(PacketType_SetTeam) {}
};

struct SETTURNPACKET : BASEPACKET
{
	CAMP setTurn;
};


//�̵��� ��ǥ(m_iX�ε���) + �̵��� ��ǥ(Rect)�� ����
struct MOVEOBJECTPACKET : SETTURNPACKET
{
	//m_iX�� m_iY�� �����ؼ� ������ ��ġ�� �˷��ش�.
	//m_moveRect�̰� �޾Ƽ� �ű� ��ġ�� �˷��ش�.

	int m_iX, m_iY; //map���� �� ��ġ ã�� �ε��� �뵵
	RECT m_moveRect; //�̵� ��ų rect �ӽ� �����
};

//������ �Ϲ� �̵� . �̰� �����ϴ� �⹰ �̵�(��� ������ �Ѿ�� �ʰ�)
struct MOVEPROMOTIONOBJECTPACKET : BASEPACKET
{
	int m_iX, m_iY; //map���� �� ��ġ ã�� �ε��� �뵵
	RECT m_moveRect; //�̵� ��ų rect �ӽ� �����
};

struct PROMOTIONPACKET : SETTURNPACKET
{
	PROMOTION_RECT promotion; //�ٲ� ���� ����
};

struct WINCHECKPACKET : MOVEOBJECTPACKET
{
	CAMP winTeam;
};

#pragma pack()