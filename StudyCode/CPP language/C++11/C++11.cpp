/*!
 * \file C++11.cpp
 * \date 2018/12/24 14:05
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief learn c++11 standard code
 *
 * TODO: long description
 *
 * \note
*/
#include "C++11.h"

using namespace std;

/////////////////////////////对外接口/////////////////////////////////////////////
// CPP11
void CPP11::BeginTest()
{
	NewFeatures NF;
	NF.BeginTest();

	GeneralUtilities GU;
	GU.BeginTest();

	STLContainer container;
	container.BeginTest();

	FunAndLambda funLambda;
	funLambda.BeginTest();

	NewString newString;
	newString.BeginTest();

	MultiThread multiThread;
	multiThread.BeginTest();

	return;
}
