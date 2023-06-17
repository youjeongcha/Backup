#include "UIImage.h"
#include "ResourceManager.h"

namespace ENGINE
{
	VOID UIImage::SetRect(BOOL pivotCenter)
	{
		POINT pos = position;
		size = image->GetBitmapSize();

		if (pivotCenter)
		{
			pos.x -= size.cx * 0.5f;
			pos.y -= size.cy * 0.5f;
		}

		rect = { pos.x, pos.y, pos.x + size.cx, pos.y + size.cy };
	}

	VOID UIImage::Initialize(const std::string& ImageName, DrawType type)
	{
		image = ResourceMgr->GetBitmap(ImageName);
		this->type = type;
		SetRect(pivotCenter);
	}

	VOID UIImage::Draw()
	{
		if (!isEnable)
			return;

		if (image)
		{
			switch (type)
			{
			case ENGINE::DrawType::Transparent:
				image->TransparentBlt(rect.left, rect.top);
				break;
			default:
				image->BitBlt(rect.left, rect.top);
				break;
			}
		}

		UIPanel::Draw();
	}

} //namespace ENGINE