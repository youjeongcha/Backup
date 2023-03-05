#include <stdio.h>
#include <stdlib.h>

void main()
{
	int* pNum = (int*)malloc(sizeof(int));
	*pNum = 10;
	printf("pNum주소 = %p\npNum값 = %d", pNum, *pNum);
	free(pNum);
	//*pNum = 20;
	pNum = NULL;
	printf("\npNum주소 = %p\npNum값 = %d", pNum, *pNum);
	//해제후 접근하면 안된다.

	//동적 할당은 메모리가 있는 것에서 쓰는것
	//랩카드 플래시 메모리에서 할당을 하는데
	//제약 없이 쓰면 윈도우즈는 멀티 프로세싱 여러개 프로그램을 돌릴 수 있는데
	//특정 프로그램 둘이 메모리를 a 쓰고 이쓴ㄴ데 다른 프로그램이 a또 쓰겠다고 하면 문제가 생기므로
	//프로그램 독점을 해야 한 특정 메모리에 대한 권한을 할당 받아야.
	//해당 메모리에 대한 권한을 반납 하는 개념. free()
}