#pragma once
#include<iostream>
#include<functional>//함수 포인터
#include<time.h>
using namespace std;
//주의

class Character;
class AnimationManager
{

public:
	//함수 포인터에서 바인드 사용
	/*	void Play(std::function<void(Character&,int)> callbackFunc,Character *player);
	void Play(std::function<void(Character&)> callbackFunc, Character* player);*/
	void IntParameterPlay(std::function<void(int)> callbackFunc);
	void NonParameterPlay(std::function<void()> callbackFunc);
};

