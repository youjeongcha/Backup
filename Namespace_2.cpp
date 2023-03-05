#include <iostream>
#include <string>
using namespace std;
//std도 namespace 모든 c++표준 라이브러리가 std에 들어가있다.

namespace A
{
	int score = 100;
	string name = "A팀";
}
namespace B
{
	int score = 200;
	string name = "B팀";
}

//using namespace A;
//using namespace B;
/*using 안 쓰는 게 맞다.
using은 구역 구분을 하지 않겠다*/
//나중에 프로젝트 할때 안 쓰는게 좋음

void main()
{
	cout << A::name << "Score = " << A::score << endl;
	cout << B::name << "Score = " << B::score << endl;
}