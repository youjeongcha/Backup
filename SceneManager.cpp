#include "SceneManager.h"
#include "TimeManager.h"

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
		TimeMgr->Initialize(FPS); //FPS : EngineMecro::ENGINE::enum::FPS
	}

	void SceneManager::Release()
	{
		currScene = NULL;
		TimeMgr->Destroy;
		
		for (std::pair<std::string, Scene*> scene : scenes)
			REL_DEL(scene.second);

	}
	void SceneManager::Render()
	{
	}
	bool SceneManager::RegisterScene(LPCSTR sceneName, Scene* scene)
	{
		return false;
	}
	bool SceneManager::LoadScene(LPCSTR scenenName)
	{
		return false;
	}
	void SceneManager::SetScene()
	{
	}
	void SceneManager::Update()
	{
	}
	void SceneManager::Draw()
	{
	}
	HBITMAP SceneManager::CreateDIBSectionRe()
	{
		return HBITMAP();
	}
}