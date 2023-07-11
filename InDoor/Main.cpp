#include "WinApiEngine.h"
#include "SceneManager.h"
#include "DemoScene.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevINstance, _In_ LPWSTR IpCmdLine, _In_ int nCmdShow)
{
	srand(time(NULL));

	//ENGINE::WinApiEngine engine(hInstance, TEXT("WindAPI 2D Engine"),
	ENGINE::WinApiEngine engine(hInstance, TEXT("INROOM"),
		ENGINE::Client_Per_X, ENGINE::Client_Per_Y,
		ENGINE::ClientSize_Width, ENGINE::ClientSize_Height);

	//TODO:: 여기에 새로운 씬 등록 및 코드
	SceneMgr->RegisterScene("test", new DemoScene);
	SceneMgr->LoadScene("test");
	
	return engine.Run(); //Run()에서 해당 루프를 돌고. WM_DESTROY가 되면 return이 되어 나온다.
}