/********************************************************************
	filename: 	NewCPP
	purpose:	����C++ 0X ���±�׼
	https://zh.cppreference.com/w/cpp
	created:	2015/2/5
	updated:	2015/2/5
	author:		maple(������)	
*********************************************************************/
#include "NewCPP.h"

#include <algorithm>
#include <functional>
#include <exception>
#include <iostream>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

#define PR(...) printf(__VA_ARGS__)

NewCPP::NewCPP(void)
{
}

NewCPP::~NewCPP(void)
{
}

class temp
{
	public:
	temp()
	{
		cout << "temp create once" << endl;
	}
	// �ƶ����캯��
	temp(temp&& other)
	{
		str = std::move(other.str);
		pChar = std::move(other.pChar);
		other.pChar = nullptr;
		cout << "temp create && once" << endl;
	}
	~temp()
	{
		delete pChar;
		cout << "temp destory once" << endl;
	}
public:
	string str;
	char* pChar;
};

temp ReturnStr()
{
	temp t1;
	t1.str = "zsq";
	t1.pChar = new char();
	return t1;
}
/////////////////////////////����ӿ�/////////////////////////////////////////////
// NewCPP
void NewCPP::BeginTest()
{
	// ����Ԥ�����
	if (false)
	{
		// c99 is __func__
		cout << "output __FUNCTION__: " << __FUNCTION__ << endl;
		cout << "output __FILE__: " << __FILE__ << endl; 
		cout << "output __DATE__: " << __DATE__ << endl;
		cout << "output __cplusplus: " << __cplusplus << endl;

		// ������в���
		PR("printf: %d,%s\n",1,"aaa");
	}

	// long long
	if (false)
	{
		// 64λ������
		long long lint = 123456789987654321LL;
		lint = LLONG_MAX;
		cout << "long long num is: " << lint << endl;
		cout << "long long sizeof is: " << sizeof(lint) << endl;
	}

	// �ƶ�����
	if (false)
	{
		// ͨ���ƶ�����
		temp s1 = ReturnStr();
		temp s2 = ReturnStr();

		cout << s1.str<< endl;
		cout << s2.str<< endl;
	}

	// ���ϳ�ʼ��
	if (false)
	{
		int i = 3 + 4;
		int a[] = {1,2,3,4,5};
		vector<int> vct = {1,2,3,4,5};

		// �Ƿ�POD���� 
		// POD���Ϳ��԰�ȫ����C �� C++֮���໥����
		// POD���Ϳ���ֱ���ڴ����memset memcpy
		cout << is_pod<temp>::value << endl;
	}

	// lambda����
	if (false)
	{
		// �ȶ����������
		int a[] = {1,2,3,4,5};
		int add_num = 2;

		// �������
		auto print = [&]
		{
			for (auto s: a)
			{
				cout << s << "\t";
			}
			cout << endl;
		};
		
		print();

		// ������ۼ�
		for (auto& num : a)
		{
			// ִ��lambda���� ��ʡ�ǳ���Ĵ���
			[&]{ num += add_num;}();
		}

		// foreach
		for_each(a, a+5, [=](int &i){i += add_num;});

		print();
		
		// ֵ����, i������
		int i = 1;

		auto lambda_func = [=,&i]
		{
			cout << "lambda_func " << i++ <<  endl;
		};

		lambda_func(); // ���1
		lambda_func(); // ���2 ��Ϊi=2��ʱ
	}

	// �ֽڶ���
	if (false)
	{
		__declspec(align(1))
		struct MyStruct
		{
			int i;
			char j;
			int k;
			char m;

		};

		cout << " sizeof(MyStruct)  " << sizeof(MyStruct) << endl; // align
		cout << " offsetof(MyStruct i)  " << offsetof(MyStruct, i) << endl; // 0
		cout << " offsetof(MyStruct j)  " << offsetof(MyStruct, j) << endl; // 4
		cout << " offsetof(MyStruct k)  " << offsetof(MyStruct, k) << endl; // 8
		cout << " offsetof(MyStruct m)  " << offsetof(MyStruct, m) << endl; // 12
	}


	return;
}
