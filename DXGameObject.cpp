#include "DXGameObject.h"

DXGameObject::DXGameObject()
{
	AddComponent<DXTransform>();
}

DXTransform* DXGameObject::GetTransform() const
{
	return transform.get();
}

void DXGameObject::Update()
{
	for (ActionComponent* actor : actionables) actor->Update();
}

void DXGameObject::Draw(const XMMATRIX& viewProjectionMatrix)
{
	for (RenderComponent* renderer : renderables) renderer->Draw(viewProjectionMatrix);
}
