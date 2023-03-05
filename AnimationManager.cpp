#include "AnimationManager.h"
#include"Character.h"

//Character& 을 사용하면 함수를 character 클래스만 사용할 수 있게 된다.(비효율적)
//받는 쪽에서 클래스가 지정되어 고정되기때문에 > 바인드로 주는 쪽에서 클래스를 지정하게 한다.
void AnimationManager::IntParameterPlay(std::function<void(int)> callbackFunc)//Character& 캐릭터 레퍼런스 받는 쪽이 없다. 클래스의 멤버함수는 무조건 첫 번째 함수로 어느 클래스인지 인자를 받아야 한다. > 그리고 클래스를 적용시켜주기 위해 player도 보내주는 것.
{
	int oldClock = clock();
	cout << "에니메이션 실행중..." << endl;
	while (clock() - oldClock < 1000);
	callbackFunc(100); //주의
	/*callbackFunc(*player, 100);*/
}
void AnimationManager::NonParameterPlay(std::function<void()> callbackFunc)
{
	int oldClock = clock();
	cout << "에니메이션 실행중..." << endl;
	while (clock() - oldClock < 1000);
	callbackFunc(); //주의
	/*callbackFunc(*player);*/
}