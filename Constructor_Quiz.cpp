#include<iostream>
using namespace std;

class Quiz
{
private:
	int a, b;
public:
	Quiz(int a = 10, int b = 1)
	{
		int tmp;

		this->a = a;
		this->b = b;

		if (b > a) //b가 더 작아야 함
		{
			tmp = a;
			a = b;
			b = tmp;
		}
	}
	void print()
	{
		int tmp = 0;

		for (int i = b; i <= a; i++)
		{
			tmp += i;
		}

		cout << tmp << "\n";
	}
};

void main()
{
	Quiz Q1;
	cout << "Q1() : ";
	Q1.print();

	Quiz Q2(100);
	cout << "Q2(100) : ";
	Q2.print();

	Quiz Q3(5, 10);
	cout << "Q3(5, 10) : ";
	Q3.print();
}