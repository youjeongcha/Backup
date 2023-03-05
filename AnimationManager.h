#pragma once
#include<iostream>
#include<functional>//함수 포인터
#include<time.h>
using namespace std;

class Character;
class AnimationManager
{

public:
	//함수 포인터
	void Play(std::function<void(Character&,int)> callbackFunc,Character *player);
	void Play(std::function<void(Character&)> callbackFunc, Character* player);
};
