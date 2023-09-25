//카메라 컴포넌트
/*
카메라 행렬(View Matrix)과 투영 행렬(Projection Matrix)이 필요하기 때문에 카메라 객체를 만든다.
DirectX 렌더링에 사용할 카메라 객체를 DXGameObject/Components)
DXTransform을 이용하여 쉽게 움직임이 제어 가능한 카메라를 만들 수 있다.
DXtransform에 대한 자세한 내용은 계층구조에서 설명
DXGameObject, ... : 예제 진행을 위하여 만들어둔 객체
반드시 Components 폴더에 파일 생성
추가한 코드 확인 필수
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