#include <iostream>
#include <string>
using namespace std;
//std�� namespace ��� c++ǥ�� ���̺귯���� std�� ���ִ�.

namespace A
{
	int score = 100;
	string name = "A��";
}
namespace B
{
	int score = 200;
	string name = "B��";
}

//using namespace A;
//using namespace B;
/*using �� ���� �� �´�.
using�� ���� ������ ���� �ʰڴ�*/
//���߿� ������Ʈ �Ҷ� �� ���°� ����

void main()
{
	cout << A::name << "Score = " << A::score << endl;
	cout << B::name << "Score = " << B::score << endl;
}