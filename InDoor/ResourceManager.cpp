#include "ResourceManager.h"
#include <fstream>
#include <io.h> //access()

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //c++17 �̻��� ��� #include<filesystem>�� ���.
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
		// 0 : ���� �� ���丮�� ���� ����
		// 2 : ���� ���� ���� ����
		// 4 : �б� ���� ���� ����
		// 6 : �б� ���� ���� ���� ����
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
		//directory_iterator : ���丮(����) ���� ���� �� ������ ã�´�. ���� ���丮�� Ž������ �ʴ´�.

		for (const auto& file : directory_iterator(defaultPath + directoryName))
		{
			path = file.path();

			//��Ʈ�� ���ҽ����� �ε�
			if (".bmp" != path.extension().u8string())
				continue;

			name = path.u8string();
			//Load()���� defualatPath�� �߰��ؼ� ���� ������ ���ڿ����� ����
			name.replace(name.find(defaultPath), strlen(defaultPath), "");

			//�̹� ������ �ִ� ������ �ε忡�� ����
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