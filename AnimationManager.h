#pragma once
#include<iostream>
#include<functional>//�Լ� ������
#include<time.h>
using namespace std;

class Character;
class AnimationManager
{

public:
	//�Լ� ������
	void Play(std::function<void(Character&,int)> callbackFunc,Character *player);
	void Play(std::function<void(Character&)> callbackFunc, Character* player);
};
