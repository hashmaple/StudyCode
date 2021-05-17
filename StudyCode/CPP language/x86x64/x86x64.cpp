//--------------------------------------------------------------------
// �ļ���:		x86x64
// ��  ��:		32λ��64λ�ı�������
// ˵  ��:		
// ��������:	2021��5��10��
// ��������:	2021��5��10��
// ������:		Maple(������)
//--------------------------------------------------------------------
#include "x86x64.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;


class Test
{
	int num;
	string name;
};

//һ������ָ��
typedef void(*pFunc)(void);
void PrintHello(void)
{
	cout << "hello world" << endl;
}

// ��ν32λ��64λ��ָ����CPU���ֳ���
// ��ʵ��Ҫ�� GPRS(General Purpose Regisers,ͨ�üĴ���)�����ݿ�ȡ�
void x86x64::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// _WIN32 �� _WIN64 ��
	if (0)
	{
		// �����64λcl���룬����_WIN64
#ifdef _WIN64
		cout << "This is _WIN64! 64bit" << endl;
#else
		cout << "This is not _WIN64! 32bit" << endl;
#endif

		// ����32λ����64λ��ֻҪ��cl����������_WIN32
#ifdef _WIN32
		cout << "_WIN32! is allways define!" << endl;
#endif

	}

	// �������͵����� �������Ͷ��ޱ仯,��Ҫ��ָ��仯
	if (0)
	{
		cout << "�����������Ͷ��ޱ仯,��Ҫ��ָ��64λ��Ϊ8" << endl;

		cout << "sizeof(char):" << sizeof(char) << endl;		// 1
		cout << "sizeof(short):" << sizeof(short) << endl;		// 2
		cout << "sizeof(int):" << sizeof(int) << endl;			// 4
		cout << "sizeof(long):" << sizeof(long) << endl;		// 4
		cout << "sizeof(long long):" << sizeof(long long) << endl;			// 8
		cout << "sizeof(unsigned int):" << sizeof(unsigned int) << endl;	// 4
		cout << "sizeof(float):" << sizeof(float) << endl;					// 4
		cout << "sizeof(double):" << sizeof(double) << endl;				// 8

		// ��Ҫ�������������:
		void* pointer;
		cout << "sizeof(pointer):" << sizeof(pointer) << endl;	// 32-4 64-8
	}

	// ����ָ�� ����32-4 64-8
	if (0)
	{
		cout << "����ָ��, 32λ��Ϊ4,64λ�϶�Ϊ8" << endl;

		int* pInt;
		void* pVoid;
		Test* pTest = new Test();
		pFunc pfunc = PrintHello;
		cout << "sizeof(pInt):" << sizeof(pInt) << endl;
		cout << "sizeof(pVoid):" << sizeof(pVoid) << endl;
		cout << "sizeof(pTest):" << sizeof(pTest) << endl;
		cout << "sizeof(pFunc):" << sizeof(pfunc) << endl;

		delete pTest;
	}

	// string��sizeof�仯.��32-28  64-40��
	if (0)
	{
		string empty("");
		string name("hehe");
		string longstr(100, 'a');

		// string�ڲ����������ַ����������Ǳ�����һ��ָ���ַ�����ͷ��ָ�롣
		cout << sizeof(empty) << endl;	// 32-28  64-40
		cout << sizeof(name) << endl;
		cout << sizeof(longstr) << endl;
		cout << sizeof(string) << endl;
	}

}
