//--------------------------------------------------------------------
// 文件名:		STLAndGP
// 内  容:		STL和泛型编程
// 说  明:		
// 创建日期:	2022年4月20日
// 整理日期:	2022年4月20日
// 创建人:		Mike(周树青)
//--------------------------------------------------------------------
#include "STLAndGP.h"	// 优先当前目录

#include <iostream>		// 优先系统目录
#include <vector>
#include <algorithm>
#include <functional>
#include <array>

#include <cstdlib> //qsort, bsearch, NULL
#include <list>

using namespace std;

const long ASIZE = 100000L;

// 函数 输出元素
void myfunc(int i) { cout << ' ' << i;}

// 仿函数 输出元素
struct myclass 
{
	void operator() (int i) { cout << ' ' << i; }
} myobj;

// 获取一个long类型
long get_a_target_long()
{
	long target = 0;

	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	return target;
}

// 获取一个字符串类型
string get_a_target_string()
{
	long target = 0;
	char buf[10];

	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	snprintf(buf, 10, "%d", target);
	return string(buf);
}

// 用long类型比较
int compareLongs(const void* a, const void* b)
{
	return (*(long*)a - *(long*)b);
}

// 字符串比较
int compareStrings(const void* a, const void* b)
{
	if (*(string*)a > *(string*)b)
		return 1;
	else if (*(string*)a < *(string*)b)
		return -1;
	else
		return 0;
}

// 对外接口
void STLAndGP::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 入场了解
	if (0)
	{
		cout << "\n 认识六大部件 \n";

		// 容器
		int ia[7] = { 27, 210, 12, 47, 109, 83, 40 };
		// 容器 分配器(用默认的就好)  迭代器-前闭后开区间[begin,1,2,end)
		vector<int, allocator<int>> vi(ia, ia + 7);

		// 算法 函数适配器 函数对象 (统计出vi给出的区间内 !(小于40) = 大于等于40的个数)
		cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40))) << endl;	

		// 测试for_each
		cout << "\ntest_for_each().......... \n";

		vector<int> myvec{10,20,30};

		// 函数
		for_each(myvec.begin(), myvec.end(), myfunc);
		cout << endl;		//output: 10 20 30

		// 仿函数
		for_each(myvec.begin(), myvec.end(), myobj);
		cout << endl;		//output: 10 20 30

		// 引用 会改变
		for (auto& elem : myvec)
			elem += 5;

		for (auto elem : myvec)
			cout << ' ' << elem; 	//output: 15 25 35
	}

	// array
	if (0)
	{
		cout << "\ntest_array().......... \n";

		array<long, ASIZE> c;

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i) 
		{
			c[i] = rand();
		}

		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "array.size()= " << c.size() << endl;
		cout << "array.front()= " << c.front() << endl;
		cout << "array.back()= " << c.back() << endl;
		cout << "array.data()= " << c.data() << endl;

		// 获取一个查找的数字
		long target = get_a_target_long();

		timeStart = clock();

		// 快速排序
		::qsort(c.data(), ASIZE, sizeof(long), compareLongs);

		// 二分查找
		long* pItem = (long*)::bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
		
		// 排序+查找的耗时
		cout << "qsort()+bsearch(), milli-seconds : " << (clock() - timeStart) << endl;
	}

	// vector
	if (0)
	{
		cout << "\ntest_vector().......... \n";

		vector<string> c;

		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				//曾經最高 i=58389486 then std::bad_alloc
				abort();
			}
		}
		cout << "setup milli-seconds : " << (clock() - timeStart) << endl;
		cout << "vector.max_size()= " << c.max_size() << endl;	//1073747823
		cout << "vector.size()= " << c.size() << endl;
		cout << "vector.front()= " << c.front() << endl;
		cout << "vector.back()= " << c.back() << endl;
		cout << "vector.data()= " << c.data() << endl;
		cout << "vector.capacity()= " << c.capacity() << endl << endl;

		string target = get_a_target_string();
		
		{
			// 使用STL的模板算法来查找
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
		}

		{
			// 使用sort + bsearch来查找
			timeStart = clock();
			sort(c.begin(), c.end());
			cout << "sort(), milli-seconds : " << (clock() - timeStart) << endl;

			timeStart = clock();
			string* pItem = (string*)::bsearch(&target, (c.data()),
				c.size(), sizeof(string), compareStrings);
			cout << "bsearch(), milli-seconds : " << (clock() - timeStart) << endl;
		}

		c.clear();
	}

	// list
	if (0)
	{
		cout << "\ntest_list().......... \n";

		list<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}

		cout << "setup milli-seconds : " << (clock() - timeStart) << endl;
		cout << "list.size()= " << c.size() << endl;
		cout << "list.max_size()= " << c.max_size() << endl;
		cout << "list.front()= " << c.front() << endl;
		cout << "list.back()= " << c.back() << endl;

		string target = get_a_target_string();

		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

		c.clear();
	}
}
