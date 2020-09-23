#include <stdio.h>
#include <iostream>

//#include "MyBoost.h"
#include "Testthread.h"
#include "json/Testjson.h"
#include "TestVMP.h"
#include "TestLua.h"
#include "TestPython.h"
#include "TestLibcurl.h"

int main()
{
	Testthread test_thread;
	test_thread.BeginTest();

	Testjson test_json;
	test_json.BeginTest();

	TestVMP test_vmp;
	test_vmp.BeginTest();

	TestLua test_lua;
	test_lua.BeginTest();

	TestPython test_python;
	test_python.BeginTest();

	TestLibcurl test_libcurl;
	test_libcurl.BeginTest();

	int i;
	std::cin >> i;
	return 0;
}
