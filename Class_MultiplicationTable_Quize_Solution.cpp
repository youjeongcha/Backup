#include<iostream>
using namespace std;

class GuGuDan
{
private:
	int StartGuGuDan;
	int EndGuGuDan;
public:
	void SetGuGuDan()
	{
		while (1)
		{
			cout << "시작 단 입력 : ";
			cin >> StartGuGuDan;
			cout << "끝 단 입력 : ";
			cin >> EndGuGuDan;
			if (StartGuGuDan < 2 || StartGuGuDan > 9) //if문 처리하는 쪽도 고려
				cout << "시작 단이 2보다 작거나 9보다 큽니다." << endl;
			else if (EndGuGuDan < 2 || EndGuGuDan > 9)
				cout << "끝 단이 2보다 작거나 9보다 큽니다." << endl;
			else if (StartGuGuDan > EndGuGuDan)
				cout << "시작 단이 끝 단보다 큽니다." << endl;
			else
				break;
			system("pause");
		}
	}
	void ShowGuGuDan()
	{
		for (int j = 0; j <= 9; j++)
		{
			for (int i = StartGuGuDan; i <= EndGuGuDan; i++)
			{//가로로 2단*1 3단*1 4단*1 식으로 먼저 출력하고 *9까지 순서대로 출력
				if (j == 0) //j가 시작하기 전에 제일 먼저 출력 처리 //주의
					cout << "=======" << i << "단=======\t";
				else
					cout << "    " << i << " x " << j << " = " << i * j << "\t\t";
			}
			cout << endl;
		}
	}
};

void main()
{
	GuGuDan Gu1;
	Gu1.SetGuGuDan();
	Gu1.ShowGuGuDan();
}