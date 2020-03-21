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

#include "NewFeatures.h"
#include "GeneralUtilities.h"
#include "STLContainer.h"
#include "FunAndLambda.h"
#include "C++11String.h"
#include "MultiThread.h"

using namespace std;

CPP11::CPP11(void)
{
}

CPP11::~CPP11(void)
{
}


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

	int m = 100, n = 101;
	int &k = m;
	k = n;

	

	return;
}
