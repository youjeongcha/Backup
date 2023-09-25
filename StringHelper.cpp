#include "StringHelper.h"

std::wstring StringHelper::StringToWideString(std::string str)
{
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

std::string StringHelper::GetDirectoryFromPath(const std::string& filePath)
{
    size_t offset1 = filePath.find_last_of('\\'); // find_last_of() : �ش� ������ ��ġ�� ã�� ���ϸ� std::string::nops�� ��ȯ.
    size_t offset2 = filePath.find_last_of('/'); // ���ڸ� ã���� �迭���� �ε����� ��ȯ
    
    //(��: find, rfind, find_first_of, find_last_of ��)���� ���ڿ� �Ǵ� ������ ��ġ�� ã�� ������ �� ��ȯ��
    // npos�� ���� std::string::size_type ������ �ִ밪���� ���ǵȴ�.

    if ((std::string::npos == offset1) && (std::string::npos == offset2))
        return "";

    if (std::string::npos == offset1)
        return std::string(filePath.substr(0, offset2)); //substr() Ư�� ���ڿ���  ����

    if (std::string::npos == offset2)
        return std::string(filePath.substr(0, offset1));
    
    //�� offset���� �� �����ϴ� ���, �� ū ���� ����ؾ� �Ѵ�.(0�������� max(offset1,offset2)����
    return std::string(filePath.substr(0, std::max(offset1, offset2)));
}

std::string StringHelper::GetFileExtention(const std::string& fileName)
{
    size_t offset = fileName.find_last_of('.');
 
    if (std::string::npos == offset)
        return "";

    return std::string(fileName.substr(offset + 1));
}
