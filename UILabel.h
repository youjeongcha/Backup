#pragma once
#include "UIPanel.h"

//Text 출력을 위한 UI Tool 폰트 및 색상 등의 변경이 가능

#ifndef UI_LABEL_H
#define UI_LABEL_H

namespace ENGINE
{
	class UILabel : public UIPanel
	{
	protected:
		std::string text;
		COLORREF color;
		HFONT font, oldFont;

	public:
		UILabel() : color(0), font(NULL), oldFont(NULL) { uiType = UIType::LABEL; }

		VOID Initialize(CONST std::string& text, COLORREF color = RGB(0, 0, 0), HFONT font = NULL);
		VOID SetColor(COLORREF color) { this->color = color; }
		VOID SetText(CONST std::string& text);
		VOID SetFont(HFONT font);

		LPCSTR GetText() { return text.c_str(); }
		virtual VOID Draw() override;

	protected:
		virtual VOID SetRect(BOOL pivotCenter) override;
	};
}
#endif // !UI_LABEL_H

