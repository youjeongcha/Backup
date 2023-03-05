#include <iostream>
using namespace std;

enum WEEK
{
	WEEK_SUN,
	WEEK_MON,
	WEEK_TUE,
	WEEK_WED,
	WEEK_THU,
	WEEK_FRI,
	WEEK_SAT
};

void main()
{
	WEEK today = WEEK_MON;
	//WEEK::WEEK_FRI //목록 접근 가능
	switch (today)
	{
	case WEEK_SUN:
			cout << "일요일 입니다.";
			break;	
	case WEEK_MON:
			cout << "월요일 입니다.";
			break;	
	case WEEK_TUE:
			cout << "화요일 입니다.";
			break;	
	case WEEK_WED:
			cout << "수요일 입니다.";
			break;	
	case WEEK_THU:
			cout << "목요일 입니다.";
			break;	
	case WEEK_FRI:
			cout << "금요일 입니다.";
			break;	
	case WEEK_SAT:
			cout << "토요일 입니다.";
			break;	
	}
}