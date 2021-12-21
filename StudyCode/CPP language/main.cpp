#include <stdio.h>
#include <iostream>

#include "CodeSafe.h"
#include "CPP98.h"
#include "C++11/C++11.h"
#include "TestCLib.h"
#include "TestSTL.h"
#include "C++11/C++11.h"
#include "C++14/C++14.h"
#include "C++17/C++17.h"
#include "x86x64/x86x64.h"
#include "DataStruct/DataStruct.h"


int main()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	SafeTest();

	TestCLib();

	TestMyStaticLib();

	TestMyDLL();

	// 调用会导致 MyLibClass使用本工程代码定义 非LIB库定义
	//MyLibClass myclass;
	//cout << "call MyStaticLib.lib MyStaticLibClass GetNumber() = "
	//	<< myclass.GetNumber() << endl;

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
	
	TestC17 cpp17;
	cpp17.BeginTest();

	x86x64 cpp3264;
	cpp3264.BeginTest();

	DataStruct dataStruct;
	dataStruct.BeginTest();


	std::cout << endl << "运行结束,请输入任意键退出" << endl;
	int i;
	std::cin >> i;
	return 0;
}
