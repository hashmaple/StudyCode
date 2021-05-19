// MyStaticLib.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>

using namespace std;

// TODO: 这是一个库函数示例
void fnMyStaticLib()
{
	cout << "This is from staticlib: " << endl;
	std::cout << __FILE__ << "  " << __FUNCTION__ << std::endl;
}

// 静态库中的累加
int AddByStaticLib(int i, int j)
{
	return i + j + 1;
}
