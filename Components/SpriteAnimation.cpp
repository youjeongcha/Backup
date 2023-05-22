#include "SpriteAnimation.h"
#include "SpriteRenderer.h"
#include "../TimeManager.h"

namespace ENGINE
{
	SpriteAnimation::SpriteAnimation(UINT divX, UINT divY, BOOL autoPlay) : 
		AnimationComponent(divY, divX, autoPlay),
		frame(0), animTimer(frameRate), renderer(nullptr)
	{ }

	VOID SpriteAnimation::Operate(GameObject* Owner)
	{
		renderer = Owner->GetComponent(ComponentType::Graphic);
		if (!renderer) return;

		static_cast<SpriteRenderer*>(renderer)->SetSrc(frame, index);

		if (!isPlaying)
		{
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
		}
	}
	VOID SpriteAnimation::Reset()
	{
		index = 0U;
		speed = 1U;
		frame = 0;
		animTimer = frameRate;
	}
}