//자식 Class 객체의 주소값을 부모 Class 포인터 변수에 담아 사용한다.
//여러 자식 Class의 부모가 동일 할 경우 해당 부모 Class에 여러 자식 Class를 모아 일괄 처리한다. (ex.부모 : 동물 자식 : 고양이, 강아지,원숭이

#include <iostream>
using namespace std;

class Mammal
{
public:
	void speak(int cnt)
	{
		cout << cnt << "번 짖다" << endl;
	}
	void speak()
	{
		cout << "짖다" << endl;
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
	Mammal* ptr;
	Dog jindo;
	ptr = &jindo;
	ptr->speak();
	ptr->speak(5);
}