/********************************************************************
	filename: 	CodeSafe
	purpose:	C C++ 安全编码
	created:	2014/10/21
	updated:	2014/10/21
	author:		maple(周树青)	
*********************************************************************/
#include <float.h>
#include <math.h>
#include <time.h>
#include <windows.h>

// 整数范围定义
#include "limits.h"

#include <stdarg.h>

#include <iostream>
#include <fstream>

#include <map>
#include <string>
using namespace std;

/// \brief  获得64位的当前时间,精确到ms，注意获取到的是UTC时间
__time64_t util_get_time_64()
{
	SYSTEMTIME stm;
	FILETIME ftm;
	::GetSystemTime(&stm);
	::SystemTimeToFileTime(&stm, &ftm);

	__time64_t now = ftm.dwHighDateTime;
	now = ((now << 32) | ftm.dwLowDateTime) / 10000;

	return now;
}


// 变参函数 读取和获取!!
bool test_args(int begin, ...)
{
	va_list arglist;

	va_start(arglist, begin);

	char* arg1 = va_arg(arglist, char*);
	int arg2   = va_arg(arglist, int);
	char* arg3 = va_arg(arglist, char*);
	int arg4   = va_arg(arglist, int);

	va_end(arglist);

	return false;
}

struct TagTest
{
	int nNum;
	char p;

	TagTest()
	{
		nNum =1;
		p = 0;
	}
	~TagTest()
	{
		p = 1;
	}
};

struct TagTestEx
{
	int nNum;
	char p;

	~TagTestEx()
	{
		p = 1;
	}
};


TagTest GetStructA()
{
	TagTest tag;
	tag.nNum = 9527;
	return tag;
}

TagTest& GetStructB()
{
	TagTest tag;
	tag.nNum = 9528;
	return tag;
}

const TagTest& GetStructC()
{
	TagTest tag;
	tag.nNum = 9529;
	return tag;
}

const TagTest& GetStructD()
{
	TagTest tag;
	tag.nNum = 9530;
	return tag;
}

int getInt()
{
	int i = 1234;
	return i;
}

// 定义指针类型
typedef int* intpoint;

// 组织字符串
inline void Port_SafeSprintf(char* buf, size_t byte_size, const char* info, ...)
{
	va_list args;

	va_start(args, info);

	_vsnprintf(buf, byte_size - 1, info, args);

	buf[byte_size - 1] = 0;
}

// 字符串查找
int FindSubStr(char* main_str, char* sign_str)
{
	// safe check
	if (main_str == NULL || sign_str == NULL || 
		strlen(sign_str) <= 0 || strlen(sign_str) <= 0 ||
		std::strlen(sign_str) >= strlen(main_str))
	{
		return -1;
	}

	// loop find
	int sing_length = strlen(sign_str);
	char* main_p = main_str;
	char* sign_p = sign_str;
	int inc_index = 0;
	for (; *main_p != NULL; ++main_p)
	{
		// seek 2point find
		char a = *main_p;
		char b = *sign_p;
		if (a == b)
		{
			inc_index++;

			if (inc_index == sing_length)
			{
				return main_p - main_str;
			}
			else
			{
				++sign_p;
				continue;
			}
		}
		else
		{
			sign_p = sign_str;
		}
	}

	return -1;
}

struct MyStruct
{
	string name;
	string sex;
	string age;

	MyStruct() : 
		name(""),
		sex(""),
		age(0) // 必定崩溃
	{}
};

// 飞舟战活动时间
struct ShipBattleTimeData
{
	ShipBattleTimeData()
		: nDay(0),
		nSignUpStart(0),
		nAdjustStart(0),
		nApplyStart(0),
		nMatchStart(0),
		nGameStart(0),
		nGameOver(0)
	{

	}
	int			nDay;					// 周几
	int			nSignUpStart;			// 登记开始
	int			nAdjustStart;			// 调配开始
	int			nApplyStart;			// 报名开始
	int			nMatchStart;			// 匹配开始
	int			nGameStart;				// 战场开始
	int			nGameOver;				// 战场结束
};

// 血条名字颜色
enum HideBarNameColor:unsigned int
{
	NAME_COLOR_WHITE = 0xffffffff, // 白色
	NAME_COLOR_RED = 0xfffa646e, // 红色
	NAME_COLOR_YELLOW = 0xffe9e9b1, // 黄色
	NAME_COLOR_GREEN = 0xff73e8d8, // 绿色
};


// 测试函数
bool SafeTest()
{

	int* p = NULL;
	free(p);



	if (false)
	{
		// string赋值0 崩溃
		// string name = 0;

		// 字符指针和'0'比较
		const char* szTargetConfigId = "";
		int i = strlen(szTargetConfigId);
		if (NULL == szTargetConfigId || '\0' == szTargetConfigId[0])
		{
			cout << "szTargetConfigId[0]是首字符" << endl;
		}
	}
	


	// 浮点数和整形计算
	if (false)
	{
		__time64_t begin = GetTickCount64();

		for (int i = 2; i < 100000000; i++)
		{
			double x = (i+i+1.22f) / 1.025f;
		}

		std::cout << "浮点数消耗: " << GetTickCount64() - begin << endl;

		begin = GetTickCount64();

		for (int i = 2; i < 100000000; i++)
		{
			int x = (i + i + 3) / i;
		}

		std::cout << "整形消耗: " << GetTickCount64() - begin << endl;
	}

	// 迭代器性能 ++it 性能减少一半
	if (false)
	{
		map<string, MyStruct> mapTest;
		MyStruct ms;
		ms.name = "maple";
		ms.sex = "male";
		ms.age = "100";
		char buff[32];

		for (int i = 0; i < 1000000; i++)
		{
			sprintf_s(buff, "id=%d", i);
			mapTest.insert(make_pair(buff, ms));
		}

		// 测试迭代器获取
		__time64_t begin = GetTickCount64();

		map<string, MyStruct>::iterator it = mapTest.begin();
		for (int i = 0; it != mapTest.end(); ++it)
		{
			i++;
		}

		std::cout << "++it 消耗: " << GetTickCount64() - begin << endl;

		begin = GetTickCount64();

		it = mapTest.begin();
		for (int i = 0; it != mapTest.end(); it++)
		{
			i++;
		}

		std::cout << "it++ 消耗: " << GetTickCount64() - begin << endl;
	}

	// 字符串性能
	if (false)
	{
		__time64_t begin = GetTickCount64();

		string name;
		for (int i = 0; i < 1000000; i++)
		{
			name = "kyooooo";
		}

		__time64_t end = GetTickCount64();

		cout << "循环外定义string的性能消耗: " << end - begin << endl;

		//////////////////////////////////////////////////////////////////////////
		begin = GetTickCount64();

		for (int i = 0; i < 1000000; i++)
		{
			string name = "kyooooo";
		}

		end = GetTickCount64();

		cout << "循环内定义string的性能消耗: " << end - begin << endl;
	}

	// strstr
	if (false)
	{
		int i1 = FindSubStr("zsqkyozsqkyo", "sq");
		int i2 = FindSubStr("zsqkyozsqkyo", "f");
	}

	// 字符串安全

	if (false)
	{
		const char* pStr = "abcdefghijklmn";

		char ch[10],*p = NULL;
		char *q = NULL;

		strncpy(ch, pStr, 10);


		p = strrchr(ch,'e');

		q = strrchr(ch,'h');

		int i1 = strlen(ch);
		int i2 = strlen(p);
		int i3 = strlen(q);
		int i4 = strlen(pStr);


		string temp1 = p;
		string temp2 = q;

		string abc = temp1 + temp2;


	}

	// 浮点数丢失问题
	if (false)
	{
		float f1 = 12345129.999f;
		float f2 = 12345129.99f;
		float subf1f2 = f1 - f2;

		double df1 = 12345.12999f;
		double df2 = 12345.1299f;
		double subdf1df2 = df1 - df2;

		double d1 = 12345.12999;
		double d2 = 12345.1299;
		double subd1d2 = d1 - d2;

		bool b3 = (f1 < (f2 + 0.00001f)) && (f1 > (f2 - 0.00001f));
		bool b32 = (f1 < (f2 + FLT_EPSILON)) && (f1 > (f2 - FLT_EPSILON));

		double f2p = f2 + 0.00001f;
		double f2s = f2 - 0.00001f;

		bool b4 = fabs(f1 - f2) < FLT_EPSILON;

		cout << f1 << endl << f2 ;

		bool b5 = memcmp(&f1, &f2, sizeof(f2)) == 0;

		// 数值安全
		f1 = f1 - 1.0f;
		f1 = f1 - 10.0f;
		f1 = f1 - 100.0f;

		f2 = f2 - 1.0f;
		f2 = f2 - 10.0f;
		f2 = f2 - 100.0f;
	}
	
	// 类型定义
	if (false)
	{
		// AB都是指针
		intpoint A, B;

		// a是指针 b是整形
		int* a, b;
	}

	// 国际化
	if (false)
	{
		locale loc0;
		locale loc1 = locale();
		locale loc2("");
		locale loc3("C");
	}

	// 测试返回
	if (false)
	{
		TagTest& tagA = GetStructA();

		// BCD会出现很奇异的数据 因为指向栈上地址.
		TagTest& tagB = GetStructB();
		const TagTest& tagC = GetStructC();
		const TagTest& tagD = GetStructD();
		// 到这里 BCD都指向为D.

		// 这句会导致BCD数据异常
		int temp_i = getInt();

		tagA.nNum++;
		tagB.nNum++;
	}

	// 优先级  .和[] > *
	if (false)
	{
		TagTest* p = new TagTest();
		int i = (*p).nNum++;	// i为nNum数值 先用后加
		int j = ++(*p).nNum;	// j为nNum+1数值 先加后用
	}

	// [2011/9/2 Maple(周树青)]
	// [needfix 测试字符串安全]
	if (false)
	{
		// 输入BUG
		char ch[3];
		cin.width(3+1); // 这句很重要:保护输入
		cin>>ch;
		cout << ch;
		puts(ch);
		int str_lengh = strlen(ch);

		// 空结尾
		char a[16];
		strcpy(a, "1234567890123456");
		printf("a = %s", a);\

		// 直接数组越界 
		a[16] = 'a';
	}

	// gets
	char buff[12];
	if (false)
	{
		// 导致崩溃
		// gets(buff);		

		// 安全替代(截断)
		if (fgets(buff, 12, stdin) == NULL)
		{
			abort();
		}

		// 安全替代(位数错误 报告)
		if (gets_s(buff, 12) == NULL)
		{
			abort();
		}
	}
	
	// memcpy
	if (false)
	{
		char buff1[2];
		string str = "abcdef";

		// 全部复制(有BUG)
		memcpy(buff1, str.c_str(), 13);

		// 无符号的地方 负数变很大
		int len = atoi("-2");
		memcpy(buff1, "123456789", len);

		// 按数量复制(还是有BUG)
		memcpy_s(buff1, 3, str.c_str(), 3);
	}

	#define SPRINTF_S(buf, str, ...) sprintf_s(buf, sizeof(buf), str, __VA_ARGS__)
	
	// strcpy
	// strcat
	if (false)
	{
		try
		{
			char a[3];
			strncpy_s(a, 8, "scsidesk", 8);

			// 不安全 超出崩溃
			sprintf_s(a, 2, "a");

			// 堆损坏
			strcpy(a, "abcde"); // 复制
			strcat(a, "ABCDE"); // 追加

			// 有错误报告 检查字符结束符
			strcpy_s(a, 2, "abcde");

			// 有错误报告 检查字符结束符
			strcat_s(a, 4, "AB");

			// 安全
			strncpy(a, "abcde", 4);
			a[4] = '\0';

			// 安全
			strncat(a, "abcde", 4);
			a[4] = '\0';

			strncpy_s(a, 2 + 1, "ab", 2); // DES的长度 必须为 复制的长度 + 1 放入结束符.
			// 安全 自动加结尾 
			strncpy_s(a, "abcde", 5-1);

			// 安全 自动加结尾
			strncat_s(a, "abcde", 5-1);
		}
		catch (...)
		{
			int NeverComeHere = 0;
			return false;
		}
		
	}

	// stllen
	if (false)
	{
		char a[2];
		strcpy(a, "abcde"); 
		a[5] = 's';

		// 无结束符号 错误结果
		int str_count = strlen(a);
		str_count = strnlen(a, 10);
		str_count = strnlen_s(a, 10);
	}

	// 安全输入
	if (false)
	{
		// STL库
		string str;
		cin >> str;

		// 有点区别
		const char* pstr1 = str.data();
		const char* pstr2 = str.c_str();
	}


	// 记得注意
	if (false)
	{
		// 字符比较
		const char* pStr = "";
		if (pStr == "")
		{
			int NeverComingHere = 0;
			NeverComingHere++;
		}

		// 字符比较
		const char* pStr2 = "zsq";
		if (pStr2 == "zsq")
		{
			int NeverComingHere = 0;
			NeverComingHere++;
		}

		// 变参函数调用
		test_args(1, "zsq", 3, "maple", 5, 6);

		// 输出格式
		for (int i = 0 ; i < 100 ; i ++)
		{
			// 转换提示符: 
			// d/i=带符号十进制
			// f/F=浮点数double
			// s=字符数组的指针直到空字符为止
			// 左对齐 8位置 不足不空..后2位精度
			printf("%-8.2f",1234.5678);
		}

		// 堆损坏
		char* pBuff = new char[2];
		sprintf(pBuff, "12");
		delete(pBuff);

		// 缺少参数 乱读地址崩溃
		printf("%s");
	}

	// 安全文件操作
	if (false)
	{
		string filename;
		ifstream ifs;

		cin >> filename;
		ifs.open(filename.c_str());

		if (ifs.fail())
		{
			cout << "error open: " << filename << endl;
		}
		else
		{
			cout << ifs.width(); // ???
		}

		ifs.close();
	}

	TagTestEx m_TagTestEx;

	return true;
}


