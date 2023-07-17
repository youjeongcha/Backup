#include "../Component.h"
#include "../Bitmap.h"

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

namespace ENGINE
{
	//struct Location
	//{
	//	Vector2 pos;
	//	SIZE size;
	//};

	class SpriteRenderer : public GrahpicComponent
	{
	private:
		Bitmap* sprites;
		SIZE localSize, size;
		Vector2 pos, divide;
		//Location location; //
		RECT rect; //범위 체크 위해 추가 pos에다가 이미지 크기 계속 하는 것보다 나을 것으로 판단

	private:
		SpriteRenderer();
	public:
		SpriteRenderer(LPCSTR name, UINT divX = 1, UINT divY = 1);
		//SpriteRenderer(std::vector<ENGINE::TotalResource> vResources);

		VOID SetPivot(INT pivot) { if (sprites) sprites->SetPivot(pivot); }
		VOID SetSrc(UINT cx, UINT cy);
		void SetPos(float x, float y)
		{ 
			pos.x = x; pos.y = y; 
			SetRect();
		}
		//void SetLocation() { location.pos = pos; location.size = size; }
		void SetRect() 
		{
			rect.left = pos.x;
			rect.top = pos.y;
			rect.right = rect.left + size.cx;
			rect.bottom = rect.top + size.cy;
		}
		SIZE GetDrawSize() { return size; }
		//Location GetLocation() { return location; }
		RECT GetRect() { return rect; } //범위 체크 위해 추가
		//Vector2 GetPos() { return pos; } //범위 체크 위해 추가
		//SIZE GetSize() { return size; } //범위 체크 위해 추가
		//Vector2 GetPos() { return pos; }

		// GrahpicComponent을(를) 통해 상속됨
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;
		virtual VOID SetScale(UINT cx, UINT cy) override;
		virtual VOID Draw() override;

		//추가 코드
		//VOID ChangeSpritese(ENGINE::TotalResource vResource);
	};
}

#endif // !SPRITE_RENDERER_H
