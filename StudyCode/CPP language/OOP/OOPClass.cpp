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

// 支持complex的输出(pass by reference, return by reference)
ostream& operator << (ostream& os, const complex& x)
{
	// 若不返回 os, 则无法支持  cout << c1 << c2;
	return os << '(' << real(x) << ',' << imag(x) << ')';
}

// 支持String的输出
ostream& operator << (ostream& os, const String& str)
{
	return os << str.get_c_str();
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
		cout << c1 << c2 << endl;

		cout << c1 + c2 << endl;
		cout << (c1 == c2) << endl;

		// 转换为: complex:: .operator +=(this, c2)
		cout << (c1 += c2) << endl;

		cout << (5 + c2) << endl;

		// new操作分解
		complex* p = new complex(1, 2);
		delete p;
		p = nullptr;

		// new complex 编译器转换为以下代码
		void* mem = operator new(sizeof(complex)); // 分配内存(malloc(n))
		p = static_cast<complex*>(mem);	// 类型转换
		p->complex::complex(1, 2);	// 构造函数

		cout << "complex(1, 2) *p = " << *p << endl;

		p->complex::~complex(); // 执行析构函数

		cout << "p->complex::~complex()  *p = " << *p << endl;

		operator delete(p); // 释放内存

		cout << "delete(p) danger!! *p = " << *p << endl;
	}

	// String 相关测试
	if (1)
	{
		cout << "String 相关测试  " << endl;

		cout << "String("") = " << String(0) << endl;


		String s1("s1");
		String s2("s2");

		cout << "s1 s2 = " << s1 << " " << s2<< endl;

		String s3(s2);
		cout << "s3(s2) s3=" << s3 << endl;

		s3 = s1;
		cout << "s3 = s1 s3=" << s3 << endl;

		// 不可漏写[] 影响元素的析构调用
		String* p = new String[3];
		std::cout << "new String[3]" << std::endl;
		delete[] p;
		std::cout << "delete p[] end" << std::endl;
	}
}
