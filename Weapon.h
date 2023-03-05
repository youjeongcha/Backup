#pragma once
#include "Mecro.h"
#include "MapDraw.h"
//----strcpy : 복사할 공간 / 복사할 내용--------------
//strcpy(Name, My_Name); 
// //앞 변수에 뒷 변수의 문자열을 복사
//----strcmp : 문자열을 비교해주는 함수---------------
//대소관계 비교해서 다른 인자가 나왔을 때
//(1) str1 < str2 인 경우에는 음수 1 반환
//(2) str1 > str2 인 경우에는 양수 1 반환
//(3) str1 == str2 인 경우에는 0을 반환 합니다.

enum WEAPON
{
	WEAPON_DOUBLESWORD = 1,
	WEAPON_BOW,
	WEAPON_HAMMER,
	WEAPON_WAND,
	WEAPON_Count = WEAPON_WAND
};

//추상 클래스는 다른 형식의 기반 클래스로만 사용할 수 있고 개체를 생성할 수 없는 클래스
class Weapon abstract
{
protected:
	WEAPON mWeaponEnum;
	string mType;
	string mName;
	int mPrice;
	int mAttack;

	int mCriticalRate;
	string mCriticalWords;
	long double mRisingPercentage;
	///LATER::화살표가 해당 무기에 커서 있으면 설명을 띄워주는 구조로 만들고 싶다.
public:
	//Weapon();
	//~Weapon();

	void PrintInfo(int _Y);
	void SimpleInfo(int _Y);

	void Set(string _name, int _price, int _attack) { mName = _name; mPrice = _price; mAttack = _attack; }
	void SetCritical(int _criticalRate, string _criticalWords, long double _risingPercentage) {	mCriticalRate = _criticalRate, mCriticalWords = _criticalWords, mRisingPercentage = _risingPercentage; }

	string GetType() { return mType; }
	WEAPON GetWeaponEnum() { return mWeaponEnum; }
	string GetName() { return mName; }
	int GetPrice() { return mPrice; }
	int GetAttack() { return mAttack; }

	int GetCriticalRate() { return mCriticalRate; }
	string GetCriticalWords() { return mCriticalWords; }
	long double GetRisingPercentage() { return mRisingPercentage; }
};