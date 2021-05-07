//--------------------------------------------------------------------
// �ļ���:		TestC14
// ��  ��:		
// ˵  ��:		
// ��������:	2020��10��10��
// ��������:	2020��10��10��
// ������:		Maple(������)
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

// ��������ֵ�����Ƶ�
auto func(int i)
{
	return i*10;
}

// ģ����
template<typename T> auto func_T(T t) 
{ 
	return t * 2; 
}

// ����ģ��
template<class T>
constexpr T pi = T(3.1415926535897932385L);

// ����ģ��
template<typename T, typename U>
struct A 
{
	T t;
	U u;
};
template<typename T>
using B = A<T, int>;

// ����ӿ�
void TestC14::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	if (0)
	{
		cout << "===TestC14::BeginTest===" << endl;

		// ��������ֵ�����Ƶ�
		auto re = func(100);

		auto re_t1 = func_T(3.14);

		auto re_t2 = func_T(314);

		// lambda����auto
		auto f = [](auto a) { return a; };
		cout << "lambda����auto f(1)= " << f(1) << endl;
		cout << "lambda����auto f(2.3f)= " << f(2.3f) << endl;

		// ����ģ��
		cout << "pi<int>= " << pi<int> << endl;			// 3
		cout << "pi<double>= " << pi<double> << endl;	// 3.14159

		// ����ģ��
		B<double> b;
		b.t = 10;
		b.u = 20;
		cout << b.t << endl;	// double
		cout << b.u << endl;	// int

		// [[deprecated]] auto func(int i)
		// ��������Ҫ����������������� D _CRT_SECURE_NO_DEPRECATE

		// ������������ �� �����������ָ���
		int a1 = 0b0001'0011'10'10;
		double a2 = 3.14'1234'1234'1234;
		int a3 = 12'345;
		int a4 = 12'34'5;
	}
}
