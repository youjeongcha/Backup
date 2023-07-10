#include "UIButton.h"
#include "ResourceManager.h"
#include "InputManager.h"

namespace ENGINE
{
	UIButton::UIButton() : clickListener(nullptr), pressedListener(nullptr), state(ButtonState::NONE), isUp(FALSE), isInteractable(TRUE), normal(nullptr), pressed(nullptr), hover(nullptr), disable(nullptr)
	{
		uiType = UIType::BUTTON;
	}

	VOID UIButton::Initialize(const std::string& normal, const std::string& pressed, const std::string& hover, const std::string& disable, DrawType type)
	{
		UIImage::Initialize(normal, type);

		//일반 이미지로 먼저 초기화를 끝내고
		this->disable = this->hover = this->pressed = this->normal = image;

		//해당 이미지를 대입한다.
		if (!pressed.empty())
			this->pressed = ResourceMgr->GetBitmap(pressed);
		if (!hover.empty())
			this->hover = ResourceMgr->GetBitmap(hover);
		if (!disable.empty())
			this->disable = ResourceMgr->GetBitmap(disable);
	}

	VOID UIButton::SetListener(EventListener click, EventListener pressed)
	{
		clickListener = click;
		pressedListener = pressed;
	}

	VOID UIButton::Update()
	{
		if (!isEnable)
			return;

		UIImage::Update();

		if (!isInteractable)
		{
			state = ButtonState::NONE;
			if (disable)
				image = disable;
			return;
		}

		isUp = InputMgr->GetMouseButtonUp(VK_LBUTTON);

		if (PtInRect(&rect, InputMgr->GetMousePosition()))
		{
			switch (state)
			{
			case ButtonState::NONE:
				state = ButtonState::HOVER;
			case ButtonState::HOVER:
				if (InputMgr->GetMouseButtonDown(VK_LBUTTON))
					state = ButtonState::PRESSED;
				break;
			case ButtonState::PRESSED:
				if (isUp && clickListener)
					clickListener();
				break;
			}

		}
		else if (ButtonState::PRESSED != state)
			state = ButtonState::NONE;

		switch (state)
		{
		case ButtonState::NONE:
			image = normal;
			break;
		case ButtonState::HOVER:
			image = hover;
			break;
		case ButtonState::PRESSED:
			image = pressed;
			if (isUp) state = ButtonState::NONE;
			if (pressedListener)
				pressedListener();
			break;
		}
	}
}