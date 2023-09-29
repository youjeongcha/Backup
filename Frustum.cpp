#include "Frustum.h"

bool Frustum::Initialize(DXCamera* camera, float planeEpsilon)
{
	if (!camera)
		return false;

	this->camera = camera;
	this->planeEpsilon = planeEpsilon;
	for (int i = 0; 6 > i; i++)
		frustumPlane[i] = XMVectorSet(0, 0, 0, 0);

	return true;
}

void Frustum::ConstructFrustum()
{
	// 최종 정점은 (-1, -1, 0) ~ (1, 1, 1) 사이의 값으로 바뀐다.
	XMFLOAT3 frustumVertices[8] =
	{
		{-1.0f, -1.0f, 0.0f},	// near left bootomv()
		{1.0f, -1.0f, 0.0f},	// near right bootomv1
		{1.0f, -1.0f, 1.0f},	// far right bootomv2
		{-1.0f, -1.0f, 1.0f},	// far left bootomv3

		{-1.0f, 1.0f, 0.0f},	// near left topv4
		{1.0f, 1.0f, 0.0f},		// near right topv5
		{1.0f, 1.0f, 1.0f},		// far right topv6
		{-1.0f, 1.0f, 1.0f},	// far left topv7
	};

	// view * Proj의 역행렬 계산.
	XMMATRIX invViewProjectionMatrix = XMMatrixInverse(NULL, camera->GetViewMatrix() * camera->GetProjectionMatrix());
	XMVECTOR frustumVectors[8];
	for (int i = 0; 8 > i; i++)
	{
		frustumVectors[i] = XMVector3TransformCoord(XMVectorSet(frustumVertices[i].x, frustumVertices[i].y, frustumVertices[i].z, 1.0f),
			invViewProjectionMatrix);
	}
	frustumPlane[0] = XMPlaneFromPoints(frustumVectors[4], frustumVectors[7], frustumVectors[6]); // 상 평면(top)
	frustumPlane[1] = XMPlaneFromPoints(frustumVectors[0], frustumVectors[1], frustumVectors[2]); // 하 평면(bottom)
	frustumPlane[2] = XMPlaneFromPoints(frustumVectors[0], frustumVectors[4], frustumVectors[5]); // 근 평면(near)
	frustumPlane[3] = XMPlaneFromPoints(frustumVectors[2], frustumVectors[6], frustumVectors[7]); // 원 평면(far)
	frustumPlane[4] = XMPlaneFromPoints(frustumVectors[0], frustumVectors[3], frustumVectors[7]); // 좌 평면(left)
	frustumPlane[5] = XMPlaneFromPoints(frustumVectors[1], frustumVectors[5], frustumVectors[6]); // 우 평면(right)

}

bool Frustum::IsInFrustum(XMFLOAT3 v)
{
	return IsInFrustum(XMVectorSet(v.x, v.y, v.z, 1.0f));
}

bool Frustum::IsInFrustum(XMVECTOR v)
{
	return IsInFrustumBoundsSphere(v, 0.0f);
}

bool Frustum::IsInFrustumExceptUpDown(XMFLOAT3 v)
{
	return IsInFrustumBoundsSphereExceptUpDwon(v, 0.0f);
}



bool Frustum::IsInFrustumBoundsSphere(XMFLOAT3 v, float radius)
{
	return IsInFrustumBoundsSphere(XMVectorSet(v.x, v.y, v.z, 1.0f), radius);
}

bool Frustum::IsInFrustumBoundsSphere(XMVECTOR v, float radius)
{
	for (int i = 0; 6 > i; i++)
	{
		// 내적은 frustumPlane에서 v까지의 수직상 거리와 같다.
		if (XMVectorGetX(XMPlaneDotCoord(frustumPlane[i], v)) > (radius + planeEpsilon))
			return false;
	}

	return true;
}

bool Frustum::IsInFrustumBoundsSphereExceptUpDwon(XMFLOAT3 v, float radius)
{
	XMVECTOR vector = XMVectorSet(v.x, v.y, v.z, 1.0f);

	for (int i = 2; 6 > i; i++)
	{
		// 내적은 frustumPlane에서 v까지의 수직상 거리와 같다.
		if (XMVectorGetX(XMPlaneDotCoord(frustumPlane[i], vector)) > (radius + planeEpsilon))
			return false;
	}

	return true;
}

bool Frustum::IsInFrustumBoundsCube(XMFLOAT3 v, float radius)
{
	for (int i = 0; 6 > i; i++)
	{
		if (IsInBoundsCube(frustumPlane[i], v, XMFLOAT3(radius, radius, radius))) continue;
		return false;
	}
	return true;
}

bool Frustum::IsInFrustumBoundsCube(XMVECTOR v, float radius)
{
	XMFLOAT3 dest;
	XMStoreFloat3(&dest, v);
	return IsInFrustumBoundsCube(dest, radius);
}




bool Frustum::IsInFrustumBoundsRectangle(XMFLOAT3 v, XMFLOAT3 r)
{
	for (int i = 0; 6 > i; i++)
	{
		if (IsInBoundsCube(frustumPlane[i], v, r)) continue;
		return false;
	}
	return true;
}

bool Frustum::IsInFrustumBoundsRectangle(XMVECTOR v, XMFLOAT3 r)
{
	XMFLOAT3 destV;
	XMStoreFloat3(&destV, v);
	return IsInFrustumBoundsRectangle(destV, r);
}

bool Frustum::IsInFrustumBoundsRectangle(XMVECTOR v, XMVECTOR r)
{
	XMFLOAT3 destV, destR;
	XMStoreFloat3(&destV, v);
	XMStoreFloat3(&destR, r);
	return IsInFrustumBoundsRectangle(destV, destR);
}

bool Frustum::IsInBoundsCube(XMVECTOR p, XMFLOAT3 v, XMFLOAT3 r)
{
	return
	(
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x - r.x, v.y - r.y, v.z - r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x - r.x, v.y - r.y, v.z + r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x - r.x, v.y + r.y, v.z - r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x - r.x, v.y + r.y, v.z + r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x + r.x, v.y - r.y, v.z - r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x + r.x, v.y - r.y, v.z + r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x + r.x, v.y + r.y, v.z - r.z, 1.0f))) <= planeEpsilon) ||
		(XMVectorGetX(XMPlaneDotCoord(p, XMVectorSet(v.x + r.x, v.y + r.y, v.z + r.z, 1.0f))) <= planeEpsilon)
	);
}
