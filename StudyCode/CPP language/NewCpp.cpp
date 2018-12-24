/********************************************************************
	filename: 	NewCPP
	purpose:	测试C++ 0X 最新标准
	https://zh.cppreference.com/w/cpp
	created:	2015/2/5
	updated:	2015/2/5
	author:		maple(周树青)	
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
	// 移动构造函数
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
/////////////////////////////对外接口/////////////////////////////////////////////
// NewCPP
void NewCPP::BeginTest()
{
	// 测试预定义宏
	if (false)
	{
		// c99 is __func__
		cout << "output __FUNCTION__: " << __FUNCTION__ << endl;
		cout << "output __FILE__: " << __FILE__ << endl; 
		cout << "output __DATE__: " << __DATE__ << endl;
		cout << "output __cplusplus: " << __cplusplus << endl;

		// 输出所有参数
		PR("printf: %d,%s\n",1,"aaa");
	}

	// long long
	if (false)
	{
		// 64位的类型
		long long lint = 123456789987654321LL;
		lint = LLONG_MAX;
		cout << "long long num is: " << lint << endl;
		cout << "long long sizeof is: " << sizeof(lint) << endl;
	}

	// 移动函数
	if (false)
	{
		// 通过移动构造
		temp s1 = ReturnStr();
		temp s2 = ReturnStr();

		cout << s1.str<< endl;
		cout << s2.str<< endl;
	}

	// 集合初始化
	if (false)
	{
		int i = 3 + 4;
		int a[] = {1,2,3,4,5};
		vector<int> vct = {1,2,3,4,5};

		// 是否POD类型 
		// POD类型可以安全的在C 和 C++之间相互操作
		// POD类型可以直接内存操作memset memcpy
		cout << is_pod<temp>::value << endl;
	}

	// lambda函数
	if (false)
	{
		// 先定义变量数组
		int a[] = {1,2,3,4,5};
		int add_num = 2;

		// 输出函数
		auto print = [&]
		{
			for (auto s: a)
			{
				cout << s << "\t";
			}
			cout << endl;
		};
		
		print();

		// 方便的累加
		for (auto& num : a)
		{
			// 执行lambda函数 节省非常多的代码
			[&]{ num += add_num;}();
		}

		// foreach
		for_each(a, a+5, [=](int &i){i += add_num;});

		print();
		
		// 值传递, i用引用
		int i = 1;

		auto lambda_func = [=,&i]
		{
			cout << "lambda_func " << i++ <<  endl;
		};

		lambda_func(); // 输出1
		lambda_func(); // 输出2 因为i=2这时
	}

	// 字节对齐
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
