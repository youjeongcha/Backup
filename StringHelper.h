// StringHelper.h
#pragma once
#include <string>
class StringHelper
{
public:
	//문자열을 와이드 문자열로 변환
	static std::wstring StringToWideString(std::string str); 
	//파일명을 제외한 폴더까지의 경로를 알아온다.
	static std::string GetDirectoryFromPath(const std::string& filePath); 
	//파일의 확장자를 알아온다.
	static std::string GetFileExtention(const std::string& fileName); 
};

