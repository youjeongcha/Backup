#include <iostream>
#include <string> //string 이용할때
#include <Windows.h>
#include <list> //list 이용
using namespace std;

#define IDLEN 3
#define PASSWORDLEN 8
#define IDMAX 10

struct Member //typedef struct Member 왜 안 하는지
{//typedef는 c에서만 필요했다.
	string Id;
	string Password;
	string Name;
	int Age;
	string PhonNumber;
	int Mileage;
};//Member ?


bool StringCheck(char Start, char End, char Check)
{//유의깊게 보기
	if (Check >= Start && Check <= End)
		return true;
	else return false;
}

string CreateID(list<Member> Member_List)
{
	bool EngCheck, IDCheck;
	string id;
	do
	{
		EngCheck = true;
		IDCheck = true;
		system("cls");
		cout << "아이디 입력([3글자↑] AND [한글X]) : ";
		cin >> id;
		for (int i = 0; i < id.length(); i++)
		{
			if (StringCheck('A', 'Z', id[i]) == false && StringCheck('a', 'z', id[i]) == false
				&& StringCheck('0', '9', id[i]) == false)
			{
				EngCheck = false;
				break;
			}
		}
		//auto i = 10.0f;하면 i는 실수
		for (auto iter = Member_List.begin(); iter != Member_List.end(); iter++)
			//auto는 자료형을 초기에 받은 값으로 지정해준다.
			//list<Member>::iterator iter로 하는 게 정석이자 베스트
		{
			if (iter->Id == id)
				IDCheck = false;
		}
		if (IDCheck == false)
			cout << "동일한 아이디가 존재합니다." << endl;
		if (EngCheck == false)
			cout << "id가 영문이 아닙니다." << endl;
		if (id.length() < IDLEN)
			cout << "id가 세글자 이하 입니다." << endl;
		system("pause");
	} while (EngCheck == false || IDCheck == false || id.length() < IDLEN);
	return id;
}

string CreatePassword()
{
	string Password, ComparePassword;
	bool EngCheck, CompareCheck, IDCheck, NumberCheck; //IDCheck ?
	do
	{
		EngCheck = true;
		CompareCheck = true;
		NumberCheck = false;

		system("cls");
		cout << "비밀번호 입력([8글자↑]AND[영문]AND[숫자 포함]) : ";
		cin >> Password;
		for (int i = 0; i < Password.length(); i++)
		{//비밀 번호 숫자 체크 코드와, 비밀번호 확인 코드의 순서 > 가독성 유의
			if (StringCheck('A', 'Z', Password[i]) == false && StringCheck('a', 'z', Password[i]) == false)
			{
				if (StringCheck('0', '9', Password[i]) == true)
					NumberCheck = true;
				else
					EngCheck = false;
			}
		}
		cout << "비밀번호 확인 : ";
		cin >> ComparePassword;
		if (ComparePassword != Password)
			CompareCheck = false;

		if (EngCheck == false)
			cout << "password가 영문이 아닙니다." << endl;
		if (Password.length() < PASSWORDLEN)
			cout << "Password가 여덟글자 이하 입니다." << endl;
		if (NumberCheck == false)
			cout << "숫자가 포함되어 있지 않습니다." << endl;
		if (CompareCheck == false)
			cout << "비밀번호가 일치하지 않습니다." << endl;
		system("pause");
	} while (EngCheck == false || CompareCheck == false || NumberCheck == false || Password.length() < PASSWORDLEN);
	return Password;
}

Member Join(list<Member> Member_List)
{
	bool EngCheck, CompareCheck, IDCheck; //?
	int CountNum = 0; //?
	string CheckPassword; //?
	Member member;
	member.Id = CreateID(Member_List);
	member.Password = CreatePassword();
	system("cls");
	cout << "닉네임 입력 : ";
	cin >> member.Name;
	cout << "나이 입력 :";
	cin >> member.Age;
	cout << "휴대폰 번호 입력 : ";
	cin >> member.PhonNumber;
	cout << "회원가입 성공 !! 마일리지 1000원 등록" << endl;
	member.Mileage = 1000;
	system("pause");
	return member;
}

void SimpleShowID(Member member)
{
	cout << "============회원 정보============" << endl;
	cout << "ID : " << member.Id << "   닉네임 : " << member.Name << endl;
}

void ShowID(Member member)
{
	system("cls");
	SimpleShowID(member);
	cout << " 나이 : " << member.Age << "살" << "   휴대폰 번호 : " << member.PhonNumber << endl;
	cout << "마일리지 : " << member.Mileage << "원" << endl;
}

void Setstring(string* str, string tmp)//여기는 얕은 복사
{//유의
	string tmpstr;
	tmpstr = *str;//복사 //*str이 주소값인데 내부적으로 처리해줌. strcpy와 같음ㄴ
	cout << "현재 " << tmp << ": " << tmpstr << endl;
	cout << "변경할 " << tmp << "입력 : ";
	cin >> *str;
	cout << tmpstr << " -> " << *str << endl;
	system("pause");
}

void Setint(int* num, string tmp)
{//유의
	int tmpint;
	tmpint = *num;
	cout << "현재 " << tmp << " : " << tmpint << endl;
	cout << "변경할 " << tmp << "입력 : ";
	cin >> *num;
	cout << tmpint << " -> " << *num << endl;
	system("pause");
}

void SetID(list<Member>::iterator member)
{
	int Select;
	while (1)
	{
		ShowID(*member);
		cout << "===================" << endl;
		cout << "1.닉네임 변경" << endl;
		cout << "2.나이 변경" << endl;
		cout << "3.휴대폰 번호 변경" << endl;
		cout << "4.돌아가기" << endl;
		cout << "입력 : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			Setstring(&member->Name, "닉네임");//유의 //주소 전달? //"닉네임"이 전달되는 원리 ?
			break;
		case 2:
			Setint(&member->Age, "나이");
			break;
		case 3:
			Setstring(&member->PhonNumber, "휴대폰 번호");
			break;
		case 4:
			return;
		}
	}
}


void Display(list<Member>::iterator member)
{
	int Select;
	while (1)
	{
		system("cls");
		cout << "========Menu========" << endl;
		cout << "  1.회원 정보" << endl;
		cout << "  2.회원 정보 변경" << endl;
		cout << "  3.로그아웃" << endl;
		cout << "입력 : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			ShowID(*member);
			system("pause");
			break;
		case 2:
			SetID(member);
			break;
		case 3:
			return;
		}
	}
}

void Login(list<Member>* MemberList)
{
	string tmpID, tmpPassword;
	system("cls");
	cout << "아이디 입력 : ";
	cin >> tmpID;
	cout << "비밀번호 입력 : ";
	cin >> tmpPassword;
	for (auto iter = MemberList->begin(); iter != MemberList->end(); iter++) // ?
	{
		if (tmpID == iter->Id)
		{
			if (tmpPassword == iter->Password)
				Display(iter);
			else
				cout << "비밀번호가 틀렸습니다." << endl;
			return;
		}
	}
	cout << "해당 아이디가 없습니다." << endl;
}

void main()
{
	list<Member> MemberList;
	string TmpId, TmpPassword; // ?
	int Select;
	while (1)
	{
		system("cls");
		cout << "=====Login=====(회원수[" << MemberList.size() << "명])" << endl;
		cout << "   1.회원 가입" << endl;
		cout << "   2.로그인" << endl;
		cout << "   3.종료" << endl;
		cout << "입력 : ";
		cin >> Select;
		switch (Select)
		{
		case 1:
			if (MemberList.size() >= IDMAX)
			{
				cout << "더이상 회원을 등록할 수 없습니다." << endl;
				break;
			}
			MemberList.push_back(Join(MemberList));
			break;
		case 2:
			Login(&MemberList);
			break;
		case 3:
			return;
		}
		system("pause");
	}
}

