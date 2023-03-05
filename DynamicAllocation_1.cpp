//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
using namespace std;

void main()
{
	int* ptr;
	//ptr = (int*)malloc(sizeof(int));
	ptr = new int;

	*ptr = 10;
	//printf("%d", *ptr);
	cout << *ptr << endl;
	cout << ptr << endl;
	//free(ptr);
	delete ptr;
}