// COMException.h
//COM(Component Object Model)
 //DirectX의 프로그래밍 언어 독립성과 하위 호환성을 가능하게 하는 기능

#pragma once
#include <comdef.h>
#include "StringHelper.h"

class COMException
{
private:
	std::wstring error_msg;

public:
	//HRESULT는 32비트의 부호 있는 정수로 표현되며, 주로 함수 또는 메소드 호출의 결과로 반환(오류 정보 제공, 디버깅 및, 오류 처리를 톱는다.)
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
//if가 실패할 경우 'COMEException' 클래스를 생성하는 코드이다. 오류 메시지와 관련된 정보가 포함되 예외 객체가 만들어진다.(오류 처리와 디버깅에 용이)
//해당 객체는 오류 정보를 담고 있다. 
//hr : 오류 콛, msg : 오류메시지, __FILE__ : 소스 파일 이름, __FUNCTION__ : 함수 이름, __LINE__ 소스코드의 라인 번호
#define COM_ERROR_IF_FAILED(hr, msg) if (FAILED(hr)) throw COMException(hr,msg, __FILE__, __FUNCTION__, __LINE__)