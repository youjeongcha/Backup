#include "WinApiEngine.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevINstance, _In_ LPWSTR IpCmdLine, _In_ int nCmdShow)
{
	ENGINE::WinApiEngine engine(hInstance, TEXT("WindAPI 2D Engine"),
		ENGINE::Client_Per_X, ENGINE::Client_Per_Y,
		ENGINE::ClientSize_Width, ENGINE::ClientSize_Height);

	//TODO:: ���⿡ ���ο� �� ��� �� �ڵ�
	
	return engine.Run(); //Run()���� �ش� ������ ����. WM_DESTROY�� �Ǹ� return�� �Ǿ� ���´�.
}