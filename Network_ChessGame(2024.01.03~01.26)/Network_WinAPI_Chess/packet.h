#pragma once

#include <Windows.h>

#pragma pack(1)

enum PacketType
{
	PacketType_BasePacket, //기본
	PacketType_SetTeam, //팀 세팅
	PacketType_SetTurn, //턴 전환
	PacketType_MoveObject,//기본 이동
	PacketType_MovePromotionObject,//폰 - 승진 전 이동
	PacketType_Promotion, //승진
	PacketType_WinCheck, //승리 체크
	
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


	//이렇게 쓸 수도 있는데 추천하지 않음
	// 패킷 생성할때마다 새로 초기화해주는 쪽이 명시적이고 좋음
	//BASEPACKET의 생성자에서 인자로 전달받은 값을 사용하여 packetType을 설정
	//SETTEAM() : BASEPACKET(PacketType_SetTeam) {}
};

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

//위에는 일반 이동 . 이건 승진하는 기물 이동(상대 턴으로 넘어가지 않게)
struct MOVEPROMOTIONOBJECTPACKET : BASEPACKET
{
	int m_iX, m_iY; //map에서 말 위치 찾을 인덱스 용도
	RECT m_moveRect; //이동 시킬 rect 임시 저장용
};

struct PROMOTIONPACKET : SETTURNPACKET
{
	PROMOTION_RECT promotion; //바뀔 말의 종류
};

struct WINCHECKPACKET : MOVEOBJECTPACKET
{
	CAMP winTeam;
};

#pragma pack()