#include <stdio.h>
#include <iostream>

//#include "MyBoost.h"
#include "TestHeader.h"

using namespace std;

int main()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

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

	TestXML test_xml;
	test_xml.BeginTest();

	WinSocketServer socketServer;
	socketServer.BeginTest();

	WinSocketClient socketClient;
	socketClient.BeginTest();

	FileCleanUp file_cleanup;
	file_cleanup.BeginTest();

	int i;
	std::cin >> i;
	return 0;
}
