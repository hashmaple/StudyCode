#include <stdio.h>
#include <iostream>

#include "CodeSafe.h"
#include "CPP98.h"
#include "NewCpp.h"
#include "MyCLib.h"
#include "TestSTL.h"


int main()
{
	SafeTest();
	MyCLibTest();

	CPP98 old_cpp;
	old_cpp.BeginTest();

	NewCPP new_cpp;
	new_cpp.BeginTest();

	MySTL stl_cpp;
	new_cpp.BeginTest();

	int i;
	std::cin >> i;
	return 0;
}
