//--------------------------------------------------------------------
// 文件名:		OOPClass
// 内  容:		面向对象高级编程DEMO
// 说  明:		Class with or without pointer member
// 创建日期:	2022年2月26日
// 整理日期:	2022年2月26日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
// guard 防御声明(避免多次重复包含)
#ifndef OOPClass_h__
#define OOPClass_h__

// guard 防御声明(避免多次重复包含)
// #pragma once

class complex;	// 前向声明
class OOPClass
{
public:
	OOPClass(void) {};
	~OOPClass(void) {};

	// 对外接口
	void BeginTest();
};

// 前向声明
class complex;
complex& __doapl(complex* ths, const complex& r);
complex& __doami(complex* ths, const complex& r);

// 类声明 without pionter class
class complex
{
public:
	// 构造函数 + 初值列,初始列(区别于赋值)
	complex(double r = 0, double i = 0): re(r), im(i) {}
	
	// 析构函数
	~complex() { re = 0; im = 0; }

	// 操作符重载 (return by reference)
	complex& operator += (const complex&);
	complex& operator -= (const complex&);

	// const常量成员函数 此方法不会修改内部数据 const对象也可以调用
	double real() const { return re; }
	// 在class body内直接定义,自动成为inline的候选人
	double imag() const { return im; }

private:
	double re, im;

	// 友元(函数内可以访问private member)
	friend complex& __doapl(complex*, const complex&);
	friend complex& __doami(complex*, const complex&);
};

// 在body外的类定义(inline最终按编译器为准)
inline complex& __doapl(complex* ths, const complex& r)
{
	// 因为为友元,自由取得friend的private成员
	ths->re += r.re;
	ths->im += r.im;

	// 返回类型为 complex&, 不可返回临时对象~
	return *ths;
}

// 重载的+=操作符 让__doapl去实现. 
inline complex& complex::operator += (const complex& r)
{
	return __doapl(this, r);
}

// 第一个参数会改变,第二个参数不会改变 返回引用
inline complex& __doami(complex* ths, const complex& r)
{
	// 返回类型为 complex&, 不可返回临时对象~
	ths->re -= r.re;
	ths->im -= r.im;
	return *ths;
}

// 重载的-=操作符 让__doami去实现. 
inline complex& complex::operator -= (const complex& r)
{
	return __doami(this, r);
}

// 全局函数 提供2个complex的 + 操作
inline double imag(const complex& x) { return x.imag(); }

inline double real(const complex& x){ return x.real(); }

// 不可返回complex&, 因为结果为临时对象 local object
inline complex operator + (const complex& x, const complex& y)
{
	return complex(real(x) + real(y), imag(x) + imag(y));
}

// 操作符重载, 非成员函数
inline bool operator == (const complex& x, const complex& y)
{
	return real(x) == real(y) && imag(x) == imag(y);
}


// 类声明 with pionter class
class String
{
	// Big Three 三个特殊函数
public:
	// class with pointer 必须有 copy ctor 和 op=
	String(const char* cstr = 0);
	String(const String& str); // 拷贝构造函数
	String& operator=(const String& str); // 拷贝赋值函数
	// 开启了堆内存,就必须析构时释放
	~String();
	
	char* get_c_str() const	{ return m_data; }

private:
	char* m_data;
};

// String类定义
#include <cstring>
inline String::String(const char* cstr)
{
	// 参数保护
	if (cstr)
	{
		// heap堆上开空间,复制内容
		m_data = new char[strlen(cstr) + 1];
		strcpy_s(m_data, strlen(cstr) + 1, cstr);
	}
	else
	{
		// 确保构造成功,空内容的字符串
		m_data = new char[1];
		*m_data = '\0';
	}
}

inline String::String(const String& str)
{
	m_data = new char[strlen(str.m_data) + 1];
	strcpy_s(m_data, strlen(str.m_data) + 1, str.m_data);
}

inline String& String::operator =(const String& str)
{
	// 检测自我赋值 self assignment
	if (this == &str)
	{
		return *this;
	}

	delete[] m_data;

	m_data = new char[strlen(str.m_data) + 1];
	strcpy_s(m_data, strlen(str.m_data) + 1, str.m_data);
	return *this;
}

#include <iostream>

inline String::~String()
{
	if (m_data)
	{
		delete[] m_data;
	}

	std::cout << "~String" << std::endl;
}

#endif // OOPClass_h__
