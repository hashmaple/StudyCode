#include <stdio.h>
#include <iostream>

#include "CodeSafe.h"
#include "CPP98.h"
#include "C++11/NewCpp.h"
#include "MyCLib.h"
#include "TestSTL.h"
#include "C++11/C++11.h"


int main()
{
	SafeTest();
	MyCLibTest();

	CPP98 old_cpp;
	old_cpp.BeginTest();


	NewCPP new_cpp;
	new_cpp.BeginTest();

	MySTL stl_cpp;
	stl_cpp.BeginTest();

	CPP11 cpp11;
	cpp11.BeginTest();

	std::cout << endl << "运行结束,请输入任意键退出" << endl;
	int i;
	std::cin >> i;
	return 0;
}
