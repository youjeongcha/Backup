#include<iostream>
#include<string> //string 이용할때
#include<map>
#include<Windows.h> //이거 써도 되는지
using namespace std;

#define FULLUSER 10
#define IDCOUNT 3
#define PWCOUNT 8

typedef struct User
{
	//string id; //킷값은 구조체 들어갈 필요X
	string pw;
	string name;
	int age;
	int ph;
	int mleage = 1000;
}User;

//---------------------------------------------
//-----------------회원 가입-------------------
int Select(map<string, User> UserMap)
{
	int input;
	cout << "=====Login=====(회원수[" << UserMap.size() << "명])" << endl;
	cout << "   1.회원 가입" << endl;
	cout << "   2.로그인" << endl;
	cout << "   3.종료" << endl;
	cout << "입력 : ";
	cin >> input;

	return input;
}

bool AlphaNumFunc(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!(input[i] >= '0' && input[i] <= '9') && //!이거 쓰면 Not가능하다
			!(input[i] >= 'A' && input[i] <= 'Z') &&
			!(input[i] >= 'a' && input[i] <= 'z'))
			return false;
	}
	return true;
}

string SetId(map<string, User> UserMap)
{
	string input;

	while (TRUE)
	{
		system("cls");
		cout << "아이디 입력([3글자↑] AND [한글X] : ";
		cin >> input;

		map<string, User>::iterator iter = UserMap.find(input);
		bool idCheck = AlphaNumFunc(input);

		if ((idCheck == false) || (input.length() < IDCOUNT) || (iter != UserMap.end()))
		{
			if (idCheck == false)
				cout << "id가 영문이나 숫자가 아닙니다." << endl;
			if (input.length() < IDCOUNT)
				cout << "id가 세글자 이하 입니다." << endl;
			else if (iter != UserMap.end())
				cout << "동일한 아이디가 존재합니다." << endl;
		}
		else
			break;
		system("pause");
	}
	return input;
}

bool PwFunc(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] >= '0' && input[i] <= '9')
			return true;
	}
	return false;
}

string SetPw()
{
	string pw;
	string pwRe;

	while (TRUE)
	{
		system("cls");
		cout << "비밀번호 입력([8글자↑]AND[영문]AND[숫자 포함]) : ";
		cin >> pw;
		cout << "비밀번호 확인 : ";
		cin >> pwRe;

		bool pwCheck = AlphaNumFunc(pw);
		bool pwNumCheck = PwFunc(pw);

		if ((pwCheck == false) || pw.length() < PWCOUNT || (pwNumCheck == false) || pw != pwRe)
		{
			if (pwCheck == false)
				cout << "id가 영문이나 숫자가 아닙니다." << endl;
			if (pw.length() < PWCOUNT)
				cout << "Passowrd가 여덟글자 이하입니다." << endl;
			if (pwNumCheck == false)
				cout << "Passowrd에 숫자가 포함되어 있지 않습니다." << endl;
			if (pw != pwRe)
				cout << "비밀번호가 일치하지 않습니다." << endl;
			system("pause");
		}
		else
			return pw;
	}
}

User SetInfo()
{
	User user;

	user.pw = SetPw();
	system("cls");
	cout << "닉네임 입력 : ";
	cin >> user.name;
	cout << "나이 입력 : ";
	cin >> user.age;
	cout << "휴대폰 번호 입력 : ";
	cin >> user.ph;
	cout << "회원가입 성공!! 마일리지 1000원 등록" << endl;
	return user;
}

//---------------------------------------
//----------------로그인-----------------

int Menu()
{
	int select;
	cout << "========Menu========" << endl;
	cout << "   1.회원 정보" << endl;
	cout << "   2.회원 정보 변경" << endl;
	cout << "   3.로그아웃" << endl;
	cout << "입력 : ";
	cin >> select;
	return select;
}

void UserInfo(string id, User user)
{
	cout << "============회원 정보============" << endl;
	cout << "ID : " << id << "   닉네임 : " << user.name << endl;
	cout << "나이 : " << user.age << "   휴대폰 번호 : " << user.ph << endl;
	cout << "마일리지 : " << user.mleage << "점" << endl;
}

int ChangeSelect()
{
	int select;
	cout << "==================================" << endl;
	cout << "1.닉네임 변경" << endl;
	cout << "2.나이 변경" << endl;
	cout << "3.휴대폰 번호 변경" << endl;
	cout << "4.돌아가기" << endl;
	cout << "입력 : ";
	cin >> select;
	return select;
}

User ChangeUserInfo(string id, User user)
{
	string sTemp;
	int iTemp;
	while (TRUE)
	{
		system("cls");
		UserInfo(id, user);
		switch (ChangeSelect())
		{
		case 1:
			cout << "현재 닉네임 : " << user.name << endl;
			cout << "변경할 닉네임 입력 : ";
			sTemp = user.name;
			cin >> user.name;
			cout << sTemp << " -> " << user.name << endl;
			system("pause");
			break;
		case 2:
			cout << "현재 나이 : " << user.age << endl;
			cout << "변경할 나이 입력 : ";
			iTemp = user.age;
			cin >> user.age;
			cout << iTemp << " -> " << user.age << endl;
			system("pause");
			break;
		case 3:
			cout << "현재 휴대폰 번호 : " << user.ph << endl;
			cout << "변경할 나이 입력 : ";
			iTemp = user.ph;
			cin >> user.ph;
			cout << iTemp << " -> " << user.ph << endl;
			system("pause");
			break;
		case 4:
			return user;
		}
	}
}

void Modify(map<string,User>::iterator iter)
{
	while (TRUE)
	{
		system("cls");
		switch (Menu())
		{
		case 1://회원 정보
			system("cls");
			UserInfo(iter->first, iter->second);
			system("pause");
			break;
		case 2://회원 정보 변경
			iter->second = ChangeUserInfo(iter->first, iter->second);
			break;
		case 3://로그아웃
			return;
		}
	}
}

void Login(string id, map<string, User> UserMap)
{
	string idCheck;
	string pwCheck;

	while (TRUE)
	{
		system("cls");
		cout << "아이디 입력 : ";
		cin >> idCheck;
		cout << "비밀번호 입력 : ";
		cin >> pwCheck;

		map<string, User>::iterator iter = UserMap.find(id);

		if (iter->first != idCheck)//(iter == UserMap.end()) 아이디 있으면 무조건 통과
		{
			cout << "해당 아이디가 없습니다\n";
			system("pause");
		}
		else
		{
			if (iter->second.pw != pwCheck)
			{
				cout << "비밀번호가 틀렸습니다\n";
				system("pause");
			}
			else
			{
				system("cls");
				Modify(iter); //id안 보내고 iter로 바로 수정되게 넣기
				break;
			}
		}
	}
}

void main()
{
	map<string, User> UserMap;
	string id;//킷값은 구조체에 들어갈 필요X

	while (TRUE)
	{
		system("cls");
		switch (Select(UserMap))
		{
		case 1://회원 가입
			//if (UserMap.max_size() == 1) 
			// //UserMap.max_size()는 mapContainer가 받을 수 있는 element의 maximum size반환
			if (UserMap.size() == FULLUSER)
			{
				system("cls");
				cout << "회원가입 인원수가 다 찼습니다." << endl;
				system("pause");
				break;
			}
			id = SetId(UserMap);
			UserMap[id] = SetInfo();
			system("pause");
			break;
		case 2://로그인
			Login(id, UserMap);
			break;
		case 3://종료
			return;
		}
	}
}