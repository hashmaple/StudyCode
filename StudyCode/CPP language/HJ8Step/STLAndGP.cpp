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
#include <queue>

#include <xtree>
#include <set>
#include <map>

#include <unordered_set>
#include <unordered_map>
#include <numeric>

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

// 迭代器的类型重载
void _display_category(random_access_iterator_tag)
{
	cout << "random_access_iterator" << endl;
}
void _display_category(bidirectional_iterator_tag)
{
	cout << "bidirectional_iterator" << endl;
}
void _display_category(forward_iterator_tag)
{
	cout << "forward_iterator" << endl;
}
void _display_category(output_iterator_tag)
{
	cout << "output_iterator" << endl;
}
void _display_category(input_iterator_tag)
{
	cout << "input_iterator" << endl;
}

// 依据迭代器类型打印
template<typename I>
void display_category(I itr)
{
	typename iterator_traits<I>::iterator_category cagy;
	_display_category(cagy);

	//The output depends on library implementation.
	cout << "typeid(itr).name()= " << typeid(itr).name() << endl << endl;
}

// 用于STL算法函数
int acc_func(int x, int y) { return x + 2 * y; }

// STL算法依赖的仿函数
struct
{
	int operator()(int x, int y) { return x + 3 * y; }
} acc_obj;

bool compare_func(int i, int j) { return (i < j); }

struct compare_class {
	bool operator() (int i, int j) { return (i < j); }
} compare_obj;

// 除法函数
double divide_func(double x, double y)
{
	return x / y;
}

// 乘法功能类
struct MultiplyClass
{
	double a, b;

	double multiply()
	{
		return a * b;
	}
};

// 重载ostream对象的流插入 << 运算符函数
ostream& operator<< (ostream& out, const MultiplyClass& mc)
{
	out << "mc.a = "  << mc.a << " mc.b =  " << mc.b;
	return out;
}

using namespace std::placeholders;

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

	// ITERATOR TAGS 迭代器类型等
	if (0)
	{
		// 迭代器必须提供的5个types
		/*using _Nodeptr = typename _Mylist::_Nodeptr;
		using value_type = typename _Mylist::value_type;
		using difference_type = typename _Mylist::difference_type;
		using pointer = typename _Mylist::pointer;
		using reference = value_type&;*/

		// 类型不同,对算法的影响(++, --, distance, *, 等算法函数)
		// struct input_iterator_tag {};
		// struct output_iterator_tag {};
		// struct forward_iterator_tag : input_iterator_tag {};  // 单向
		// struct bidirectional_iterator_tag : forward_iterator_tag {};
		// struct random_access_iterator_tag : bidirectional_iterator_tag {};

		// 通过iterator_traits萃取各个迭代器的类型
		iterator_traits< forward_list<int>::iterator >::iterator_category forward_list_forward;
		cout << "forward_list it type = " << typeid(forward_list_forward).name() << endl;

		iterator_traits< list<int>::iterator >::iterator_category list_bidirectional;
		cout << "list it type = " << typeid(list_bidirectional).name() << endl;
		
		iterator_traits< set<int>::iterator >::iterator_category set_bidirectional;
		cout << "set it type = " << typeid(set_bidirectional).name() << endl;

		iterator_traits< array<int, 10>::iterator >::iterator_category array_random_access;
		cout << "array it type = " << typeid(array_random_access).name() << endl;
		
		iterator_traits< vector<int>::iterator >::iterator_category vec_random_access;
		cout << "vector it type = " << typeid(vec_random_access).name() << endl;


		// iterator_traits更进一步获取 传入的类型是否为class 是否为pod 等等
		// 比如 has non-trivial dtor 决定destroy时是否调用析构函数

		// 通过函数重载来输出类型
		display_category(array<int, 10>::iterator());
		display_category(vector<int>::iterator());
		display_category(list<int>::iterator());
		display_category(forward_list<int>::iterator());
		display_category(deque<int>::iterator());

		display_category(istream_iterator<int>());
		display_category(ostream_iterator<int>(cout, ""));
	}

	// array:fixed size array of values
	if (0)
	{
		cout << "\ntest_array().......... \n";

		// 存储在堆上,导致堆空间大小不足 需要修改链接器中系统,堆栈保留大小
		array<long, ASIZE> c;

		// pointer _Ptr; // beginning of array
		// size_t _Idx; // offset into array
		// _Ty _Elems[_Size];

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

		//pointer _Myfirst; // pointer to beginning of array
		//pointer _Mylast; // pointer to current end of sequence
		//pointer _Myend; // pointer to end of array

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

		//_Mapptr _Map; // pointer to array of pointers to blocks
		//size_type _Mapsize; // size of map array, zero or 2^N
		//size_type _Myoff; // offset of initial element
		//size_type _Mysize; // current length of sequence

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

	// stack: container adaptors funs: top push pop (deque)
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

	// queue: container adaptors funs: front back push pop (deque)
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

	// multiset<xtree>: ordered red-black tree of key values, non-unique keys
	if (0)
	{
		cout << "\ntest_multiset().......... \n";

		// _Tree<_Tset_traits<int, less<int>, allocator<int>, false>>;

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

	// multimap<xtree>: ordered red-black tree of {key, mapped} values, non-unique keys
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

	// STL提供的hash函数
	if (0)
	{
		// STL提供的hash函数
		auto hash_str = hash<const char*>()("mike 123456");
		auto hash_int = hash<int>()(123456);
		auto hash_float = hash<float>()(123.456f);
		auto hash_double = hash<double>()(123.456f);

		// 万用的hash function combine + args...
		// auto hash_val = hash_val(1, 2, 3, 4);
	}

	// unordered_multiset(hash_xxx): hash table of key-values, non-unique keys
	if (0)
	{
		// N个篮子 每个篮子里挂链表存元素
		cout << "\ntest_unordered_multiset().......... \n";

		// hash table -- list with vector of iterators for quick access

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

	// set<xtree>:ordered red-black tree of key values, unique keys
	if (0)
	{
		cout << "\ntest_set().......... \n";
		// class _Tree { // ordered red-black tree for map/multimap/set/multiset

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

	// map<xtree>:ordered red-black tree of {key , mapped} values, unique keys
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
	if (0)
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

	// 分配器：分配内存、构造对象、析构对象、释放内存
	if (0)
	{
		// STL容器有自己的分配器
		//construct() : placement new 指定地址构造对象
		//allocate() ： 内存空间分配（按对象的大小为单位从alloc中获取） new
		//destroy() : operator delete 指定地址析构对象
		//deallocate() : 内存空间的回收（释放给alloc进行管理） delete
			
		/* 默认的分配器调用的new
		// STRUCT _Default_allocate_traits
		struct _Default_allocate_traits {
			__declspec(allocator) static void* _Allocate(const size_t _Bytes) {
				return ::operator new(_Bytes);
			}
		*/
	}

	// STL 算法分析 accumulate for_each
	if (0)
	{
		cout << "\ntest_accumulate().......... \n";
		int init = 100;
		int nums[] = { 10,20,30 };


		// template <class _InIt, class _Ty, class _Fn>
		// accumulate(const _InIt _First, const _InIt _Last, _Ty _Val, _Fn _Reduce_op)

		cout << "using default accumulate: "; // 元素累加
		cout << accumulate(nums, nums + 3, init);  //160 = (10 + 20 + 30 + 100)
		cout << '\n';

		cout << "using functional's minus: "; // _Val = _Reduce_op(_Val, *_UFirst);
		cout << accumulate(nums, nums + 3, init, minus<int>()); //40 = -90 -70 -40
		cout << '\n';

		cout << "using custom function(x + 2 * y): "; // _Val = _Reduce_op(_Val, *_UFirst);
		cout << accumulate(nums, nums + 3, init, acc_func);	//220: 100+20 120+40 160+60
		cout << '\n';

		cout << "using custom object(x + 3y): "; // _Val = _Reduce_op(_Val, *_UFirst);
		cout << accumulate(nums, nums + 3, init, acc_obj);	//280 
		cout << '\n';

		// for_each demo
		vector<int> myvec;
		myvec.push_back(10);
		myvec.push_back(20);
		myvec.push_back(30);

		// 打印
		for_each(myvec.begin(), myvec.end(), myfunc);
		cout << endl;		//output: 10 20 30

		// 打印
		for_each(myvec.begin(), myvec.end(), myobj);
		cout << endl;		//output: 10 20 30

		//since C++11, range-based warn:&
		for (auto& elem : myvec)
			elem += 5;

		for (auto elem : myvec)
			cout << ' ' << elem; 	//output: 15 25 35

		// 其他函数: 
		// replace repace_copy relace_if 替换
		// count count_if
		// find find_if
		// sort

	}

	// sort算法
	if (0)
	{
		cout << "\ntest_sort().......... \n";

		// 不带sort的容器: array vector deque
		// 遍历自然sorted状态: set map unordered
		// 自带sort容器: lsit forward_list

		int myints[] = { 32,71,12,45,26,80,53,33 };
		vector<int> myvec(myints, myints + 8);          // 32 71 12 45 26 80 53 33

		// using default comparison (operator <):
		sort(myvec.begin(), myvec.begin() + 4);         //(12 32 45 71)26 80 53 33

		// using function as comp
		sort(myvec.begin() + 4, myvec.end(), compare_func); 	// 12 32 45 71(26 33 53 80)

		// using object as comp
		sort(myvec.begin(), myvec.end(), compare_obj);      //(12 26 32 33 45 53 71 80)

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 12 26 32 33 45 53 71 80

	   // using reverse iterators and default comparison (operator <):
		sort(myvec.rbegin(), myvec.rend());

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 80 71 53 45 33 32 26 12    

	   // using explicitly default comparison (operator <):
		sort(myvec.begin(), myvec.end(), less<int>());

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 12 26 32 33 45 53 71 80   

	   // using another comparision criteria (operator >):
		sort(myvec.begin(), myvec.end(), greater<int>());

		// print out content:
		cout << "\nmyvec contains:";
		for (auto elem : myvec)		//C++11 range-based for statement
			cout << ' ' << elem; 	//output: 80 71 53 45 33 32 26 12 	     
	}

	// 算法的实现
	if (0)
	{
		cout << "\ntest_all_components().......... \n";

		int ia[7] = { 27, 210, 12, 47, 109, 83, 40 };
		vector<int, allocator<int>> vi(ia, ia + 7);

		// 
		// FUNCTION TEMPLATE not1
		/*template <class _Fn>
		_CXX17_DEPRECATE_NEGATORS _NODISCARD constexpr unary_negate<_Fn> not1(const _Fn& _Func) {
			return unary_negate<_Fn>(_Func);
		}*/

		// 一元函数  argument_type result_type
		// CLASS TEMPLATE unary_negate
		/*template <class _Fn>
		class _CXX17_DEPRECATE_NEGATORS unary_negate {
		public:
			using argument_type = typename _Fn::argument_type;
			using result_type = bool;

			constexpr explicit unary_negate(const _Fn& _Func) : _Functor(_Func) {}

			_NODISCARD constexpr bool operator()(const argument_type& _Left) const {
				return !_Functor(_Left);
			}

		private:
			_Fn _Functor;
		};*/

		// 仿函数 2元操作 需要typedef 1stArg 2ndArg ResultType
		/*template <class _Ty = void>
		struct less {
			_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef _Ty _FIRST_ARGUMENT_TYPE_NAME;
			_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef _Ty _SECOND_ARGUMENT_TYPE_NAME;
			_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef bool _RESULT_TYPE_NAME;

			_NODISCARD constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const {
				return _Left < _Right;
			}
		};*/

		// 查找 v1提供的范围内 取反(小于40) 的数 => 大于等于40的个数
		cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
		cout << endl;
	}

	// 新适配器 bind
	if (0)
	{
		// 需要使用namespace std::placeholders;

		auto fun1 = bind(divide_func, 10, 2);
		cout << " 10 / 2 = " << fun1() << endl;
		cout << " fun1 = " << bind(divide_func, 10, 2)() << endl;

		// arg1先占位 2赋值给arg2 在调用
		auto fun2 = bind(divide_func, _1, 2);
		cout << " fun2 = " << fun2(10) << endl;

		// 10赋值给arg1 在调用 arg1/2
		auto fun22 = bind(divide_func, 10, _1);
		cout << " fun22 = " << fun22(2) << endl;

		// 绑定
		auto fun3 = bind(divide_func, _1, _2);
		cout << " fun3 = " << fun3(10, 2) << endl;

		// 逆序绑定
		auto fun4 = bind(divide_func, _2, _1);
		cout << " fun4 = " << fun4(2, 10) << endl;

		// 绑定成员
		MultiplyClass mpObj{ 10, 2 };

		cout << "bind mpObj = " << bind(&MultiplyClass::multiply, mpObj)() << endl;

		// 绑定mpObj为this 来调用MultiplyClass::multiply
		auto b1 = bind(&MultiplyClass::multiply, _1);
		cout << "b1 = " << b1(mpObj) << endl;

		// 输出mpObj.a
		auto b2 = bind(&MultiplyClass::a, mpObj);
		cout << "b2 = " << b2() << endl;

		// 输出mpObj.b
		auto b3 = bind(&MultiplyClass::b, _1);
		cout << "b3 = " << b3(mpObj) << endl;

		vector<int> v = { 1,3,5,7};

		// 小于5的数量 2  (return _Left < 5;)
		auto fn1 = bind(less<int>(), _1, 5);
		cout << count_if(v.begin(), v.end(), fn1) << endl;

		// 大于5的数量 1  (return 5 < _Right;)
		auto fn2 = bind(less<int>(), 5, _1);
		cout << count_if(v.begin(), v.end(), fn2) << endl;
	}

	// copy inserter ostream_iterator istream_iterator
	if (0)
	{
		vector<int> v1 = { 1,3,5,7,9};
		vector<int> v2(3, 0);
		vector<int> v3;

		// 复制,需要有空间
		copy(v1.begin(), v1.end(), v2.begin());

		// 复制,通过inserter插入
		copy(v1.begin(), v1.end(), inserter(v3, v3.begin()));

		// insert value into output stream, followed by delimiter
		/*ostream_iterator& operator=(const _Ty& _Val) 
		{ 
			*_Myostr << _Val; // 输出val;
			if (_Mydelim) *_Myostr << _Mydelim; // 输出分隔符
		}*/

		// ostream_iterator 打印
		std::ostream_iterator<int> out_it(std::cout, ",");
		copy(v1.begin(), v1.end(), out_it);


		// istream_iterator get a _Ty value if possible
		/*void _Getval() 
		{ 
			_STL_ASSERT(_Myistr, "The stored stream pointer in_stream must be non-null");
			if (!(*_Myistr >> _Myval)) // 输入数据
			{
				_Myistr = nullptr;
			}
		}*/

		int a1, a2;
		std::istream_iterator<int> in_it_end;
		std::istream_iterator<int> in_it(std::cin);

		if (in_it != in_it_end)
		{
			a1 = *in_it;
		}

		++in_it;
		if (in_it != in_it_end)
		{
			a2 = *in_it;
		}

		cout << "a1 = " << a1 << " a2 = " << a2 << endl;

	}

	// tuple
	if (0)
	{
		tuple<string, int, float> t1("mike", 35, 1.75f);
		cout << "sizeof(t1) = " << sizeof(t1) << endl;
		cout << get<0>(t1) << endl;
		cout << get<1>(t1) << endl;
		cout << get<2>(t1) << endl;

		auto t2 = make_tuple(1, 2, 3, "123");
		get<0>(t2) = 100; // 修改值
		cout << get<0>(t2) << endl;
		cout << get<1>(t2) << endl;
		cout << get<2>(t2) << endl;
		cout << get<3>(t2) << endl;
	}

	// 重载cout<< 支持自定义对象
	if (0)
	{
		MultiplyClass mc{ 100, 200 };
		cout << " mc " << mc << endl;
	}

	// 分析moveable
	if (0)
	{
		vector<string> v1(1000000, "mike");
		vector<string> v2(100, "zsq");

		//測試 move 
		cout << "\n\ntest, with moveable elements" << endl;

		// 消耗30ms 需要做深拷贝 扩容时内部用的move 
		// 若为不支持moveable的自定义更慢
		auto timeStart = clock();
		vector<string> c11(v1);
		cout << "copy, milli-seconds : " << (clock() - timeStart) << endl;

		// 消耗0ms 只做浅拷贝
		timeStart = clock();
		vector<string> c12(std::move(v1));
		cout << "move copy, milli-seconds : " << (clock() - timeStart) << endl;

		// 消耗0ms 只做swap:交换数据的地址
		timeStart = clock();
		vector<string> c13;
		c13.swap(c12);
		cout << "swap, milli-seconds : " << (clock() - timeStart) << endl;
		cout << "c12.capacity() : " << c12.capacity() << endl;
		cout << "c13.capacity() : " << c13.capacity() << endl;
	}
}
