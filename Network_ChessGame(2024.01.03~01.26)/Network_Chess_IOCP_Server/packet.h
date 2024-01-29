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


	//이렇게 쓸 수도 있는데 추천하지 않음
	// 패킷 생성할때마다 새로 초기화해주는 쪽이 명시적이고 좋음
	//BASEPACKET의 생성자에서 인자로 전달받은 값을 사용하여 packetType을 설정
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


//이동전 좌표(m_iX인덱스) + 이동한 좌표(Rect)만 전송
struct MOVEOBJECTPACKET : SETTURNPACKET
{
	//m_iX와 m_iY를 전달해서 변경할 위치를 알려준다.
	//m_moveRect이걸 받아서 옮길 위치를 알려준다.

	int m_iX, m_iY; //map에서 말 위치 찾을 인덱스 용도
	RECT m_moveRect; //이동 시킬 rect 임시 저장용
};

#pragma pack()