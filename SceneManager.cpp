#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

namespace ENGINE
{
	SceneManager::~SceneManager() { Release(); }

	void SceneManager::Initialize(HWND hWnd, UINT32 width, UINT32 height)
	{
		if (!hWnd)
			return;

		this->hWnd = hWnd;
		this->width = width;
		this->height = height;

		hDC = GetDC(hWnd);
		hBackDC = CreateCompatibleDC(hDC);
		
		//TimeMgr의 초기화를 Scene Mgr에서 해주고 있다.
		TimeMgr->Initialize(FPS); //FPS : EngineMecro::ENGINE::enum::FPS
		InputMgr->Initialize();
		ResourceMgr->Initialize();
	}

	void SceneManager::Release()
	{
		currScene = NULL;

		InputMgr->Destroy();
		TimeMgr->Destroy();
		ResourceMgr->Destroy();
		
		//for each 반복문에서는 반복 변수의 자료형을 자동으로 추론하며, map의 경우 각 원소가 pair<const Key, T> 형태로 저장되어 있기 때문
		for (std::pair<std::string, Scene*> scene : scenes) //map은 key와 값으로 구성 >  pair로 접근을 해야한다.
			REL_DEL(scene.second);

		
		scenes.clear();
		DeleteObject(hBackDC);
		ReleaseDC(hWnd, hDC);
	}
	void SceneManager::Render()
	{
		if (!TimeMgr->Update())
			return;

		if (currScene)
		{
			Update();
			Draw();

			InputMgr->Update();
		}
		SetScene();
	}

	void SceneManager::SetScene()
	{ //다음 순서의 씬을 현재에 적용시킨다.
		if (nextScene.empty())
			return;

		if (currScene)
		{
			currScene->Release();
			ResourceMgr->Clear();
		}

		currScene = scenes[nextScene];
		currScene->Initialize();
		nextScene = "";
	}
	void SceneManager::Update()
	{
		currScene->Update(TimeMgr->DeltaTime());
	}
	void SceneManager::Draw()
	{
		HBITMAP backBitmap = CreateDIBSectionRe();
		SelectObject(hBackDC, backBitmap);

		currScene->Daw();

		BitBlt(hDC, 0, 0, width, height, hBackDC, 0, 0, SRCCOPY); //그림-사진
		DeleteObject(backBitmap);
	}

	bool SceneManager::RegisterScene(LPCSTR sceneName, Scene* scene)
	{
		if ("" == sceneName || !scene || scenes.find(sceneName) != scenes.end())
			return false;

		scenes.insert(std::make_pair(sceneName, scene));

		return true;
	}
	bool SceneManager::LoadScene(LPCSTR sceneName)
	{ //다음 scene으로 올 scene의 key값(String)을 받아온다.
		if ("" == sceneName || scenes.find(sceneName) == scenes.end())
			return false;

		nextScene = sceneName;

		return true;
	}
	HBITMAP SceneManager::CreateDIBSectionRe()
	{
		BITMAPINFO bmpInfo; ///?
		ZeroMemory(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //BITMAPINFOHEADER 구조체의 크기를 나타내는 값
		bmpInfo.bmiHeader.biBitCount = 32; //픽셀 하나를 나타내는 비트 수를 나타내는 값이다. 대부분의 비트맵 이미지에서는 24비트를 사용한다.
		bmpInfo.bmiHeader.biWidth = width; //비트맵 이미지의 가로 크기를 나타내는 픽셀 단위읭 값이다.
		bmpInfo.bmiHeader.biHeight = height; //비트맵 이미지의 세로 크기를 나타내는 픽셀 단위읭 값이다.
		bmpInfo.bmiHeader.biPlanes = 1; //비트맵 이미지의 플레인 수를 나타내는 값으로, 항상 1이다.

		LPVOID pBits; //이 포인터를 사용하여 생성된 비트맵 이미지의 픽셀 데이터에 접근할 수 있다.
		return CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		//CreateDIBSection 함수는 비트맵 이미지를 생성하고, 이 이미지에 대한 정보를 BITMAPINFO 구조체와 함께 반환하는 함수,
		//또한 비트맵 이미지의 픽셀 데이터를 저장할 메모리 공간을 할당한다.
	}
} //namespace ENGINE