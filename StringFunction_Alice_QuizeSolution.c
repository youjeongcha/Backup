#pragma warning(disable:4996) //sdl해제코드(scanf_s 사용 안하려고(옵션에서 sdl 체크 해제한 것과 같음), 파일 입력 받을 때 예를 들어 지정된 배열 크기보다 더 큰 크기를 입력 받으면 메모리가 오버 되는데 그것을 막기 위해서 sdl해제를 옵션에서 해줬던 건데 이거는 그냥 코드로 해제시켜주는 것)
#include<stdio.h>
#include<time.h> //필요없음
#include<string.h>
//KMP 알고리즘을 사용한 것.
/* KMP 알고리즘??
* 문자열 탐색 알고리즘
*/
int KMPCheck(char buf[], char Check[], int Size)
{
	for (int i = 0; i <= Size / 2; i++)
	{//size 절반으로 잘라서 //경우의 수를 확인하기 더 편리
		if (buf[i] != Check[i] || buf[Size - i] != Check[Size - i])//앞 뒤 동시에 일치 불일치 찾아본다.
			return 0; //불일치
	}
	return 1; //일치
}

int KMPSearch(char buf[], char Check[], int Size)
{//buf가 한줄씩 읽어온 문자열
	int count = 0;
	for (int i = 0; buf[i] != NULL; i++)
	{//문자열 끝날때까지 한줄씩
		if (Check[0] == buf[i] && Check[Size - 1] == buf[i + Size - 1])
		{//입력한 첫글자와 마지막 글자 인덱스 안에 있는게 buf 안에 있는 것과 같으면
			if (KMPCheck(&buf[i + 1], &Check[1], Size - 3) == 1) //일치 1
			{
				count++;
				i += (Size - 1); //입력받은 문자 크기 - 1 //문자열 두개가 합쳐지면 a+b-1
				//해당 문자열이 동일하면, 해당 문자열이 든 인덱스번호는 스킵
				//KMPCheck에서 앞뒤로 판별을 하기 때문에 스킵하는 것
			}
		}
	}
	return count;
}
void main()
{
	char buf[300000] = { 0 };
	FILE* f = fopen("Alice.txt", "r");
	if (f == NULL)
	{
		printf("해당 이름의 파일이 없습니다.\n");
		return;
	}
	else
	{
		fread(buf, sizeof(buf), 1, f);
		fclose(f);
		printf("%s", buf);
		char Check[256];
		printf("Check Word Input : ");
		scanf("%s", Check);
		f = fopen("Alice.txt", "r");
		int count = 0;
		while (!feof(f))
		{
			fgets(buf, sizeof(buf), f); //fgets는 엔터 단위로 정보를 가져옴
			count += KMPSearch(buf, Check, strlen(Check)); //나는 갱신 답안은 플러스
		}
		printf("KPM Check %s Count : %d\n", Check, count);
	}
}