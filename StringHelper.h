// StringHelper.h
#pragma once
#include <string>
class StringHelper
{
public:
	//���ڿ��� ���̵� ���ڿ��� ��ȯ
	static std::wstring StringToWideString(std::string str); 
	//���ϸ��� ������ ���������� ��θ� �˾ƿ´�.
	static std::string GetDirectoryFromPath(const std::string& filePath); 
	//������ Ȯ���ڸ� �˾ƿ´�.
	static std::string GetFileExtention(const std::string& fileName); 
};

