// Log.h
// ���� �� ����� ���� ����� ���� ó���ϵ��� �Ѵ�.
#pragma once
#include <Windows.h>
#include "COMException.h" // ���� ó���� ���� �������

class Log
{
public:
	static void ErrorMsg(std::string msg);
	static void ErrorMsg(HRESULT hr, std::string msg);
	static void ErrorMsg(HRESULT hr, std::wstring msg);
	static void ErrorMsg(COMException& ex);

	static void Output(LPCSTR str);
	static void Output(LPCWSTR str);
};

