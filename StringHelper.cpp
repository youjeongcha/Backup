#include "StringHelper.h"

std::wstring StringHelper::StringToWideString(std::string str)
{
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

std::string StringHelper::GetDirectoryFromPath(const std::string& filePath)
{
    size_t offset1 = filePath.find_last_of('\\'); // find_last_of() : 해당 문자의 위치를 찾지 못하면 std::string::nops를 반환.
    size_t offset2 = filePath.find_last_of('/'); // 문자를 찾으면 배열상의 인덱스를 반환
    
    //(예: find, rfind, find_first_of, find_last_of 등)에서 문자열 또는 문자의 위치를 찾지 못했을 때 반환값
    // npos의 값은 std::string::size_type 형식의 최대값으로 정의된다.

    if ((std::string::npos == offset1) && (std::string::npos == offset2))
        return "";

    if (std::string::npos == offset1)
        return std::string(filePath.substr(0, offset2)); //substr() 특정 문자열을  추출

    if (std::string::npos == offset2)
        return std::string(filePath.substr(0, offset1));
    
    //두 offset값이 다 존재하는 경우, 더 큰 값을 사용해야 한다.(0에서부터 max(offset1,offset2)까지
    return std::string(filePath.substr(0, std::max(offset1, offset2)));
}

std::string StringHelper::GetFileExtention(const std::string& fileName)
{
    size_t offset = fileName.find_last_of('.');
 
    if (std::string::npos == offset)
        return "";

    return std::string(fileName.substr(offset + 1));
}
