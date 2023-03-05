#include "AnimationManager.h"
#include"Character.h"

//Character& �� ����ϸ� �Լ��� character Ŭ������ ����� �� �ְ� �ȴ�.(��ȿ����)
//�޴� �ʿ��� Ŭ������ �����Ǿ� �����Ǳ⶧���� > ���ε�� �ִ� �ʿ��� Ŭ������ �����ϰ� �Ѵ�.
void AnimationManager::IntParameterPlay(std::function<void(int)> callbackFunc)//Character& ĳ���� ���۷��� �޴� ���� ����. Ŭ������ ����Լ��� ������ ù ��° �Լ��� ��� Ŭ�������� ���ڸ� �޾ƾ� �Ѵ�. > �׸��� Ŭ������ ��������ֱ� ���� player�� �����ִ� ��.
{
	int oldClock = clock();
	cout << "���ϸ��̼� ������..." << endl;
	while (clock() - oldClock < 1000);
	callbackFunc(100); //����
	/*callbackFunc(*player, 100);*/
}
void AnimationManager::NonParameterPlay(std::function<void()> callbackFunc)
{
	int oldClock = clock();
	cout << "���ϸ��̼� ������..." << endl;
	while (clock() - oldClock < 1000);
	callbackFunc(); //����
	/*callbackFunc(*player);*/
}