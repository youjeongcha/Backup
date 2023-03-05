//부모 class의 함수의 처리동작이 마음에 들지 않을 경우 동일한 이름으로 자식 class가 만들어 재정의 한다.

#include <iostream>
using namespace std;

class Mammal
{
public:
	void speak(int cnt)
	{
		cout << cnt << "번 짖어" << endl;
	}
	void speak()
	{
		cout << "짖어" << endl;
	}
};

class Dog : public Mammal
{
public:
	void speak()
	{
		cout << "멍멍" << endl;
	}
};

void main()
{
	Mammal dongmul;
	Dog jindo;
	dongmul.speak();
	dongmul.speak(3);
	jindo.speak();
	//jindo.speak(5);
}