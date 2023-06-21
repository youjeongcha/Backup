#include "SpriteAnimation.h"
#include "SpriteRenderer.h"
#include "../TimeManager.h"

namespace ENGINE
{
	//TODO::SpriteAnimation���� �����ϰ� Animation ����
	//�ִϸ��̼� ����� ������ ó��
	SpriteAnimation::SpriteAnimation(UINT divX, UINT divY, BOOL autoPlay) :
		AnimationComponent(divY, divX, autoPlay),
		frame(0), animTimer(frameRate), renderer(nullptr) {}

	/*SpriteAnimation::SpriteAnimation(ENGINE::TotalResource resource, BOOL autoPlay) : AnimationComponent(resource, autoPlay)
	//SpriteAnimation::SpriteAnimation(UINT divX, UINT divY, BOOL autoPlay)
	{ 
		frame = 0;
		animTimer = frameRate;
		renderer = nullptr;
	}*/

	VOID SpriteAnimation::Operate(GameObject* Owner)
	{
		renderer = Owner->GetComponent(ComponentType::Graphic);
		if (!renderer) return;

		static_cast<SpriteRenderer*>(renderer)->SetSrc(frame, index);

		if (!isPlaying)
		{//TODO::count�� length�� renderer �ʿ��� �޾ƿͼ� �ڵ������� ���õǰ�
			frame = 0;
			animTimer = frameRate;
			return;
		}

		animTimer += TimeMgr->DeltaTime() * speed;
		if (frameRate <= animTimer)
		{
			animTimer -= frameRate;
			frame += (isReverse ? -1 : 1);
			frame = Repeat(frame, (int)(length - 1));
			OutputDebugStringA((std::to_string(frame) + "\n").c_str());
		}
	}
	VOID SpriteAnimation::Reset()
	{
		index = 0U;
		speed = 1U;
		frame = 0;
		animTimer = frameRate;
	}
	/*VOID SpriteAnimation::ChangeAnim(ENGINE::TotalResource resource, BOOL autoPlay)
	{
		AnimationComponent::ChangeAnimComp(resource, autoPlay);

		frame = 0;
		animTimer = frameRate;
		renderer = nullptr;
	}*/
}