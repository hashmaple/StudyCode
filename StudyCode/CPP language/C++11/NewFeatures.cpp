/*!
 * \file NewFeatures.cpp
 * \date 2018/12/24 14:05
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief learn c++11 NewFeatures 
 *
 * TODO: long description
 *
 * \note
*/
#include "NewFeatures.h"

#include <vector>
#include <string>

#include <iostream>

using namespace std;

NewFeatures::NewFeatures(void)
{
}

NewFeatures::~NewFeatures(void)
{
}


/////////////////////////////对外接口/////////////////////////////////////////////
// NewFeatures
void NewFeatures::BeginTest()
{
	if (false)
	{
		// nullptr 基础类型 不会转为整形,会转为各种指针类型. 
		int *p = nullptr;

		// auto 类型自动推导. 原先意义为某变量是局部的.
		auto i = 20;

		// 一致性的初始化 都可以使用大括号
		int j{}; // j = 0 会初始化
				 // int k; 未初始化编译不通过
		int values[]{ 1,2,3 };
		vector<int> v = { 2,3,4,5,6 };
		vector<string> vstr = { "zsq", "kyo" };

		// range-based for循环
		for (auto it : v) {} // 会赋值给it,产生一份副本
		for (auto& it : v) { ++it; } // it是引用,可以修改
		for (const auto& it : v) {} // it是常量引用,不可修改

		// std::move() 搬迁语义 适用于变量搬迁后不再使用的情形.
		int i_move = 1;
		vector<int> v_int1{ 1,2,3,4 };
		vector<int> v_int2(4);
		v_int2 = move(v_int1); // 直接移动内容过来,减少了一次复制消耗. 
		v_int2.size(); // 4
		v_int1.size(); // 0 处于未指定,但有效的状态 move后不用此容器,用法正确!

					   // 字符串字面常量
		cout << R"(/N)" << endl;
	}
	
	if (false)
	{
		// lambda []=获取上下文变量   ()输入参数   ->返回值
		int lambda_i = 8;
		int lambda_j = 8;
		auto l = [lambda_i, &lambda_j](int i, const string& s) -> int
		{
			cout << "lambda functon call! input args i/s = " << i << s << endl;
			cout << "lambda_i = " << lambda_i << endl;
			lambda_j++;
			cout << "lambda_j = " << lambda_j << endl;
			return 9527;
		};
		// 先调用l函数,在输出返回值
		cout << "lambda call return = " << l(1, "maple") << endl;
		cout << "lambda_j = " << lambda_j << endl;	// 在函数传递引用后已经被修改
	}

	return;
}
