//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
using namespace std;

void main()
{
	int* ptr;
	//ptr = (int*)malloc(sizeof(int));
	ptr = new int[2];

	ptr[0] = 10;
	ptr[1] = 20;
	//printf("%d", *ptr);
	cout << ptr[0] << endl;
	cout << ptr[1] << endl;
	//free(ptr);
	delete []ptr; //?

}