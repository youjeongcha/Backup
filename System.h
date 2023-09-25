#pragma once
#include "WindowContainer.h"
#include "Graphics.h"

class System final : public WindowContainer
{
public:
	//TODO::템플릿 어떻게 쓰는건지도 알아보기
	template<typename T, typename = std::enable_if<std::is_base_of<Graphics, T>::value>>
	
	bool Intialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height, bool fullScreen = false)
	{
		window = std::make_unique<Window>();

		if (!window->Intialize(this, hInstance, title, width, height, fullScreen)) 
			return false;

		Input::Initialize(window->GetScreenWidth(), window->GetScreenHeight());
		timer = std::make_unique<Timer>();
		timer->Start();

		//Graphics
		gfx = std::make_unique<T>();

		if (!gfx->Initialize(this))
			return false;

		return true;
	}

	void Processing();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM, LPARAM lParam) override;

	virtual bool Update() override;
	virtual void RenderFrame() override;
};
