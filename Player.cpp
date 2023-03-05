#include "Player.h"

Player::Player()
{
	mLife = MAXLIFE; //플레이어 목숨 세팅
	mScore = 0;
	mName = "? ? ?";
}
Player::~Player()
{}

void Player::InitalSetting()
{
	mLife = MAXLIFE;
	mScore = 0;
	mName = "? ? ?";
}

void Player::DecreasePlayerLife()
{
	mLife--;
}