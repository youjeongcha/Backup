#include "../Component.h"

#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

namespace ENGINE
{
	//애니메이션 제어와 프레임 처리
	class SpriteAnimation : public AnimationComponent
	{
	private:
		INT frame;
		FLOAT animTimer;
		Component* renderer;

	private:
		SpriteAnimation();
	public:
		//SpriteAnimation(ENGINE::TotalResource resource, BOOL autoPlay = FALSE);
		SpriteAnimation(UINT divX, UINT divY, BOOL autoPlay = FALSE);

		// AnimationComponent을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;

		//추가 코드
		//VOID ChangeAnim(ENGINE::TotalResource resource, BOOL autoPlay = FALSE);
	};
}

#endif // !SPRITE_ANIMATION_H