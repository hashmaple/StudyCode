/********************************************************************
	filename: 	TestSTL
	purpose:	测试STL
	created:	2014/10/17
	updated:	2014/10/17
	author:		maple(周树青)	
*********************************************************************/
#include "TestSTL.h"

#include <algorithm>
#include <functional>
#include <exception>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <ctime>

using namespace std;

// 测试标志
BOOL BTEST_SIGN = FALSE;

MySTL::MySTL(void)
{
}

MySTL::~MySTL(void)
{
}

// 容器输出
#define SPRINT(container)	sPrint((container).begin(),(container).end());

//OP查找
bool FindValue(int value)
{
	return value % 2 == 0;
}

// 结构定义
struct TagMyStr
{
	int i;
	string str;

	TagMyStr()
	{
		i = 9527;
		str = "zsq";
	}
};

// 定义 <<
ostream& operator << (ostream& s, const TagMyStr& z)
{
	return s << "TagMyStr: " << z.i << " " << z.str;

}

// 位域(考虑对其)
struct PPN
{
	int  : 32;
	int nnn: 8;
	bool B : 1;
	bool C : 1;
	int A : 22;
};

const char* PropNameArray[10] = 
{
	"BeAttackTalk",
	"BeginFightTalk",
	"EndFightTalk",
	"SummonTalk",
	"DieTalk",
	"FreeTalk",
	"BeginQiecuoTalk",
	"EndQiecuoTalk",
	"SpecialTalk"
};


/////////////////////////////对外接口/////////////////////////////////////////////
// STL
void MySTL::BeginTest()
{
	// io
	if (BTEST_SIGN)
	{
		// 定义一个读写文件流 追加模式
		fstream fs_m;
		fs_m.open("test.ini", ofstream::out | ofstream::in | ios::app);
		if (!fs_m)
		{
			return;
		}

		// 写入一个字符
		fs_m << GetTickCount() << endl;

		// 定位到文件头开始读取
		fs_m.clear();
		fs_m.seekp(ios_base::beg);

		string str1, str2;
		fs_m >> str1 >> str2;

		// 读取一行
		getline(fs_m, str1);

		// 必须关闭 可重复使用fs_m
		fs_m.close();
		// clear any existing errors
		fs_m.clear();

		// string 流
		int val1 = 512, val2 = 1024; 
		stringstream format_message; 
		
		// 输入到字符串
		format_message << "val1: " << val1 << "\n" << "val2: " << val2 << "\n";

		// 输出字符串流中数据
		format_message >> str1 >> str2;

		// 获取所有字符
		string str3 = format_message.str();
	}

	// 字符串
	if (BTEST_SIGN)
	{
		string s1("testTeSt");
		string s2(10, 'z');
		string s3;

		// sonsole type
		// cin >> s3;

		// 转小写 auto变量为引用 修改后影响原数据
		for (auto& temp_char:s1)
		{
			// 是大写的才存入
			if (isupper(temp_char))
			{
				s3 += tolower(temp_char);
				temp_char = tolower(temp_char);
			}
		}

		// 转小写 不加&符号 为复制的对象
		for (auto temp_char:s1)
		{
			// 是大写的才存入
			if (islower(temp_char))
			{
				temp_char = toupper(temp_char);
			}
		}
		
		// 字符数组默认填充0 崩溃!! 只有9个
		for (int i = 0; i < 9 ; i ++)
		{
			const char* pStr = PropNameArray[i];
			string str = PropNameArray[i];
		}
	}

	// bitset
	if (BTEST_SIGN)
	{
		// 用字符输出 00000000000...111000
		string s1("111000");
		bitset<32> bit(s1);
		cout << bit << endl;

		// 非全0 && 有1
		if (bit.none() == false && bit.any())
		{
			cout << bit.count() << endl;
		}
	}

	// map
	if (BTEST_SIGN)
	{
		// 空字符也可以插入MAP
		map<string, int> mapTest;
		mapTest[""] = 3;

		// 插入字符和数字
		for (int i = 0; i < 1000; i++)
		{
			char buf[16] = {0};
			itoa(i, buf, 10);

			mapTest[buf] = i;
		}

		// 导致空字符串会被FIND
		string id;
		if (mapTest.find(id) != mapTest.end())
		{
			cout << "空字符串会被FIND"<< endl;
		}
	}

	// VECTOR
	if (BTEST_SIGN)
	{
		int j;

		vector<int> vct1;
		// 为空时候 都指向最后一个元素的下一个
		if (vct1.begin() == vct1.end())
		{
			vct1.push_back(1);
		}

		vector<int> vct_num(10, 5);
		// 越界BUG
		// j = vct_num[-1];
		// 抛出异常
		// j = vct_num.at(-1);

		vector<int>::iterator k = std::find(vct_num.begin(), vct_num.end(), 5);
		
	}

	// 位域(考虑对其) int反而访问速度快!
	if (BTEST_SIGN)
	{
		PPN my_test;
		my_test.A = 0;
		my_test.nnn = 0;
		my_test.B = 0;
		my_test.C = 1;
		int i = sizeof(my_test);

		i = sizeof(i);
	}

	// 字符流
	if (BTEST_SIGN)
	{
		// 字符最大范围
		string sas;
		string::size_type size = sas.max_size();

		// 错误输出
		cerr << "x = 1" << '\n';

		// 自定义输出
		TagMyStr my;
		cout << my;
	}

	// 异常处理
	if (BTEST_SIGN)
	{
		try
		{
			vector<int> vct;
			vct.resize(10,0);
			int i = vct.at(10);
		}
		catch (exception& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "error: ...";
		}
	}

	//vector
	if (BTEST_SIGN)
	{
		std::vector<int> vctInt;
		vctInt.reserve(10);
		vctInt.resize(10,0);
		for (size_t i = 0; i < 10 ; i ++)
		{
			vctInt.at(i) = i;
		}

		// 20位1
		vctInt.clear();
		vctInt.resize(20,1);

		// 21位5
		vctInt.assign(21, 5);
		SPRINT(vctInt);

		for (int i = 0; i < 9; i++)
		{
			vctInt.push_back(i);
		}

		//OP on the all values
		//for_each(vctInt.begin(),vctInt.end(),bind2nd<>(Add, 2));

		//find the counts of explicit value
		int nCount1 = std::count(vctInt.begin(), vctInt.end(), 2);
		int nCount2 = std::count_if(vctInt.begin(), vctInt.end(), FindValue);


		//find min or max value's point
		int minValue = *std::min_element(vctInt.begin(),vctInt.end());
		int maxValue = *std::max_element(vctInt.begin(),vctInt.end());


		//std::search_n(vctInt.begin(), vctInt.end(), vctInt.size(), int(2));

		std::list<int> vctInt2;


		std::copy(vctInt.begin(),vctInt.end(),std::front_inserter(vctInt2));
		std::swap_ranges(vctInt.begin(),vctInt.end(),vctInt2.begin());

		std::reverse(vctInt.begin(),vctInt.end());
		SPRINT(vctInt);
		std::random_shuffle(vctInt.begin(),vctInt.end());
		SPRINT(vctInt);
		std::sort(vctInt.begin(),vctInt.end());
		SPRINT(vctInt);
	}


	//堆 last in first out
	if (BTEST_SIGN)
	{
		std::stack<int> stk;
		stk.push(1);
		stk.push(2);
		stk.push(3);
		stk.pop();
		stk.pop();

		if (stk.empty() == false)
		{
			std::stack<int>::value_type nTop = stk.top();
		}
	}
	

	//队列 first in first out
	if (BTEST_SIGN)
	{
		std::queue<int> que;
		que.push(1);
		que.push(2);
		que.push(3);
		que.pop();
		que.pop();
		if (que.empty() == false)
		{
			std::queue<int>::value_type nTop = que.front();
			std::queue<int>::value_type nBack = que.back();
		}
	}
	


	//优先队列 first in first out
	if (BTEST_SIGN)
	{
		std::priority_queue<int> priQue;
		priQue.push(1);
		priQue.push(2);
		priQue.push(3);
		priQue.pop();
		priQue.pop();
		if (priQue.empty() == false)
		{
			std::queue<int>::value_type nTop = priQue.top();
		}
	}
	

	//bool array <set / reset>
	if (BTEST_SIGN)
	{
		std::bitset<10> bitSet;
		bitSet.set();

		// 把b中在pos处的二进制位置为0
		bitSet.reset(1);
		bool a0 = bitSet[0];
		bool a1 = bitSet[1];
		bool a2 = bitSet[2];

		bitSet[3] = 0;
		bool a3 = bitSet[3];
		bool a4 = bitSet[4];

		// b中置为1的二进制位的个数
		int n = bitSet.count();

		// b中是否存在置为1的二进制位？
		int nn = bitSet.any();
	}

	//string
	if (BTEST_SIGN)
	{
		//构造
		std::wstring str(L"zsqkyo0");
		std::wstring str1(L"zsqkyo1");
		std::wstring str2 = L"zsqkyo2";
		std::wstring str3 = L"zsqkyo3";
		std::wstring str4(L"zsqkyo4444444",7);
		std::wstring str5(str4,6);
		std::wstring str6(10,'a');

		// 直接加数值 截断有BUG!!!
		string zsqsqs = "asdasd";
		zsqsqs += 123456;
		str += 123456;

		//寻找
		std::wstring::size_type Idx1 = str.find(L"qk");
		std::wstring::size_type Idx2 = str.find('s');
		std::wstring::size_type Idx3 = str.find('t');
		
		//找不到
		if (Idx3 == std::wstring::npos)
		{
			Idx3 = str.find('q');
		}

		//截取
		str4 = str.substr(0,3);


		//连接
		str5 = L"zsqkyo " + str + L"." + L"111";
		const wchar_t* oldStr = str5.c_str();


		//截取
		str6 = str5.substr(0,8);
		const wchar_t oldSubStr[] = L"Hello";
	
		//大小范围
		size_t wcharSize = sizeof(oldSubStr);
		size_t wcharLength = wcslen(oldSubStr);
		std::wstring::size_type Size = str6.size();
		std::wstring::size_type maxSize = str6.max_size();
		std::wstring::size_type capSize = str6.capacity();
		
	}

	//有符号无符号
	//有符号和无符号比较 有符号转为无符号
	//为负的有符号数 一定不能与无符号比较
	//无符号数给有符号，注意判断溢出
	if (BTEST_SIGN)
	{
		//大多数情况下 不要用int 用size_t 除非带负号的数
		//多用size_t转为int 
		int num = -5;
		size_t unum = 10;
		
		//有符号 无符号比较
		//有符号数为负号，结果异常
		bool b1 = num > unum;
		bool b2 = unum > num;

		int i = 1;
		i = int(unum);
	}




	//IOStream
	if (BTEST_SIGN)
	{
		//输入输出
	/*	size_t a,b;
		while (std::cin>> a >> b)
		{
			std::cout<< a << std::endl;
			std::cout<< b << std::endl;
		}*/

		//文件读写
		std::fstream file;
		file.open("1.txt");
		if (file)
		{
			file << "Maple" << std::endl << "Time:" << GetTickCount()/1000/60/24/365;
			file << "周树青";
		}

		char str[64];
		file.getline(str,64);

		FILE* fp;
		fp = fopen("2.txt", "w+");
		fprintf(fp, "%s", "九阴真经");
		fclose(fp);
	}

	//function
	if (BTEST_SIGN)
	{
		//比较前保证不为空
		const char *p1 = "zsq";
		const char *p2 = "kyo";
		int ret = strcmp(p1,p2);

		//i是指针  j是变量
		int* i,j;
		int z = 10;
		i = &z;
		j = z;

		int x[] = {1,2,3,4,5};
		int y[] = {0,2,3,4,5};
		i = find(x, x+ 5, 2);
		i = find_first_of(x, x+ 5, y, y+5);

		// 加法函数对象
		plus<string> plus_string;
		cout << plus_string("hello", " world1 ");
		cout << plus<string>()("hello", " world2 ");

		// 排序函数对象使用,可用于迭代器
		int a[11] = {2,3,22,12,1,3,4,5,6,7,8};
		sort(a, a+11);
		sort(a, a+11, less<int>());
		sort(a, a+11, greater<int>());

		// 绑定到输出迭代器(适配器)
		ostream_iterator<int> outit(cout, " ");
		copy(a, a+11, outit);

		// 小于2的元素个数  和 不小于10的元素个数
		cout << endl << count_if(a, a+11, bind2nd(less<int>(), 2));
		cout << endl << count_if(a, a+11, not1(bind2nd(less<int>(), 10)));

	}

	//Allocator
	if (BTEST_SIGN)
	{
		std::vector<int> vct;

		vct.push_back(1);
		vct.push_back(2);
		vct.push_back(1);
		std::vector<int>::_Alloc alloc = vct.get_allocator();
	}

	//safe function
	if (BTEST_SIGN)
	{
		//2005以上 安全函数用_s结束
		int i ;
		scanf_s("%d",&i);
		printf_s("scanf_s num = %d",i);
	}

	//runtime type information
	if (BTEST_SIGN)
	{
		int i =10;
		int *p = &i;

		//都是指针或者都是左值
		if (typeid(*p) == typeid(i) && typeid(p) == typeid(&i))
		{
			std::cout<< "typeid(p) == typeid(&i)" <<std::endl;
		}
			
		//都是指针或者都是左值
		if (typeid(*p) == typeid(int) && typeid(i) == typeid(int))
		{
			std::cout<< "typeid(p) == typeid(int)" <<std::endl;
		}
	}

	//template
	if (BTEST_SIGN)
	{
		double key = 11;
		float i = sPower(key);
	}

	//random num
	if (BTEST_SIGN)
	{
		//统计随即数
		//先记录
		std::vector<int> VctNums(100, 0);

		//分类
		std::map<int, std::vector<int>> mapNums;
		//默认构造
		for (int i = 0; i < 10; i ++)
		{
			mapNums[i].resize(100, -1);
		}

		//选择进去
		for (int i = 0; i < 100; i ++)
		{
			//塞选数为0~9
			int swtichNum = (VctNums[i])/100;
			mapNums[swtichNum].at(i) = VctNums[i];
		}

		//按行打印
		std::map<int, std::vector<int>>::iterator it = mapNums.begin();
		while(it != mapNums.end())
		{
			//只能打印75列
			for (int i = 0 ; i < 75; i ++)
			{
				if (it->second.at(i) == -1)
				{
					std::cout << "-";
				}
				else
				{
					std::cout << "1";
				}
			}
			
			//换下行
			std::cout << std::endl;
			it++;
		}
		
	}

	//strstr
	if (BTEST_SIGN)
	{
		// 字符长度
		const char* a1 = "zsqkyo!!!";
		static char* a2 = "zsqkyo!!!";
		const char a3[] = "zsqkyo!!!";
		static char a4[] = "zsqkyo!!!";

		// 错误大小长度
		int i = sizeof(a1);
		i = sizeof(a2);
		i = sizeof(a3);
		i = sizeof(a4);

		// 正确字符长度
		i = strlen(a1);
		i = strlen(a2);
		i = strlen(a3);
		i = strlen(a4);

		// 为NULL不可以直接[0]校验
		const char* secName = "a"; //NULL;
		if (secName[0] == 0)
		{
			int i=1;
		}

		// 尚能返回
		std::wstring  str1 = GetWString();
		const TCHAR * q   = str1.c_str();

		// 无效字符
		const TCHAR * p   = GetWString().c_str(); 

		// 集合返回
		std::vector<int> vct1 = GetVector();
		std::vector<int> vct2 = GetVector(); 
		int nVar1 = vct1.at(2);
		int nVar2 = GetVector().at(2);

		// 字符查找
		std::string p1 = "abcdefg";
		std::string p2 = "f";
		std::string p3 = std::strstr(p1.c_str(), p2.c_str());
	}

}


///////////////////////////////内部函数///////////////////////////////////////////
//加数
void MySTL::Add(int& value, int addvalue)
{
	value += addvalue;
}

// 输出容器
template<class _FwdIt1>
inline bool MySTL::sPrint(_FwdIt1 _First1, _FwdIt1 _Last1)
{	

	for (;_First1 != _Last1; ++_First1 )
	{
		std::cout<< *_First1 <<"  ";
	}

	std::cout<<"\n";

	return true;
}

// 带类型校验的乘方
template<class power>
power MySTL::sPower(power value)
{
	//RTTI校验类型
	if (typeid(power) == typeid(int))
	{
		std::cout << "typeid(power) == typeid(int)" << std::endl;
	}
	return value * value;
}


// 返回STRING
std::wstring MySTL::GetWString()
{
	std::wstring q = L"zsq";
	return q;
}
// 返回VECTOR
std::vector<int> MySTL::GetVector()
{
	std::vector<int> q;
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);
	return q;
}

