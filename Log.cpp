#include "Log.h"

void Log::ErrorMsg(std::string msg)
{
	MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR);
	//에러 메시지를 표시. 오류 코드('HRESULT')를 처리하지 않고 단순히 문자열 메시지를 출력한다.
}

void Log::ErrorMsg(HRESULT hr, std::string msg)
{
	ErrorMsg(hr, StringHelper::StringToWideString(msg));
	//'HRESULT' 값과 'std::wstring'형식의 메시지를 받아와 '_com_error' 클래스를 사용하여 오류 정보를 얻고 해당 정보와 메시지를 조합하여 Windows 'MessageBoxW'함수를 사용하여 에러 메시지를 표시한다.
}

void Log::ErrorMsg(HRESULT hr, std::wstring msg)
{
	//_com_error 클래스를 사용하여 오류 정보를 얻고
	//해당 정보와 메시지를 조합하여 Windows MessageBoxW 함수를 사용하여 에러 메시지를 표시
	_com_error error(hr);
	std::wstring log = msg + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, log.c_str(), L"Error", MB_ICONERROR);
}

void Log::ErrorMsg(COMException& ex)
{
	//COMException 예외 객체를 받아와 예외 객체의 what() 함수를 사용하여 예외 메시지를 출력합니다. 이것은 사용자 정의 예외 처리를 위한 함수
	MessageBoxW(NULL, ex.what(), L"Error", MB_ICONERROR);
}

void Log::Output(LPCSTR str)
{
	OutputDebugStringA(str);
	// 문자열을 Windows의 OutputDebugStringA 및 OutputDebugStringW 함수를 사용하여 디버그 출력 창에 출력
}

void Log::Output(LPCWSTR str)
{
	OutputDebugStringW(str);
}
