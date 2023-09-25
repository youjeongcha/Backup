//main.cpp
#include "System.h"
#include "DirectX11Graphics.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR IpCmdLine, _In_ int nCmdShow)
{
	std::unique_ptr<System> main = std::make_unique<System>();

	if (main->Intialize<DirectX11Graphics>(hInstance, L"DirectX11", 800, 600))
	{
		main->Processing();
	}

	return 0;
}