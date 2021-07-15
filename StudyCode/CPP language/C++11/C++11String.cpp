/*!
 * \file C++11String.cpp
 * \date 2019/02/22 15:41
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief string
 *
 * TODO: long description
 *
 * \note
*/
#include "C++11String.h"

#include <string>

#include <algorithm>
#include <iostream>
#include <regex>


using namespace std;

/////////////////////////////对外接口/////////////////////////////////////////////
// FunAndLambda
void NewString::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// string
	if (0)
	{
		// 内部函数测试
		string MyStr = "hello mike!";
		MyStr.erase(); // = clear();
		MyStr.append("How are you");
		MyStr.push_back('?');
		MyStr.insert(MyStr.length(), " YES!");
		MyStr.pop_back();

		cout << "c_str= " << MyStr.c_str() << endl;
		cout << "size= " << MyStr.size() << endl;
		cout << "length= " << MyStr.length() << endl;
		cout << "capacity= " << MyStr.capacity() << endl;
		cout << "max_size= " << MyStr.max_size() << endl;
		cout << "front= " << MyStr.front() << endl;
		cout << "back= " << MyStr.back() << endl;
		
		MyStr.reserve(30);
		cout << "after reserve(30) capacity= " << MyStr.capacity() << endl;
		MyStr.shrink_to_fit();
		cout << "after shrink_to_fit capacity= " << MyStr.capacity() << endl;
		MyStr.resize(10);
		cout << "after resize(10) = " << MyStr << endl;
		MyStr.replace(MyStr.begin(), MyStr.begin()+3, "What");
		cout << "after replace = " << MyStr << endl;

		if (MyStr.find("are") != string::npos)
		{
			cout << "find  'are' Inside" << endl;
		}

		// 逐个输出字符
		auto it = MyStr.cbegin();
		for (int i = 0; it != MyStr.end(); ++it, ++i)
		{
			//cout << *it;
			//cout << MyStr[i];
			cout << MyStr.at(i);
		}
		cout << endl;

		// 数值和字符串转换
		string numstr = " 1234";
		numstr = to_string(9527);
		int num = stoi(numstr);
		cout << "numstr stoi = " << num << endl;
	}

	// 正则表达式 参考 ECMA脚本文法
	if (0)
	{
		// 正则表达式查找 
		string numstr = " 1234";
		regex reg1("..23.");
		regex reg2(".*23.*");

		if (regex_match(numstr, reg1))
		{
			// .代表非换行外的单字符
			cout << "regex_match  (..23.)find " << endl;
		}

		if (regex_match(numstr, reg2))
		{
			// *匹配前面的表达式0~N次
			cout << "regex_match  (.*23.*)find " << endl;
		}
	}
}
