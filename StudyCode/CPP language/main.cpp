#include <stdio.h>
#include <iostream>

#include "CodeSafe.h"
#include "CPP98.h"
#include "C++11/NewCpp.h"
#include "MyCLib.h"
#include "TestSTL.h"
#include "C++11/C++11.h"
#include "C++14/C++14.h"


int main()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

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

	TestC14 cpp14;
	cpp14.BeginTest();

	std::cout << endl << "���н���,������������˳�" << endl;
	int i;
	std::cin >> i;
	return 0;
}
