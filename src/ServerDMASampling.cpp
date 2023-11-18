#include <iostream>

#include "ProcStat.hpp"

using namespace std;

int main()
{
#ifdef __linux__
	// Code to execute if the OS is Linux
	cout << "linux" << endl;

	ProcStat ps;
	string ret = ps.get();
	cout << ret << endl;
#endif
	return 0;
}