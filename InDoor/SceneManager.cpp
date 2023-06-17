#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "UIManager.h"

namespace ENGINE
{
	/*�̸����� ���ǵǾ� ������, ���� ��ȯ�� �������� �����մϴ�. ���� ��ȯ�� LoadScene �Լ��� ����Ͽ� ������ ǥ���� ���� �����մϴ�. ����, Update �Լ��� Draw �Լ��� ȣ���Ͽ� ���� ���� ������Ʈ�� �������� ó��
	scenes��� ��(Map)�� �����ϸ�, �� ���� �� �̸��� �� ��ü(Scene)�� �����Ͽ� �����մϴ�. RegisterScene �Լ��� ����Ͽ� ���� ����ϰ�, SetScene �Լ��� ȣ���Ͽ� ������ ǥ���� ���� ����

	���� DemoScene�� SceneMgr�� ���� �����Ǹ�, ���� ȭ���� �̹����� �����ϰ� �÷��̾� ��ü�� ������Ʈ�ϰ� �׸��� ������ ����*/
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
		
		//TimeMgr�� �ʱ�ȭ�� Scene Mgr���� ���ְ� �ִ�.
		TimeMgr->Initialize(FPS); //FPS : EngineMecro::ENGINE::enum::FPS
		InputMgr->Initialize();
		ResourceMgr->Initialize();
		UIMgr->Initialize();
	}

	void SceneManager::Release()
	{
		currScene = NULL;

		InputMgr->Destroy();
		TimeMgr->Destroy();
		ResourceMgr->Destroy();
		UIMgr->Destroy();
		
		//for each �ݺ��������� �ݺ� ������ �ڷ����� �ڵ����� �߷��ϸ�, map�� ��� �� ���Ұ� pair<const Key, T> ���·� ����Ǿ� �ֱ� ����
		for (std::pair<std::string, Scene*> scene : scenes) //map�� key�� ������ ���� >  pair�� ������ �ؾ��Ѵ�.
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

			InputMgr->Update(); //�ش� �κп��� down > pressed ���� �ٲ�� �ִ�.
		}
		SetScene();
	}

	void SceneManager::SetScene()
	{ //���� ������ ���� ���翡 �����Ų��.
		if (nextScene.empty())
			return;

		if (currScene)
		{
			currScene->Release();
			UIMgr->Clear();
			ResourceMgr->Clear();
		}

		currScene = scenes[nextScene];
		currScene->Initialize();
		nextScene = "";
	}
	void SceneManager::Update()
	{
		UIMgr->Update();
		currScene->Update(TimeMgr->DeltaTime());
	}
	void SceneManager::Draw()
	{
		HBITMAP backBitmap = CreateDIBSectionRe();
		SelectObject(hBackDC, backBitmap);

		currScene->Draw();
		UIMgr->Draw();

		BitBlt(hDC, 0, 0, width, height, hBackDC, 0, 0, SRCCOPY); //�׸�-����
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
	{ //���� scene���� �� scene�� key��(String)�� �޾ƿ´�.
		if ("" == sceneName || scenes.find(sceneName) == scenes.end())
			return false;

		nextScene = sceneName;

		return true;
	}
	HBITMAP SceneManager::CreateDIBSectionRe()
	{
		BITMAPINFO bmpInfo; ///?
		ZeroMemory(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
		bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //BITMAPINFOHEADER ����ü�� ũ�⸦ ��Ÿ���� ��
		bmpInfo.bmiHeader.biBitCount = 32; //�ȼ� �ϳ��� ��Ÿ���� ��Ʈ ���� ��Ÿ���� ���̴�. ��κ��� ��Ʈ�� �̹��������� 24��Ʈ�� ����Ѵ�.
		bmpInfo.bmiHeader.biWidth = width; //��Ʈ�� �̹����� ���� ũ�⸦ ��Ÿ���� �ȼ� ������ ���̴�.
		bmpInfo.bmiHeader.biHeight = height; //��Ʈ�� �̹����� ���� ũ�⸦ ��Ÿ���� �ȼ� ������ ���̴�.
		bmpInfo.bmiHeader.biPlanes = 1; //��Ʈ�� �̹����� �÷��� ���� ��Ÿ���� ������, �׻� 1�̴�.

		LPVOID pBits; //�� �����͸� ����Ͽ� ������ ��Ʈ�� �̹����� �ȼ� �����Ϳ� ������ �� �ִ�.
		return CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		//CreateDIBSection �Լ��� ��Ʈ�� �̹����� �����ϰ�, �� �̹����� ���� ������ BITMAPINFO ����ü�� �Բ� ��ȯ�ϴ� �Լ�,
		//���� ��Ʈ�� �̹����� �ȼ� �����͸� ������ �޸� ������ �Ҵ��Ѵ�.
	}
} //namespace ENGINE