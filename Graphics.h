#pragma once
#include <Windows.h>
#include <assert.h> //º¸Çè

class WindowContainer;
class Graphics abstract
{
protected:
	int screenWidth, screenHeight;
public:
	virtual ~Graphics() {}

	virtual bool Initialize(WindowContainer* pWindowContainer)
	{
		assert("Graphics::Initialize must be overridden." && 0); 
		return false;
	}

	virtual void Update()

	{
		assert("Graphics::Update must be overridden." && 0);
	}

	virtual void RenderFrame()
	{
		assert("Graphics::RenderFrame must be overridden." && 0);
	}
};