#include<windows.h>
#include<string>
#include<vector>
#include<map>
#include<functional>
#include "Math.h"

#ifndef COMPONENT_H
#define COMPONENT_H

typedef std::function<VOID()> EventListener;

namespace ENGINE
{


	//struct TotalResource
	//{
	//	LPCSTR name;
	//	UINT divX;
	//	UINT divY;
	//	Vector2 divide;
	//};
	enum class ComponentType { GameObject, Transform, Graphic, Input, Animation, };

	class GameObject;
	__interface Component
	{
		VOID Operate(GameObject* Owner);
		VOID Reset();
		ComponentType GetType() CONST;
	};

	//게임 오브젝트의 위치와 크기를 관리
	struct Transform : public Component
	{
		Vector2 position; //좌표
		Vector2 scale; //무게

		Transform() : position(0.0f, 0.0f), scale(1.0f, 1.0f) {}

		// Component을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override { }
		virtual VOID Reset() override;
		virtual ComponentType GetType() const override { return ComponentType::Transform; }
	};

	class GameObject : public Component
	{
	private:
		std::map<ComponentType, Component*> components;
	protected:
		Transform* transform;

	public:
		GameObject();
		virtual ~GameObject();

	public:
		Component* GetComponent(CONST ComponentType& type);
		BOOL AddComponent(Component* component);
		Transform* GetTransform() CONST { return transform; }

		virtual VOID SetPosition(CONST Vector2& pos) { transform->position = pos; }
		virtual VOID SetScale(CONST Vector2& scale) { transform->scale = scale; }

		// Component을(를) 통해 상속됨
		virtual VOID Operate(GameObject*) override;
		virtual VOID Reset() override;
		virtual ComponentType GetType() const override { return ComponentType::GameObject; }
	};

	class GrahpicComponent : public Component
	{
	public:
		virtual ~GrahpicComponent() { }

		virtual VOID SetScale(UINT cx, UINT cy) abstract;
		virtual VOID Draw() abstract;
		// Component을(를) 통해 상속됨
		virtual ComponentType GetType() const override { return ComponentType::Graphic; }
	};

	class AnimationComponent : public Component
	{
	protected:
		BOOL isPlaying, isReverse;
		UINT index;
		FLOAT speed;
		UINT length;
		UINT maxSize;
		FLOAT frameRate;
		//CONST UINT length;
		//CONST UINT maxSize;
		//CONST FLOAT frameRate;

	private:
		AnimationComponent();
	public:
		AnimationComponent(UINT count, UINT length, BOOL autoPlay) : isPlaying(autoPlay), isReverse(FALSE), index(0U), speed(1.0f), length(length), maxSize(count), frameRate(1.0f / length) { }
		//AnimationComponent(ENGINE::TotalResource resource, BOOL autoPlay)
		//{
		//	isPlaying = autoPlay;
		//	isReverse = FALSE;
		//	index = 0U;
		//	speed = 1.0f;
		//	length = resource.divY;
		//	maxSize = resource.divX;
		//	frameRate = 1.0f / maxSize;
		//	//SetChangeResouce(resource);
		//}

		virtual ~AnimationComponent() { }

		VOID SetSpeed(FLOAT speed);
		VOID Play(UINT index) { this->index = clamp(index, 0, maxSize - 1); isPlaying = TRUE; }
		//VOID Idle(UINT index) { this->index = clamp(index, 0, maxSize - 1); isPlaying = TRUE; }
		VOID Stop() { isPlaying = FALSE; }
		// Component을(를) 통해 상속됨
		virtual ComponentType GetType() const override { return ComponentType::Animation; }

		//추가 코드
		/*VOID ChangeAnimComp(ENGINE::TotalResource resource, BOOL autoPlay) { SetChangeResouce(resource); };*/

		//VOID SetChangeResouce(ENGINE::TotalResource resource, BOOL autoPlay = FALSE) 
		//{ 
		//	isPlaying = autoPlay; 
		//	isReverse = FALSE; 
		//	index = 0U;
		//	speed = 1.0f; 
		//	length = resource.divY;
		//	maxSize = resource.divX; 
		//	frameRate = 1.0f / maxSize; 
		//}
	};
}

#endif // !COMPONENT_H