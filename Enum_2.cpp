#include <iostream>
using namespace std;

enum WEEK
{//시작과 끝을 판단하기 쉽게
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
{//end가 null같은 역할. 전체 요소의 갯수를 의미하기도 한다.
	//WEEK Week_List[WEEK_END];
	for (int day = WEEK_START; day != WEEK_END; day++)
		cout << day << endl;
}