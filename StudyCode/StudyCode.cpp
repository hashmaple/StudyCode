/********************************************************************
	filename: 	StudyCode
	purpose:	÷˜»Îø⁄
	created:	2014/10/17
	updated:	2014/10/17
	author:		maple(÷‹ ˜«‡)	
*********************************************************************/

#include "stdafx.h"

#include <iostream>
using namespace std;

// ≤‚ ‘STL
#define TEST_STL
// ≤‚ ‘clib
#define TEST_CLIB
// ≤‚ ‘safecode
#define TEST_SAFE
// ≤‚ ‘new cpp
#define TEST_0X
// ≤‚ ‘cpp98
#define TEST_CPP98
// ≤‚ ‘PTHREAD
#define TEST_PTHREAD

#ifdef TEST_STL
	#include "stl/TestSTL.h"
#endif

#ifdef TEST_CLIB
#include "clib/MyCLib.h"
#endif

#ifdef TEST_SAFE
#include "safe/CodeSafe.h"
#endif

#ifdef TEST_0X
#include "newCPP/NewCpp.h"
#endif

#ifdef TEST_CPP98
#include "C++98/CPP98.h"
#endif

#ifdef TEST_PTHREAD
#include "thread/Testthread.h"
#endif

#include "thread/QueryOrder.cpp"

int _tmain(int argc, _TCHAR* argv[])
{

#ifdef TEST_STL
	MySTL stl;
	stl.BeginTest();
#endif

#ifdef TEST_CLIB
	MyCLibTest();
#endif

#ifdef TEST_SAFE
	SafeTest();
#endif

#ifdef TEST_0X
	NewCPP newcpp;
	newcpp.BeginTest();
#endif

#ifdef TEST_CPP98
	CPP98 cpp98;
	cpp98.BeginTest();
#endif

#ifdef TEST_PTHREAD
	Testthread tpthread;
	tpthread.BeginTest();
#endif

	// µ»¥˝Ω· ¯
	system("pause");

	return 0;
}

