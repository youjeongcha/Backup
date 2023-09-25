//ī�޶� ������Ʈ
/*
ī�޶� ���(View Matrix)�� ���� ���(Projection Matrix)�� �ʿ��ϱ� ������ ī�޶� ��ü�� �����.
DirectX �������� ����� ī�޶� ��ü�� DXGameObject/Components)
DXTransform�� �̿��Ͽ� ���� �������� ���� ������ ī�޶� ���� �� �ִ�.
DXtransform�� ���� �ڼ��� ������ ������������ ����
DXGameObject, ... : ���� ������ ���Ͽ� ������ ��ü
�ݵ�� Components ������ ���� ����
�߰��� �ڵ� Ȯ�� �ʼ�
*/

#pragma once
#include "../DXGameObject.h"
enum class ProjectionType { Perspective, Orthographic };

class DXCamera :public BaseComponent
{
private:
	ProjectionType type;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	float width, height;
	float nearZ, farZ;
	float fovDegrees;

public:
	DXCamera(DXGameObject* owner);

	void SetProjectionType(ProjectionType type);
	void SetProjection(float width, float height, float nearZ, float farZ, float fovDegrees = 60.0f);
	void ChangeProjectionType(const ProjectionType& type);
	const ProjectionType& GetProjectionType() const { return type; }
	const XMMATRIX& GetViewMatrix() const { return viewMatrix; }
	const XMMATRIX& GetProjectionMatrix() const { return projectionMatrix; }
	XMMATRIX GetViewProjectionMatrix() const { return viewMatrix * projectionMatrix; }
	float GetDepth() const { return farZ; }
private:
	void UpdateMatrix();
	friend DXTransform;
};