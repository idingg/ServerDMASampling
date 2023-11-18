#include <iostream>
#include "lz4.h"

using namespace std;

int main()
{
	string *l = new string("Hello, World!");
	cout << *l << endl;

	return 0;
}