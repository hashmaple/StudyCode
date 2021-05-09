//--------------------------------------------------------------------
// 文件名:		TestC17
// 内  容:		
// 说  明:		
// 创建日期:	2021年5月7日
// 整理日期:	2021年5月7日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "C++17.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

// 自动推导返回类型
template<typename T>
auto addByType(const T& t)
{
	// 条件判断中 表达式编译为常量结果
	if constexpr(is_integral<T>::value)
	{
		return t + 1;
	}
	else
	{
		return t;
	}
}


// 强制实例化
template class vector<int>;
// 不实例化
extern template class vector<bool>;

class Base
{
public:
	int v1=0, v2=0;
	Base() { v1 = 1; };

	// 委托给无参构造，再执行
	Base(int v) :Base()
	{
		v2 = v;
	}
};

class SubClass:public Base
{
public:
	// 继承基类的构造函数
	using Base::Base;
};


// 对外接口
void TestC17::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// if中存放临时变量 条件编译为常量 构造 委托和继承
	if (0)
	{
		/* / if中存放临时变量 需要打开 C++语言标准  /std： c + + 17
		vector<int> vct = { 1,2,3,4 };
		if (const vector<int>::iterator it = find(vct.begin(), vct.end(), 2); it!= vct.end())
		{
			*it = 1;
		} */

		// 结构化绑定
		// tuple<int,double,string> [x,y,z] = make_tuple(1, 2.3, "123");
		// cout << x << y << z << endl;

		// 让判断条件编译为常量，效率更好
		cout << "addByType 1 = " << addByType(1) << endl;
		cout << "addByType 1.1 = " << addByType(1.1f) << endl;
		
		// 连续的>>
		vector<int> vctInt = { 1,2,3 };
		vector<vector<int>> vctVctInt;

		// 构造 委托和继承
		Base base(2); // 使用委托构造
		cout << "base.v1 = " << base.v1 << endl;
		cout << "base.v2 = " << base.v2 << endl;
		SubClass sub(3); // 用基类的构造函数
		cout << "sub.v1 = " << sub.v1 << endl;
		cout << "sub.v2 = " << sub.v2 << endl;
	}

	// 添加X86和X64的C++区别 [5/9/2021 zhousq]
}
