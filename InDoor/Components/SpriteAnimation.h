#include "../Component.h"

#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

namespace ENGINE
{
	//�ִϸ��̼� ����� ������ ó��
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

		// AnimationComponent��(��) ���� ��ӵ�
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;

		//�߰� �ڵ�
		//VOID ChangeAnim(ENGINE::TotalResource resource, BOOL autoPlay = FALSE);
	};
}

#endif // !SPRITE_ANIMATION_H