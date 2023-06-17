#include "UILabel.h"
#include "SceneManager.h"

namespace ENGINE
{
	VOID UILabel::SetRect(BOOL pivotCenter)
	{
		if (font)
			oldFont = (HFONT)SelectObject(SceneMgr->GetBackDC(), font);

		GetTextExtentPoint32A(SceneMgr->GetBackDC(), text.c_str(), text.length(), &size);

		if (font)
			SelectObject(SceneMgr->GetBackDC(), oldFont);

		POINT pos = position;

		if (pivotCenter)
		{
			pos.x -= size.cx * 0.5f;
			pos.y -= size.cy * 0.5f;
		}

		rect = { pos.x, pos.y, pos.x + size.cx, pos.y + size.cy };
	}

	VOID UILabel::Initialize(const std::string& text, COLORREF color, HFONT font)
	{
		SetBkMode(SceneMgr->GetBackDC(), TRANSPARENT);
		SetColor(color);
		SetFont(font);
		SetText(text);
	}

	VOID UILabel::SetText(const std::string& text)
	{
		this->text = text;
		SetRect(pivotCenter);
	}

	VOID UILabel::SetFont(HFONT font)
	{
		if (font)
		{
			this->font = font;

			if (!text.empty())
				SetRect(pivotCenter);
		}
	}

	VOID UILabel::Draw()
	{
		if (!isEnable)
			return;

		if (font)
			oldFont = (HFONT)SelectObject(SceneMgr->GetBackDC(), font);

		SetTextColor(SceneMgr->GetBackDC(), color);
		DrawTextA(SceneMgr->GetBackDC(), text.c_str(), text.length(), &rect, NULL);

		if (font)
			SelectObject(SceneMgr->GetBackDC(), oldFont);

		UIPanel::Draw();
	}

}//namespace ENGINE