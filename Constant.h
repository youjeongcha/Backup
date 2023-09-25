//상수 버퍼와 상수 구조체
//정점 셰이더에 값을 입력하기 위한 구조체와 이를 정점 셰이더에 알려줄 상수 버퍼
//셰이더는 상수 구조체의 메모리를 16바이트 단위로 사용한다.
//셰이더의 bool 메모리 크기는 4바이트

#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct Matrices
{
	XMMATRIX world;
	XMMATRIX viewProjection;
};