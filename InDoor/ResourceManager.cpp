#include "ResourceManager.h"
#include <fstream>
#include <io.h> //access()

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //c++17 이상의 경우 #include<filesystem>을 사용.
#include <experimental/filesystem> //directory_iterator()
using namespace std::experimental::filesystem;


namespace ENGINE
{
	ResourceManager::~ResourceManager()
	{
		Clear();
	}

	VOID ResourceManager::Initialize()
	{
		Clear();
	}

	BOOL ResourceManager::Load(const std::string& fileName)
	{
		if (fileName.empty())
			return false;

		std::string path = defaultPath + fileName;
		// 0 : 파일 및 디렉토리의 존재 유무
		// 2 : 쓰기 접근 가능 여부
		// 4 : 읽기 접근 가능 여부
		// 6 : 읽기 쓰기 접근 가능 여부
		// return : 0(true), -1(false)

		if (0 != _access(path.c_str(), 0))
			return false;

		Bitmap* bitmap = new Bitmap;
		bitmap->Load(defaultPath + fileName);
		resources.insert(make_pair(fileName, bitmap));

		return true;
	}

	VOID ResourceManager::LoadAll(const std::string& directoryName)
	{
		v1::path path;
		std::string name;
		//directory_iterator : 디렉토리(폴더) 내의 파일 및 폴더를 찾는다. 하위 디렉토리는 탐색하지 않는다.

		for (const auto& file : directory_iterator(defaultPath + directoryName))
		{
			path = file.path();

			//비트맵 리소스만을 로드
			if (".bmp" != path.extension().u8string())
				continue;

			name = path.u8string();
			//Load()에서 defualatPath를 추가해서 쓰기 때문에 문자열에서 제거
			name.replace(name.find(defaultPath), strlen(defaultPath), "");

			//이미 가지고 있는 파일은 로드에서 제외
			if (nullptr != GetBitmap(name))
				continue;

			Load(name);
		}
	}

	Bitmap* ResourceManager::GetBitmap(const std::string& name)
	{
		std::map<std::string, Bitmap*>::iterator iter = resources.find(name);

		if (resources.end() != iter)
			return iter->second;

		return nullptr;
	}


	VOID ResourceManager::Clear()
	{
		for (std::pair<std::string, Bitmap*> resource : resources)
			DEL(resource.second);

		resources.clear();
	}

}