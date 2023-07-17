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
		RECT rect; //���� üũ ���� �߰� pos���ٰ� �̹��� ũ�� ��� �ϴ� �ͺ��� ���� ������ �Ǵ�

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
		RECT GetRect() { return rect; } //���� üũ ���� �߰�
		//Vector2 GetPos() { return pos; } //���� üũ ���� �߰�
		//SIZE GetSize() { return size; } //���� üũ ���� �߰�
		//Vector2 GetPos() { return pos; }

		// GrahpicComponent��(��) ���� ��ӵ�
		virtual VOID Operate(GameObject* Owner) override;
		virtual VOID Reset() override;
		virtual VOID SetScale(UINT cx, UINT cy) override;
		virtual VOID Draw() override;

		//�߰� �ڵ�
		//VOID ChangeSpritese(ENGINE::TotalResource vResource);
	};
}

#endif // !SPRITE_RENDERER_H
