#include "WinApiEngine.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevINstance, _In_ LPWSTR IpCmdLine, _In_ int nCmdShow)
{
	ENGINE::WinApiEngine engine(hInstance, TEXT("WindAPI 2D Engine"),
		ENGINE::Client_Per_X, ENGINE::Client_Per_Y,
		ENGINE::ClientSize_Width, ENGINE::ClientSize_Height);

	//TODO:: 여기에 새로운 씬 등록 및 코드
	
	return engine.Run(); //?어떻게 돌아가는거지
}