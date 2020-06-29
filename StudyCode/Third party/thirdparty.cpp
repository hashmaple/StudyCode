#include <stdio.h>
#include <iostream>

//#include "MyBoost.h"
#include "Testthread.h"
#include "json/Testjson.h"
#include "TestVMP.h"

int main()
{
	Testthread test_thread;
	test_thread.BeginTest();

	Testjson test_json;
	test_json.BeginTest();

	TestVMP test_vmp;
	test_vmp.BeginTest();

	int i;
	std::cin >> i;
	return 0;
}
