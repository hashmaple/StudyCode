//--------------------------------------------------------------------
// 文件名:		TestCLib
// 内  容:		C语言库
// 说  明:		https://zh.cppreference.com/w/cpp
// 创建日期:	2011年8月18日
// 创建人:		Maple(周树青)
// 版权所有:	
//--------------------------------------------------------------------
#include <stdio.h>	// 输入输出库
#include <math.h>	// 数学函数库
#include <ctype.h>  // 字符函数库
#include <string.h>	// 字符串函数库
#include <io.h>		// 输入输出函数库
#include <conio.h>	// 控制台IO函数库
#include <assert.h>	// DEBUG库
#include <signal.h> // 信号库
#include <time.h>   // 时间库
#include <stdlib.h> // 标准工具库

#pragma warning(disable:4996)

#include <string>
#include <iostream>
using namespace std;

// 测试函数
bool TestCLib()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 定义
	int myint;
	float myfloat;
	double mydouble;

	// 读取文件
	FILE *pFile;
	char mystr[256] = {};

	// stdio库
	if (false)
	{
		// 字符输入
		sprintf_s(mystr, "zsqsqsq%c", 'f');

		// 写入文件
		fopen_s(&pFile, "test.txt", "wb");
		putc('s', pFile);
		putwc(65, pFile);

		// 文件指针重新定位到开头
		rewind(pFile); 

		fclose(pFile);

		// 读取文件
		fopen_s(&pFile, "test.txt", "rb");
		char ch = getc(pFile);
		char num = getc(pFile);
		fclose(pFile);

		// 删除文件
		remove("test.txt");

		//char ch = getc(stdin); // 获取字符
		//char ch = getchar();	 // 获取字符
		//putchar('s');			 // 输出字符
		//puts("this is maple's test");/ 输出字符串
		gets_s(mystr);	// 获取输入字符串
		puts(mystr);	// 输出字符串到控制台

		perror("输出错误信息!!!");
	}

	// math库
	if (false)
	{
		// 求平方根
		mydouble = sqrt(16.0f);

		// 直角三角形斜边
		mydouble = hypot(3, 4);

		// 汉语拼音
		//string py = pyfc("汉语拼音");

		// 取余
		myint = fmod(13.5, 2);    // 1
		mydouble = fmod(13.5, 2); // 1.5

		// 取整
		myint = ceil(1.7f);  // 2
		myint = floor(1.7f); // 1


		myint = asin(0.5f);
		myint = acos(0.5f);

		// 整数绝对值
		myint = abs(-11);

		// 浮点绝对值
		myfloat = fabs(-1.22f);
	}
	
	// 字符函数库
	if (false)
	{
		// 数字或字符
		int is_char_num = isalnum('2');

		// 英文字母
		int is_english = isalpha('s');
	}

	// 字符串函数库
	if (false)
	{
		// 字符长度
		myint = strlen("how long it is?");

		// 字符查找
		myint = strcspn("this is maple", "maple");

		// 相等为0 大于>0 小于<0
		myint = strcmp("this", "this");

		// 相等为0 大于>0 小于<0 不区分大小写
		myint = _stricmp("this", "tHis");

		// 字符追加
		strcat(mystr, "this is");

		// 字符串COPY
		strcpy(mystr, "asdasd");
	}
	
	// 输入输出函数库
	if (false)
	{
		// 打开 关闭 建立文件
		myint = _open("test.txt", 1);
		myint = _creat("test.txt", 2);
	}

	// 控制台IO库
	if (false)
	{
		// 输出
		_cputs("asdasd");

		// 无回显获取字符
		char putch = _getch();
	}

	// DEBUG库
	if (false)
	{
		// 断言
		assert(1);
	}
	
	// 内存库 mem.h
	if (false)
	{
		// 内存设置
		char chA[128];
		memset(chA, 's', 128);

		// 内存赋值
		char chB[128] = {0};
		memcpy(chA, chB, 128);
	}
	
	// 信号函数库
	if (false)
	{
		// 等待和发送
		signal(1, NULL);
		raise(SIGABRT_COMPAT);
	}

	// 时间库
	if (false)
	{
		// 取时间和现实
		time_t now_time = time(NULL);
		string str = ctime(&now_time);

		// 取时间日期
		tm* t_time = localtime(&now_time);
		str = asctime(t_time);
	}

	// 标准工具库
	if (false)
	{
		// 执行DOS命令
		system("dir");

		// 整数除 商和余
		div_t my_div;
		my_div = div(10,3);

		// 转换
		myint = atoi("111.65");			// 字符串转为int
		long mylong = atoi("47523658");	// 字符串转为long
		_itoa(111, mystr, 10);			// 数字转字符串

		// 异常终止
		abort();

		// 终止程序
		exit(0);

		// 初始化随机种子
		time_t t;
		srand((unsigned)time(&t));

		// 去随即数
		for (int i = 0; i < 100; i ++)
		{
			printf("%d\t", rand()%100);
		}

		// 分配主存储器内存
		char* ch_str = NULL;
		//ch_str = (char*)calloc(128, sizeof(char));  // 分配主存储器内存
		ch_str = (char*)malloc(128);
		printf("point address: %p\n", ch_str);
		ch_str = (char*)realloc(ch_str, 24);
		printf("point address: %p\n", ch_str);
		strcpy(ch_str, "this is my str!!");
		free(ch_str);
	}

	return true;
}

// 链接静态lib库 或者在 链接 输入中添加(测试需要,lib工程 生成后时间:copy操作)
// #pragma comment(lib,"MyStaticLib.lib") 
// 
// 包含静态库中的函数声明和类声明
#include "..\MyStaticLib\MyStaticLib.h"
#include "..\MyStaticLib\MyLibClass.h"

// 测试静态库
void TestMyStaticLib()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 测试静态库
	if (0)
	{
		// 调用静态库函数
		cout << "call MyStaticLib.lib fnMyStaticLib:" << endl;

		fnMyStaticLib();

		cout << "call MyStaticLib.lib AddByStaticLib = " << AddByStaticLib(1, 2) << endl;

		// 本类中再定义MyLibClass 会报错
		// 其他处同时包含,优先link到谁用谁.只有一份MyLibClass.
		// 若无别人用,会用lib中的定义
		MyLibClass myclass;
		cout << "call MyStaticLib.lib MyStaticLibClass GetNumber() = " 
			<< myclass.GetNumber() << endl;

		// 若调用,则报错	LNK1169	找到一个或多个多重定义的符号
		// myclass.GetNumber2();
	}
}