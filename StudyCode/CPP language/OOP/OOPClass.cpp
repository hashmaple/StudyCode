//--------------------------------------------------------------------
// 文件名:		OOPClass
// 内  容:		面向对象高级编程DEMO
// 说  明:		Class with or without pointer member
// 创建日期:	2022年2月26日
// 整理日期:	2022年2月26日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------#include "C++17.h"
#include "OOPClass.h"	// 优先当前目录

#include <iostream>		// 优先系统目录
using namespace std;

// 支持complex的输出
ostream& operator << (ostream& os, const complex& x)
{
	return os << '(' << real(x) << ',' << imag(x) << ')';
}

// 对外接口
void OOPClass::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// complex 相关测试
	if (1)
	{
		cout << "complex 相关测试  " << endl;

		complex c1(2, 1);
		complex c2(4, 0);

		cout << c1 << endl;
		cout << c2 << endl;

		cout << c1 + c2 << endl;

		cout << (c1 += c2) << endl;

		cout << (5 + c2) << endl;
	}
}
