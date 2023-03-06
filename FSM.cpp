#include <iostream>
#include "EvilPlant.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"

/* 마계 식물. (이름 안 정함)
   열매를 만들 영양이 부족하면 향기로 사람과 몬스터 동물들을 끌어들여 영양분으로 삼는다.
   마3 피3 영양소가 모이면 열매를 생성하고 15개가 되면 자식을 퍼뜨린다.
   열매는 맛있다고 하자.

   탐지는 향기로 넓은 범위에서 먹이 가능성 높음
   휴식기는 좁은 범위에서 먹이 가능성 낮음
*/

void  main()
{
	srand(time(NULL));
	SetTextColor(FOREGROUND_INTENSITY);

	EvilPlant evilPlant(ent_EvilPlant);

	for (int i = 0; 80 > i; i++)
	{
		//Update에 false가 들어오면 식물이 죽은 것. 프로그램 종료
		if (evilPlant.Update() == false)
			return;

		Sleep(1000); //게임에선 절대 사용X
	}

	PressAnyKeyToContinue();
}