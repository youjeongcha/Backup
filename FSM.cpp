#include <iostream>
#include "EvilPlant.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"

/* ���� �Ĺ�. (�̸� �� ����)
   ���Ÿ� ���� ������ �����ϸ� ���� ����� ���� �������� ����鿩 ��������� ��´�.
   ��3 ��3 ����Ұ� ���̸� ���Ÿ� �����ϰ� 15���� �Ǹ� �ڽ��� �۶߸���.
   ���Ŵ� ���ִٰ� ����.

   Ž���� ���� ���� �������� ���� ���ɼ� ����
   �޽ı�� ���� �������� ���� ���ɼ� ����
*/

void  main()
{
	srand(time(NULL));
	SetTextColor(FOREGROUND_INTENSITY);

	EvilPlant evilPlant(ent_EvilPlant);

	for (int i = 0; 80 > i; i++)
	{
		//Update�� false�� ������ �Ĺ��� ���� ��. ���α׷� ����
		if (evilPlant.Update() == false)
			return;

		Sleep(1000); //���ӿ��� ���� ���X
	}

	PressAnyKeyToContinue();
}