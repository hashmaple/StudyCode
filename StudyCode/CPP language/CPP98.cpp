//--------------------------------------------------------------------
// 文件名:		C++98
// 内  容:		学习C++98的标准函数功能等
// 说  明:		https://zh.cppreference.com/w/cpp
// 创建日期:	2017年5月2日
// 整理日期:	2017年5月2日
// 创建人:		Maple(周树青)
// 版权所有:	苏州蜗牛数字科技股份有限公司
//--------------------------------------------------------------------
#include "CPP98.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h> 
#include <set>

// 为了通过编译器VS2015
#pragma warning(disable:4996)

#include<windows.h>
#include<winbase.h>

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <random>

using namespace std;


// 返回带引号的字符
#define to_string( s ) #s

// 连接前后内容
#define abc 100

#define concatenate( a, b ) a##b

// 返回绝对值
#define absolute_value( x ) ( ((x) < 0) ? -(x) : (x) )

// 计算长度
#define query_sizeof( x ) #x<< " size is " << sizeof(x) << endl

// 定义错误输出
#if !defined(__cplusplus)
#error C++ compiler required.

#endif


CPP98::CPP98(void)
{
}

CPP98::~CPP98(void)
{
}

unsigned long ulrand(void) {
	return (
		(((unsigned long)rand() << 24) & 0xFF000000ul)
		| (((unsigned long)rand() << 12) & 0x00FFF000ul)
		| (((unsigned long)rand()) & 0x00000FFFul));
}



void exit_function(void)

{
	printf("Exit function  called\n");
}

/////////////////////////////对外接口/////////////////////////////////////////////
void CPP98::BeginTest()
{
	// 基础语法 宏 预定义变量  #pragma 
	if (1)
	{
		cout << to_string(HEELO MAPLE!) << endl;


		int xy = 10;
		cout << "print the abc value = " << abc << endl; 
		cout << "print the xy value = " << concatenate(x, y) << endl; // print the xy value = 10;

		cout << "absolute_value is " << absolute_value(-10) << endl;

		cout << " __LINE__ " << __LINE__ << endl <<
			"  __FILE__ " << __FILE__ << endl <<
			"  __DATE__ " << __DATE__ << endl <<
			"  __TIME__ " << __TIME__ << endl;

		cout << query_sizeof(bool) <<
			query_sizeof(char) <<
			query_sizeof(unsigned char) <<
			query_sizeof(signed char) <<
			query_sizeof(int) <<
			query_sizeof(unsigned int) <<
			query_sizeof(signed int) <<
			query_sizeof(short int) <<
			query_sizeof(unsigned short int) <<
			query_sizeof(signed short int) <<
			query_sizeof(long int) <<
			query_sizeof(unsigned long int) <<
			query_sizeof(signed long int) <<
			query_sizeof(float) <<
			query_sizeof(double) <<
			query_sizeof(long double) <<
			query_sizeof(wchar_t);
	}

	// 标准 C I/O 
	if (false)
	{
		FILE* pFile = fopen("cpp98.ini", "w+");
		if (pFile == NULL)
		{
			return;
		}

		if (fputs("this is cpp98.ini", pFile) == EOF)
		{
			fclose(pFile);
			return;
		}

		// 读取前指针移动到文件头
		rewind(pFile);

		// 读取
		char c = fgetc(pFile);
		while (c != EOF)
		{

			cout << c;
			c = fgetc(pFile);
		}

		fclose(pFile);
	}

	// 标准c字符和字符串
	if (false)
	{
		cout << atof("42.01is_the_answer") << endl;
		cout << atoi("42.91is_the_answer") << endl; // 不四舍五入

		char buff[32] = "China have the";
		cout << "字符串连接 strcat " << strcat(buff, " the Great") << endl; //catenate string

		char* p = strstr(buff, " the Great"); // 找不到返回空指针
		if (p)
		{
			cout << "字符串查找 strstr(buff, \" the Great\") result is " << p << endl; //find the string pos 
		}

		// 小于小于0 等于为0 大于大于0
		cout << "字符串比较 strcmp " << strcmp("zsq", "zsqkyo") << endl;

		cout << "字符小写化 strlwr " << _strlwr(buff) << endl;	
	} 

	// Standard C Math
	if (false)
	{
		cout << "abs -1 is " << abs(-1) << endl;
		cout << "fabs -1.2 is " << fabs(-1.2) << endl;
		cout << "acos -0.5 is " << acos(-0.5) << endl;
		cout << "asin -0.5 is " << asin(-0.5) << endl;
		cout << "sin -0.5 is " << sin(-0.5) << endl;


		cout << "返回不小于num 的最小整数 ceil 8.5 is " << ceil(8.5) << endl;
		cout << "返回不大于num 的最小整数 floor 8.5 is " << floor(8.5) << endl;

		cout << "求模 fmod 10, 3 is " << fmod(10, 3) << endl;
		cout << "求乘幂 pow 8, 2 is " << pow(8, 2) << endl;
		cout << "求平方根 sqrt 9 is " << sqrt(9) << endl;

		// 返回参数numerator / denominator的商和余数
		div_t temp;
		temp = div(10, 3);
		printf("%d divided by %d yields %d with a remainder of %d\n", 10, 3, temp.quot, temp.rem);
	}

	// 标准c时间与日期函数
	if (false)
	{
		time_t now_time = time(NULL);

		//  localtime函数介绍
		// 功能：把从1970 - 1 - 1零点零分(程序中是从1900年开始算的)
		// 到当前时间系统所偏移的秒数时间转换为日历时间。
		// 说明：此函数获得的tm结构体的时间，已经进行过时区转化，成为了本地时间。
		tm* t1 = localtime(&now_time);
		cout << "localtime(本地时间) is " << asctime(t1) << endl;

		// gmtime是把日期和时间转换为格林威治(GMT)时间的函数
		// localtime函数获得的tm结构体的时间，是已经进行过时区转化为本地时间。
		tm* t2 = gmtime(&now_time);
		cout << "gmtime(格林威治GMT) is " << asctime(t2) << endl;


		// 获取当地的当前系统日期和时间。
		SYSTEMTIME st1 = { 0 };
		GetLocalTime(&st1);

		// “协同世界时间”（即UTC，也叫做GMT）格式
		SYSTEMTIME st2 = { 0 };
		GetSystemTime(&st2);
	}

	// 标准c内存函数
	if (false)
	{
		// 错误,导致指针后面的内存中原有数据内容全部被覆盖
		double* p1 = (double *)malloc(1);
		*p1 = 1.1;

		// 按大小分配内存 不过对内存没有初始化 内容随机
		int* p2 = (int *)malloc(sizeof(int));
		*p2 = 2;

		// 分配 按 1 X 4分配
		int* p3 = (int *)calloc(1, 4);
		*p3 = 3;

		free(p3);
		p3 = NULL;

		free(p2);
		p2 = NULL;

		free(p1); // 因为使用越界,导致释放时候assert
		p1 = NULL;
	}

	// 其他标准c函数
	if (0)
	{
		// main执行结束后调用的函数 (_exit，_Exit 都不会调用终止程序
		atexit(exit_function);

		// 随机数
		srand(time(NULL));    
		for (int i = 0; i < 10000; i++)
		{
			//printf("Random number %d: %d\n", i, rand()%100000);
		}

		// use current time as seed for random generator  #define RAND_MAX 0x7fff
		std::srand(std::time(0)); 
		int uniform_random_variable = std::rand();
		std::cout << "Uniform random value on [0 " << RAND_MAX << "]: "
			<< uniform_random_variable << '\n';

		// 20W次产出的随机数,数量大约在86000个左右.
		srand(time(NULL));
		set<int> setNum;
		for (int i = 0; i < 200000; i++) 
		{
			int random_num = ulrand() % 100000;
			setNum.insert(random_num);
		}

		cout << "use ulrand 20W count gen " << setNum.size() << endl;

		// C++ 11的随机数库
		set<int> setNum2;
		std::random_device rd;
		std::mt19937 mt(rd());
		for (int n = 0; n < 200000; n++)
		{
			setNum2.insert(mt() % 100000);
		}
		cout << "use C++ 11 mt19937 20W count gen " << setNum2.size() << endl;

		assert(1);

		//exit(0);

		// abort the current program by raising SIGABRT
		//abort();
	}

	return;
}
