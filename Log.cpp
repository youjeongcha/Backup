#include "Log.h"

void Log::ErrorMsg(std::string msg)
{
	MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR);
	//���� �޽����� ǥ��. ���� �ڵ�('HRESULT')�� ó������ �ʰ� �ܼ��� ���ڿ� �޽����� ����Ѵ�.
}

void Log::ErrorMsg(HRESULT hr, std::string msg)
{
	ErrorMsg(hr, StringHelper::StringToWideString(msg));
	//'HRESULT' ���� 'std::wstring'������ �޽����� �޾ƿ� '_com_error' Ŭ������ ����Ͽ� ���� ������ ��� �ش� ������ �޽����� �����Ͽ� Windows 'MessageBoxW'�Լ��� ����Ͽ� ���� �޽����� ǥ���Ѵ�.
}

void Log::ErrorMsg(HRESULT hr, std::wstring msg)
{
	//_com_error Ŭ������ ����Ͽ� ���� ������ ���
	//�ش� ������ �޽����� �����Ͽ� Windows MessageBoxW �Լ��� ����Ͽ� ���� �޽����� ǥ��
	_com_error error(hr);
	std::wstring log = msg + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, log.c_str(), L"Error", MB_ICONERROR);
}

void Log::ErrorMsg(COMException& ex)
{
	//COMException ���� ��ü�� �޾ƿ� ���� ��ü�� what() �Լ��� ����Ͽ� ���� �޽����� ����մϴ�. �̰��� ����� ���� ���� ó���� ���� �Լ�
	MessageBoxW(NULL, ex.what(), L"Error", MB_ICONERROR);
}

void Log::Output(LPCSTR str)
{
	OutputDebugStringA(str);
	// ���ڿ��� Windows�� OutputDebugStringA �� OutputDebugStringW �Լ��� ����Ͽ� ����� ��� â�� ���
}

void Log::Output(LPCWSTR str)
{
	OutputDebugStringW(str);
}
