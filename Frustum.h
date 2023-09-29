#pragma once
#include "Components/DXCamera.h"

class Frustum
{
private:
	DXCamera* camera;

	float planeEpsilon;
	XMVECTOR frustumPlane[6];

public:
	bool Initialize(DXCamera* camera, float planeEpsilon = FLT_EPSILON);
	void ConstructFrustum();

	bool IsInFrustum(XMFLOAT3 v);
	bool IsInFrustum(XMVECTOR v);
	bool IsInFrustumExceptUpDown(XMFLOAT3 v);

	bool IsInFrustumBoundsSphere(XMFLOAT3 v, float radius);
	bool IsInFrustumBoundsSphere(XMVECTOR v, float radius);
	bool IsInFrustumBoundsSphereExceptUpDwon(XMFLOAT3 v, float radius);


	bool IsInFrustumBoundsCube(XMFLOAT3 v, float radius);
	bool IsInFrustumBoundsCube(XMVECTOR v, float radius);


	bool IsInFrustumBoundsRectangle(XMFLOAT3 v, XMFLOAT3 r); // Rectangle : AABB /OBB
	bool IsInFrustumBoundsRectangle(XMVECTOR v, XMFLOAT3 r);
	bool IsInFrustumBoundsRectangle(XMVECTOR v, XMVECTOR r);

private:
	bool IsInBoundsCube(XMVECTOR p, XMFLOAT3 v, XMFLOAT3 r);
};

