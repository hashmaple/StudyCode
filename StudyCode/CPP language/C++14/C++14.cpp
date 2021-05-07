//--------------------------------------------------------------------
// 文件名:		TestC14
// 内  容:		
// 说  明:		
// 创建日期:	2020年10月10日
// 整理日期:	2020年10月10日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "C++14.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

TestC14::TestC14()
{
}

TestC14::~TestC14()
{
}

// 函数返回值类型推导
auto func(int i)
{
	return i*10;
}

// 模板中
template<typename T> auto func_T(T t) 
{ 
	return t * 2; 
}

// 变量模板
template<class T>
constexpr T pi = T(3.1415926535897932385L);

// 别名模板
template<typename T, typename U>
struct A 
{
	T t;
	U u;
};
template<typename T>
using B = A<T, int>;

// 对外接口
void TestC14::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	if (0)
	{
		cout << "===TestC14::BeginTest===" << endl;

		// 函数返回值类型推导
		auto re = func(100);

		auto re_t1 = func_T(3.14);

		auto re_t2 = func_T(314);

		// lambda参数auto
		auto f = [](auto a) { return a; };
		cout << "lambda参数auto f(1)= " << f(1) << endl;
		cout << "lambda参数auto f(2.3f)= " << f(2.3f) << endl;

		// 变量模板
		cout << "pi<int>= " << pi<int> << endl;			// 3
		cout << "pi<double>= " << pi<double> << endl;	// 3.14159

		// 别名模板
		B<double> b;
		b.t = 10;
		b.u = 20;
		cout << b.t << endl;	// double
		cout << b.u << endl;	// int

		// [[deprecated]] auto func(int i)
		// 开启后，需要在链接中命令行添加 D _CRT_SECURE_NO_DEPRECATE

		// 二进制字面量 与 整形字面量分隔符
		int a1 = 0b0001'0011'10'10;
		double a2 = 3.14'1234'1234'1234;
		int a3 = 12'345;
		int a4 = 12'34'5;
	}
}
