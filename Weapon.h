#pragma once
#include "Mecro.h"
#include "MapDraw.h"
//----strcpy : ������ ���� / ������ ����--------------
//strcpy(Name, My_Name); 
// //�� ������ �� ������ ���ڿ��� ����
//----strcmp : ���ڿ��� �����ִ� �Լ�---------------
//��Ұ��� ���ؼ� �ٸ� ���ڰ� ������ ��
//(1) str1 < str2 �� ��쿡�� ���� 1 ��ȯ
//(2) str1 > str2 �� ��쿡�� ��� 1 ��ȯ
//(3) str1 == str2 �� ��쿡�� 0�� ��ȯ �մϴ�.

enum WEAPON
{
	WEAPON_DOUBLESWORD = 1,
	WEAPON_BOW,
	WEAPON_HAMMER,
	WEAPON_WAND,
	WEAPON_Count = WEAPON_WAND
};

//�߻� Ŭ������ �ٸ� ������ ��� Ŭ�����θ� ����� �� �ְ� ��ü�� ������ �� ���� Ŭ����
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
	///LATER::ȭ��ǥ�� �ش� ���⿡ Ŀ�� ������ ������ ����ִ� ������ ����� �ʹ�.
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