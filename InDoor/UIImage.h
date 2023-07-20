#pragma once
#include "UIPanel.h"
#include "SceneManager.h"
#include "Bitmap.h"

//Image ������ UI�� ����� ���� UI Tool, DrawType�� �°� �������� �׸��ų� ����ȭ�Ͽ� �׸���
//������� ��ȫ�� (RGB(255, 0, 255))���� �����Ǿ� �ִ�.

#ifndef UI_IMAGE_H
#define UI_IMAGE_H

namespace ENGINE
{
	enum class DrawType 
	{
		Normal, 
		Transparent,
		AlphaBlend,
	};


	class UIImage : public UIPanel
	{
	protected:
		Bitmap* image;
		DrawType type;
		int transparency; //AlphaBlend�� ���
	//	std::string name; //�ǳ�2,3,4 �߰� ���� ���� �߰���

	public:
		UIImage() : image(nullptr), type(DrawType::Normal) { uiType = UIType::IMAGE; }
		VOID Initialize(CONST std::string& ImageName, DrawType type = DrawType::Normal);
		virtual VOID Draw() override;
		void Set_Transparency(int _transparency) { transparency = _transparency; }
		//void TransparentDraw(int transparent) { image->TransparentBlt(rect.left, rect.top, transparent); };
//		std::string GetName() { return name; };

	protected:
		virtual VOID SetRect(BOOL pivotCenter) override;
	};
}
#endif // !UI_IMAGE_H