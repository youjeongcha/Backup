#include <iostream>
using namespace std;

enum WEEK
{//���۰� ���� �Ǵ��ϱ� ����
	WEEK_START,
	WEEK_SUN = 0,
	WEEK_MON,
	WEEK_TUE,
	WEEK_WED,
	WEEK_THU,
	WEEK_FRI,
	WEEK_SAT,
	WEEK_END
};

void main()
{//end�� null���� ����. ��ü ����� ������ �ǹ��ϱ⵵ �Ѵ�.
	//WEEK Week_List[WEEK_END];
	for (int day = WEEK_START; day != WEEK_END; day++)
		cout << day << endl;
}