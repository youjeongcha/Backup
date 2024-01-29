#pragma once
#pragma pack(1)

enum PacketType
{
	PacketType_BasePacket,
	PacketType_SetTeam,
//	PacketType_IsPlay,
//	PacketType_EndTurn,
	PacketType_SetTurn,
	PacketType_MoveObject,

};

enum CAMP
{
	CAMP_NONE = -1,
	CAMP_BLACK,
	CAMP_WHITE,
	CAMP_COUNT,
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


//struct ISPLAYPACKET : BASEPACKET
//{
//	bool isPlaying;
//};

//struct ENDTURNPACKET : BASEPACKET
//{
//	bool isEndTurn;
//};

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

#pragma pack()