//--------------------------------------------------------------------
// 文件名:		x86x64
// 内  容:		32位和64位的编码区别
// 说  明:		
// 创建日期:	2021年5月10日
// 整理日期:	2021年5月10日
// 创建人:		Maple(周树青)
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

//一个函数指针
typedef void(*pFunc)(void);
void PrintHello(void)
{
	cout << "hello world" << endl;
}

// 所谓32位和64位，指的是CPU的字长，
// 其实主要是 GPRS(General Purpose Regisers,通用寄存器)的数据宽度。
void x86x64::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// _WIN32 和 _WIN64 宏
	if (0)
	{
		// 如果是64位cl编译，则有_WIN64
#ifdef _WIN64
		cout << "This is _WIN64! 64bit" << endl;
#else
		cout << "This is not _WIN64! 32bit" << endl;
#endif

		// 无论32位还是64位，只要是cl编译器就有_WIN32
#ifdef _WIN32
		cout << "_WIN32! is allways define!" << endl;
#endif

	}

	// 数据类型的区别 数据类型都无变化,主要是指针变化
	if (0)
	{
		cout << "分析数据类型都无变化,主要是指针64位上为8" << endl;

		cout << "sizeof(char):" << sizeof(char) << endl;		// 1
		cout << "sizeof(short):" << sizeof(short) << endl;		// 2
		cout << "sizeof(int):" << sizeof(int) << endl;			// 4
		cout << "sizeof(long):" << sizeof(long) << endl;		// 4
		cout << "sizeof(long long):" << sizeof(long long) << endl;			// 8
		cout << "sizeof(unsigned int):" << sizeof(unsigned int) << endl;	// 4
		cout << "sizeof(float):" << sizeof(float) << endl;					// 4
		cout << "sizeof(double):" << sizeof(double) << endl;				// 8

		// 主要就是这里的区别:
		void* pointer;
		cout << "sizeof(pointer):" << sizeof(pointer) << endl;	// 32-4 64-8
	}

	// 分析指针 都是32-4 64-8
	if (0)
	{
		cout << "分析指针, 32位都为4,64位上都为8" << endl;

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

	// string的sizeof变化.在32-28  64-40。
	if (0)
	{
		string empty("");
		string name("hehe");
		string longstr(100, 'a');

		// string内部并不保存字符串本身，而是保存了一个指向字符串开头的指针。
		cout << sizeof(empty) << endl;	// 32-28  64-40
		cout << sizeof(name) << endl;
		cout << sizeof(longstr) << endl;
		cout << sizeof(string) << endl;
	}

}
