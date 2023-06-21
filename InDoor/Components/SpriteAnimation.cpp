#include "SpriteAnimation.h"
#include "SpriteRenderer.h"
#include "../TimeManager.h"

namespace ENGINE
{
	//TODO::SpriteAnimation먼저 수정하고 Animation 수정
	//애니메이션 제어와 프레임 처리
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
		{//TODO::count나 length를 renderer 쪽에서 받아와서 자동적으로 세팅되게
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