#pragma once
#include "Singleton.h"
#include "Bitmap.h"
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H


namespace ENGINE
{
	static const char* defaultPath = "Resources\\";

	class ResourceManager : public Singleton<ResourceManager>
	{
	private:
		std::map<std::string, Bitmap*> resources;
		ResourceManager() {}

	public:
		~ResourceManager();

		VOID Initialize();
		Bitmap* GetBitmap(const std::string& name);
		// 비트맵 이미지를 로드한다.
		BOOL Load(const std::string& fileName);
		// 폴더의 모든 비트맵 이미지를 로드.
		// 하위 폴더는 검색하지 않는다.
		VOID LoadAll(const std::string& directoryName = "");
		// 로드되어 있는 모든 리소스를 지운다.
		VOID Clear();
		friend Singleton;
	}; // class ResourceManager

#define ResourceMgr ResourceManager::GetInstance()
} // namespace ENGINE
#endif // !RESOURCE_MANAGER_