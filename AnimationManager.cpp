#include "AnimationManager.h"
#include"Character.h"

//Character& �� ����ϸ� �Լ��� character Ŭ������ ����� �� �ְ� �ȴ�.(��ȿ����)
//�޴� �ʿ��� Ŭ������ �����Ǿ� �����Ǳ⶧���� > ���ε�� �ִ� �ʿ��� Ŭ������ �����ϰ� �Ѵ�.
void AnimationManager::Play(std::function<void(Character&, int)> callbackFunc, Character *player)//Character& ĳ���� ���۷��� �޴� ���� ����. Ŭ������ ����Լ��� ������ ù ��° �Լ��� ��� Ŭ�������� ���ڸ� �޾ƾ� �Ѵ�. > �׸��� Ŭ������ ��������ֱ� ���� player�� �����ִ� ��.
{
	int oldClock = clock();
	cout << "���ϸ��̼� ������..." << endl;
	while (clock() - oldClock < 1000);
	callbackFunc(*player,100);
}
void AnimationManager::Play(std::function<void(Character&)> callbackFunc, Character* player)
{
	int oldClock = clock();
	cout << "���ϸ��̼� ������..." << endl;
	while (clock() - oldClock < 1000);
	callbackFunc(*player);
}