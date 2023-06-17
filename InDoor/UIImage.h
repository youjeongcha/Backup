#pragma once
#include "UIPanel.h"
#include "SceneManager.h"
#include "Bitmap.h"

//Image 형식의 UI를 만들기 위한 UI Tool, DrawType에 맞게 원본으로 그리거나 투명화하여 그린다
//투명색은 분홍색 (RGB(255, 0, 255))으로 고정되어 있다.

#ifndef UI_IMAGE_H
#define UI_IMAGE_H

namespace ENGINE
{
	enum class DrawType 
	{
		Normal, 
		Transparent 
	};


	class UIImage : public UIPanel
	{
	protected:
		Bitmap* image;
		DrawType type;

	public:
		UIImage() : image(nullptr), type(DrawType::Normal) { uiType = UIType::IMAGE; }
		VOID Initialize(CONST std::string& ImageName, DrawType type = DrawType::Normal);
		virtual VOID Draw() override;

	protected:
		virtual VOID SetRect(BOOL pivotCenter) override;
	};
}
#endif // !UI_IMAGE_H