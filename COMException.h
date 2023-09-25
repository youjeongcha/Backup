// COMException.h
//COM(Component Object Model)
 //DirectX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���

#pragma once
#include <comdef.h>
#include "StringHelper.h"

class COMException
{
private:
	std::wstring error_msg;

public:
	//HRESULT�� 32��Ʈ�� ��ȣ �ִ� ������ ǥ���Ǹ�, �ַ� �Լ� �Ǵ� �޼ҵ� ȣ���� ����� ��ȯ(���� ���� ����, ����� ��, ���� ó���� ��´�.)
	COMException(HRESULT hr, const std::string& msg, const std::string& file, const std::string& function, int line)
	{
		_com_error error(hr);
		error_msg = L"Msg: " + StringHelper::StringToWideString(file);
		error_msg += error.ErrorMessage();
		error_msg += L"WnFile: " + StringHelper::StringToWideString(file);
		error_msg += L"WnFunction: " + StringHelper::StringToWideString(function);
		error_msg += L"WnLine: " + std::to_wstring(line);
	}
	const wchar_t* what() const { return error_msg.c_str(); }
};
//if�� ������ ��� 'COMEException' Ŭ������ �����ϴ� �ڵ��̴�. ���� �޽����� ���õ� ������ ���Ե� ���� ��ü�� ���������.(���� ó���� ����뿡 ����)
//�ش� ��ü�� ���� ������ ��� �ִ�. 
//hr : ���� ��, msg : �����޽���, __FILE__ : �ҽ� ���� �̸�, __FUNCTION__ : �Լ� �̸�, __LINE__ �ҽ��ڵ��� ���� ��ȣ
#define COM_ERROR_IF_FAILED(hr, msg) if (FAILED(hr)) throw COMException(hr,msg, __FILE__, __FUNCTION__, __LINE__)