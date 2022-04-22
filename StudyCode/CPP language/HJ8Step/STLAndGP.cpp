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
#include <forward_list>
#include <deque>
#include <stack>
#include <set>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>

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

	// ITERATOR TAGS 迭代器类型
	// struct input_iterator_tag {};

	// struct output_iterator_tag {};

	// struct forward_iterator_tag : input_iterator_tag {}; 

	// struct bidirectional_iterator_tag : forward_iterator_tag {};

	// struct random_access_iterator_tag : bidirectional_iterator_tag {};

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

	// array:fixed size array of values
	if (0)
	{
		cout << "\ntest_array().......... \n";

		// 存储在堆上,导致堆空间大小不足 需要修改链接器中系统,堆栈保留大小
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

	// vector:varying size array of values
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

			// 输出值
			cout << "*pItem = " << *pItem << endl;
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

	// list:bidirectional linked list
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

		// 输出值
		cout << "*pItem = " << *pItem << endl;

		// 自身的算法优先使用,性能最佳
		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

		c.clear();
	}

	// forward list: singly linked list
	if (0)
	{
		cout << "\ntest_forward_list().......... \n";

		forward_list<string> c;

		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.push_front(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}

		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "forward_list.max_size()= " << c.max_size() << endl;  //536870911
		cout << "forward_list.front()= " << c.front() << endl;

		string target = get_a_target_string();
		
		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

		// 输出值
		cout << "*pItem = " << *pItem << endl;

		timeStart = clock();
		c.sort();
		cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

		c.clear();
	}

	// deque:double-ended queue 一段一段的连续空间构成
	if (0)
	{
		cout << "\ntest_deque().......... \n";

		deque<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try {
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "deque.size()= " << c.size() << endl;
		cout << "deque.front()= " << c.front() << endl;
		cout << "deque.back()= " << c.back() << endl;
		cout << "deque.max_size()= " << c.max_size() << endl;	//1073741821	
		
		string target = get_a_target_string();

		timeStart = clock();
		auto pItem = find(c.begin(), c.end(), target);
		cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

		timeStart = clock();
		sort(c.begin(), c.end());
		cout << "sort(), milli-seconds : " << (clock() - timeStart) << endl;

		c.clear();
	}

	// stack: container adaptors funs: top push pop
	if (0)
	{
		cout << "\ntest_stack().......... \n";

		// 默认deque: template <class _Ty, class _Container = deque<_Ty>>
		stack<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "stack.size()= " << c.size() << endl;
		cout << "stack.top()= " << c.top() << endl;
		c.pop();
		cout << "stack.size()= " << c.size() << endl;
		cout << "stack.top()= " << c.top() << endl;

		{
			//以 list 為底層 
			stack<string, list<string>> c;		
			for (long i = 0; i < 10; ++i) 
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
			c.pop();
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
		}

		{
			//以 vector 為底層 
			stack<string, vector<string>> c;	
			for (long i = 0; i < 10; ++i) 
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
			c.pop();
			cout << "stack.size()= " << c.size() << endl;
			cout << "stack.top()= " << c.top() << endl;
		}

		{
			//以 set 為底層  set不支持,大部分函数在编译期会报错
			stack<string, set<string>> c;	
			// c.push(string("123"));
			// cout << "stack.top()= " << c.top() << endl;
			// c.pop();
			cout << "stack.size()= " << c.size() << endl;
			// cout << "stack.top()= " << c.top() << endl;
		}
	}

	// queue: container adaptors funs: front back push pop
	if (0)
	{
		cout << "\ntest_queue().......... \n";

		queue<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "queue.size()= " << c.size() << endl;
		cout << "queue.front()= " << c.front() << endl;
		cout << "queue.back()= " << c.back() << endl;
		c.pop();
		cout << "queue.size()= " << c.size() << endl;
		cout << "queue.front()= " << c.front() << endl;
		cout << "queue.back()= " << c.back() << endl;

		{
			//以 list 為底層 
			queue<string, list<string>> c;
			for (long i = 0; i < 10; ++i) 
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
			c.pop();
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
		}

		{
			//以 vector 為底層 
			queue<string, vector<string>> c;
			for (long i = 0; i < 10; ++i) 
			{
				snprintf(buf, 10, "%d", rand());
				c.push(string(buf));
			}
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
			//[Error] 'class std::vector<std::basic_string<char> >' has no member named 'pop_front'
			//!c.pop();  
			cout << "queue.size()= " << c.size() << endl;
			cout << "queue.front()= " << c.front() << endl;
			cout << "queue.back()= " << c.back() << endl;
		}

		{
			//以 set 為底層  set不支持,大部分函数在编译期会报错
			queue<string, set<string>> c;
		}
	}

	// multiset: ordered red-black tree of key values, non-unique keys
	if (0)
	{
		cout << "\ntest_multiset().......... \n";

		multiset<string> c;
		char buf[10];
		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "multiset.size()= " << c.size() << endl;
		cout << "multiset.max_size()= " << c.max_size() << endl;	//214748364

		string target = get_a_target_string();
		{
			//比 c.find(...) 慢很多	
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);	
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
		}

		{
			//比 std::find(...) 快很多
			timeStart = clock();
			auto pItem = c.find(target);	

			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;

			// 输出值
			cout << "*pItem = " << *pItem << endl;

			// 可统计包含key的数量
			cout << "c.count() : " << c.count(target) << endl;
		}
	}

	// multimap: ordered red-black tree of {key, mapped} values, non-unique keys
	if (0)
	{
		cout << "\ntest_multimap().......... \n";

		multimap<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			try 
			{
				snprintf(buf, 10, "%d", rand());
				//multimap 不可使用 [] 做 insertion 
				c.insert(pair<long, string>(i, buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "multimap.size()= " << c.size() << endl;
		cout << "multimap.max_size()= " << c.max_size() << endl;	//178956970	

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;

		// 输出值
		cout << pItem->first << " " << pItem->second << endl;

		c.clear();
	}

	// unordered_multiset(hash_xxx): hash table of key-values, non-unique keys
	if (0)
	{
		// N个篮子 每个篮子里挂链表存元素
		cout << "\ntest_unordered_multiset().......... \n";

		unordered_multiset<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			// 当元素个数大于等于篮子数时,就会扩展篮子数量(大于个数)
			try 
			{
				snprintf(buf, 10, "%d", rand());
				c.insert(string(buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}

		// 容器解析 bucket数量一定大于元素个数 不让每个篮子太长
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "unordered_multiset.size()= " << c.size() << endl;
		cout << "unordered_multiset.max_size()= " << c.max_size() << endl;	//357913941
		cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
		cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
		cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;
		cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;
		
		// 输出篮子内的item
		for (unsigned i = 0; i < 10; ++i) 
		{
			cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
		}

		string target = get_a_target_string();

		{
			// //比 c.find(...) 慢很多	
			timeStart = clock();
			auto pItem = find(c.begin(), c.end(), target);	
			cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
			
			// 打印找到的元素
			cout << "*pItem= " << *pItem << endl;
		}

		{
			// //比 std::find(...) 快很多
			timeStart = clock();
			auto pItem = c.find(target);							
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
		}
	}

	// unordered_multimap(hash_xxx): hash table of {key, mapped} values, non-unique keys
	if (0)
	{
		cout << "\ntest_unordered_multimap().......... \n";

		unordered_multimap<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			// 当元素个数大于等于篮子数时,就会扩展篮子数量(大于个数)
			try {
				snprintf(buf, 10, "%d", rand());
				//multimap 不可使用 [] 進行 insertion 
				c.insert(pair<long, string>(i, buf));
			}
			catch (exception& p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		// 容器解析 bucket数量一定大于元素个数 不让每个篮子太长
		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "unordered_multimap.bucket_count()= " << c.bucket_count() << endl;
		cout << "unordered_multimap.size()= " << c.size() << endl;
		cout << "unordered_multimap.max_size()= " << c.max_size() << endl;	//357913941	

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
		
		cout << "found, value=" << (*pItem).second << endl;
	}

	// set:ordered red-black tree of key values, unique keys
	if (0)
	{
		cout << "\ntest_set().......... \n";

		set<string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			snprintf(buf, 10, "%d", rand());
			c.insert(string(buf));
		}

		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "set.size()= " << c.size() << endl;
		cout << "set.max_size()= " << c.max_size() << endl;	

		string target = get_a_target_string();

		{
			// 比 std::find(...) 快很多	
			timeStart = clock();
			auto pItem = c.find(target);								
			cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
			if (pItem != c.end())
				cout << "found, " << *pItem << endl;
			else
				cout << "not found! " << endl;
		}
	}

	// map:ordered red-black tree of {key, mapped} values, unique keys
	if (0)
	{
		cout << "\ntest_map().......... \n";

		map<long, string> c;
		char buf[10];

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i)
		{
			// 可以使用c[i]来新建或赋值 因为unique keys
			snprintf(buf, 10, "%d", rand());
			c[i] = string(buf);
		}

		cout << "milli-seconds : " << (clock() - timeStart) << endl;
		cout << "map.size()= " << c.size() << endl;
		cout << "map.max_size()= " << c.max_size() << endl;		//178956970

		long target = get_a_target_long();
		timeStart = clock();
		auto pItem = c.find(target);
		cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
	}

	// Operator Overloading
	if (1)
	{
		cout << "\nOperator Overloading.......... \n";
		// 可重载的运算法
		/*
		双目算术运算符 + (加)， - (减)， * (乘)， / (除)， % (取模)
		关系运算符 == (等于)， != (不等于)，< (小于)，>(大于)， <= (小于等于)， >= (大于等于)
		逻辑运算符 || (逻辑或)， && (逻辑与)，!(逻辑非)
		单目运算符 + (正)， - (负)， * (指针)， & (取地址)
		自增自减运算符++(自增)，--(自减)
		位运算符 | (按位或)， & (按位与)，~(按位取反)， ^ (按位异或), ， << (左移)， >> (右移)
		赋值运算符	=, +=, -=, *=, /=, % =, &=, |=, ^=, <<=, >>=
		空间申请与释放	new, delete, new[], delete[]
		其他运算符()(函数调用)，->(成员访问)，, (逗号)，[](下标)
		*/

		// 不可重载
		/*
		. 成员访问运算符
		.*, ->* 成员指针访问运算符
		:: 域运算符
		sizeof 长度运算符
		?: 条件运算符
		# 预处理符号
		*/

		// 迭代器重载操作符
	}

	// 分配器
	if (1)
	{
		/* 默认的分配器调用的new
		// STRUCT _Default_allocate_traits
		struct _Default_allocate_traits {
			__declspec(allocator) static void* _Allocate(const size_t _Bytes) {
				return ::operator new(_Bytes);
			}
		*/
	}
}
