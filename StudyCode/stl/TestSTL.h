/********************************************************************
	filename: 	TestSTL
	purpose:	����STL
	created:	2014/10/17
	updated:	2014/10/17
	author:		maple(������)	
*********************************************************************/
#pragma once

#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class MySTL
{
public:
	MySTL(void);
	~MySTL(void);

	// ����ӿ�
	void BeginTest();

	// �ڲ�����
private:
	void Add(int& value, int addvalue);

	template<class _FwdIt1> inline bool sPrint(_FwdIt1 _First1, _FwdIt1 _Last1);

	template<class power> power sPower(power value);

	std::wstring GetWString();

	std::vector<int> GetVector();
};
