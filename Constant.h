//��� ���ۿ� ��� ����ü
//���� ���̴��� ���� �Է��ϱ� ���� ����ü�� �̸� ���� ���̴��� �˷��� ��� ����
//���̴��� ��� ����ü�� �޸𸮸� 16����Ʈ ������ ����Ѵ�.
//���̴��� bool �޸� ũ��� 4����Ʈ

#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct Matrices
{
	XMMATRIX world;
	XMMATRIX viewProjection;
};

//���� ����
struct Material
{
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
	float specularPower;
};

struct Light
{
	XMFLOAT4 comPosition;
	XMFLOAT4 light_color;
	XMFLOAT4 light_direction;
	XMFLOAT4 globalAmbient;
	Material material;
};