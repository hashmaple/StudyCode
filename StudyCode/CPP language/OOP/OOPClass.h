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

// 类声明
class complex
{
public:
	// 构造函数 + 初始化列表
	complex(double r = 0, double i = 0): re(r), im(i) {}

	// 操作符重载
	complex& operator += (const complex&);
	complex& operator -= (const complex&);

	// const描述此方法不会修改内部数据 const对象也可以调用
	double real() const { return re; }
	double imag() const { return im; }

private:
	double re, im;

	// 友函数(函数内可以访问private member)
	friend complex& __doapl(complex*, const complex&);
	friend complex& __doami(complex*, const complex&);
};

// 类定义(inline建议, 最终按编译器为准)
inline complex& __doapl(complex* ths, const complex& r)
{
	// 返回类型为 complex&, 不可返回临时对象~
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}

// 重载的+=操作符 让__doapl去实现. 
inline complex& complex::operator += (const complex& r)
{
	return __doapl(this, r);
}

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

// 不可返回complex&, 因为结果为临时对象
inline complex operator + (const complex& x, const complex& y)
{
	return complex(real(x) + real(y), imag(x) + imag(y));
}

#endif // OOPClass_h__
