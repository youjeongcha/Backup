#include "Player.h"

Player::Player()
{
	mLife = MAXLIFE; //�÷��̾� ��� ����
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