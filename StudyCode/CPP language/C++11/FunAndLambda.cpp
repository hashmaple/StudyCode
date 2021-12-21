/*!
 * \file FunAndLambda.cpp
 * \date 2019/02/15 10:28
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief STL函数对象和lambda
 *
 * TODO: long description
 *
 * \note
*/
#include "C++11.h"

#include <vector>
#include <string>

#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <xutility>
#include <list>
#include <numeric>

using namespace std;

// 宏 打印容器
#define PRINT_ELEMENTS_C(CONTAINER)  cout << "Container "<< #CONTAINER << ": "; \
for (const auto& it : CONTAINER) { cout << it.name << " " ; }; cout << endl;

// 宏 打印容器
#define PRINT_ELEMENTS(CONTAINER)  cout << "Container "<< #CONTAINER << ": "; \
for (const auto& it : CONTAINER) { cout << it << " " ; }; cout << endl;

class Student
{
public:
	Student(string _name, int _age, int _score) 
	{
		name = _name;
		age = _age;
		score = _score;
	};

	string name;
	int age;
	int score;
};

// 函数对象为排序规则
class StudentSortCriterion 
{
public:
	bool operator() (const Student& s1, const Student& s2) const 
	{
		// 返回小于号规则
		return s1.score < s2.score || (s1.score == s2.score && s1.age < s2.age);
	}
};

// 函数对象保存数值,每次返回+1数值
class IntSquence
{
private:
	int value;
public:
	IntSquence(int initvalue) :value(initvalue)
	{};

	int operator()()
	{
		return ++value;
	}
};

// 函数对象和for_each合作求平均数
class MeanValue
{
private:
	int num;
	int sum;
public:
	MeanValue() :num(0), sum(0)
	{};

	void operator()(int element)
	{
		 ++num;
		 sum += element;
	}

	double value()
	{
		return static_cast<double>(sum) / num;
	}
};


/////////////////////////////对外接口/////////////////////////////////////////////
// FunAndLambda
void FunAndLambda::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// Lambda表达式 二种传递方法 类似为匿名函数的特效
	if (0)
	{
		// [捕获列表] (参数列表) mutable(可选)异常属性->返回类型 { 函数体}

		// 传递对象
		int value = 1;

		// 1 值捕获  在创建的时候拷贝进入,非调用时. 输出1
		auto transfer_value = [value]{return value;};
		value = 2;
		cout << "值传递 transfer_value[value] = " << transfer_value() << endl;

		// 2 引用捕获 保存的是引用, 输出100
		auto transfer_quote = [&value] {return value; };
		value = 100;
		cout << "引用传递 transfer_quote[&value] = " << transfer_quote() << endl;

		// 3 symbol传递,自行推导哪些需要传递,用符号明确是值还是引用
		int other_value = 10;
		value = 1;
		auto symbol_value1 = [=] {return value + other_value; };
		value = 2;
		auto symbol_value2 = [&] {return value + other_value; };
		value = 3;
		cout << "symbol传递 symbol_value1[=] = " << symbol_value1() << endl; // 11
		cout << "symbol传递 symbol_value2[&] = " << symbol_value2() << endl; // 13
	}

	// 对象对象为排序规则
	if (false)
	{
		// 通过函数对象 来排序. 可以定制排序规则
		set<Student, StudentSortCriterion> MySet;
		MySet.insert(Student("a", 3, 3));
		MySet.insert(Student("b", 2, 3));
		MySet.insert(Student("c", 1, 3));

		PRINT_ELEMENTS_C(MySet);
	}

	// 函数对象保存状态
	if (false)
	{
		// 插入9个数 并且为函数对象内部的数值
		vector<int> MyVct;
		generate_n(back_inserter(MyVct), 9, IntSquence(1));
		PRINT_ELEMENTS(MyVct);
	}

	// 函数对象和for_each合作求平均数
	if (false)
	{
		vector<int> MyVct{ 1,3,5,7,9,2,4,6,8,10,111 };

		MeanValue mean_value = for_each(MyVct.begin(), MyVct.end(), MeanValue());
		
		PRINT_ELEMENTS(MyVct);

		cout << "平均数为: " << mean_value.value() << endl;

		// 循环输出,并且修改了容器的数据+1
		for_each(MyVct.begin(), MyVct.end(), 
			[](int& elem)
		{
			cout << elem++ << " ";
		}
		);
		cout << endl;

		PRINT_ELEMENTS(MyVct);

	}

	// lambda表达式
	// lambda表达式的本质就是重载了()运算符的类，这种类通常被称为functor，
	// 即行为像函数的类。因此lambda表达式对象其实就是一个匿名的functor。
	if (false)
	{
		auto plus = [](int i, int j)
		{
			return i + j;
		};

		cout << plus(1, 2) << endl;

		auto plusAndtimes = [](int i, int j)
		{
			return (i + j) * 10;
		};

		cout << plusAndtimes(1, 2) << endl;
	}

	// 非更易型算法  不修改数据的算法.
	if (false)
	{
		vector<int> MyVct{ 1,3,5,7,9,2,4,6,8,10,3,3 };
		PRINT_ELEMENTS(MyVct);

		cout << "3's cout = " << count(MyVct.begin(), MyVct.end(), 3) << endl;

		// 最大最小元素
		cout << "min_element = " << *min_element(MyVct.begin(), MyVct.end()) << endl;
		cout << "max_element = " << *max_element(MyVct.begin(), MyVct.end()) << endl;
		cout << "minmax_element.first = " << *minmax_element(MyVct.begin(), MyVct.end()).first << endl;
		cout << "minmax_element.second = " << *minmax_element(MyVct.begin(), MyVct.end()).second << endl;

		// 查找某数
		auto find_it = find(MyVct.begin(), MyVct.end(), 5);
		if (find_it != MyVct.end())
		{
			cout << "find(MyVct.begin(), MyVct.end(),VALUE) = " << *find_it  << endl;
		}

		// 寻找连续的几个VALUE
		auto search_n_it = search_n(MyVct.begin(), MyVct.end(), 2,3);
		if (search_n_it != MyVct.end())
		{
			cout << "search_n(MyVct.begin(), MyVct.end(),2,3) = " << *search_n_it << endl;
		}

		// 查找第一个区间  最先/最后的为 find_first/find_end
		auto range = { 5,7,9 };
		auto search_range = search(MyVct.begin(), MyVct.end(), range.begin(), range.end());
		if (search_range != MyVct.end())
		{
			cout << "search(MyVct.begin(), MyVct.end(), range.begin(), range.end()) = " << *search_range << endl;
		}

		// 查找连续相等的元素 3,3
		auto adjacent_find_it = adjacent_find(MyVct.begin(), MyVct.end());
		if (adjacent_find_it != MyVct.end())
		{
			cout << "adjacent_find(MyVct.begin(), MyVct.end()) = " << *adjacent_find_it << endl;
		}

		// 判断区间是否相等 1,3,5,7是否在接下来MyVct.begin的里面.
		auto equal_range = { 1,3,5,7 };
		auto equal_it = equal(equal_range.begin(), equal_range.end(), MyVct.begin());
		if (equal_it)
		{
			cout << "equal(equal_range.begin(), equal_range.end(), MyVct.begin()) true!" << endl;
		}
		else
		{
			cout << "equal(equal_range.begin(), equal_range.end(), MyVct.begin()) false!" << endl;
		}

		// 判断区间是否排序
		auto sort_list = { 1,3,5,7,9 };
		auto sort_list2 = { 1,3,5,7,6 };
		cout << "{ 1,3,5,7,9 } is_sorted is = " << is_sorted(sort_list.begin(), sort_list.end()) << endl;
		cout << "{ 1,3,5,7,6 } is_sorted is = " << is_sorted(sort_list2.begin(), sort_list2.end()) << endl;
	}

	// 更易型算法  变动,改动数据的算法.
	if (false)
	{
		vector<int> MyList = { 1,2,3,4,5 };

		// copy 需要有空间5个元素.  或者选择后部插入
		vector<int> MyList2(5);
		vector<int> MyList3;
		copy(MyList.begin(), MyList.end(), MyList2.begin());
		copy(MyList.begin(), MyList.end(), back_inserter(MyList3));
		PRINT_ELEMENTS(MyList2);
		PRINT_ELEMENTS(MyList3);

		// fill fill_n 需要保证空间 填入给定的值
		fill(MyList2.begin(), MyList2.end(), 2);
		fill_n(MyList3.begin(), 3, 0);	// 给N个数修改为T
		PRINT_ELEMENTS(MyList2);
		PRINT_ELEMENTS(MyList3);

		// iota全换新值 为递增连续T T+1 T+2
		PRINT_ELEMENTS(MyList);
		iota(MyList.begin(), MyList.end(), 10);
		cout << "=== after iota, from: 10 ===" << endl;
		PRINT_ELEMENTS(MyList);

		// replace 替换元素 T->N_T
		PRINT_ELEMENTS(MyList);
		replace(MyList.begin(), MyList.end(), 10, 100);
		cout << "=== after replace, 10 -> 100 ===" << endl;
		PRINT_ELEMENTS(MyList);

	}

	// 移除型算法 remove unique
	if (false)
	{
		vector<int> MyList = { 1,1,2,2,3,3,4,4,5,5 };
		PRINT_ELEMENTS(MyList);

		// remove移除元素 可是满意修改容器的数量,需要自己删除最后.
		auto pos = remove(MyList.begin(), MyList.end(), 1);
		cout << "remove 1 and erase(pos, end): " <<endl;
		MyList.erase(pos, MyList.end());
		PRINT_ELEMENTS(MyList);

		// 移除重复 必须已排序
		pos = unique(MyList.begin(), MyList.end());
		cout << "unique and erase(pos, end): " << endl;
		MyList.erase(pos, MyList.end());
		PRINT_ELEMENTS(MyList);

	}

	// 变序/排序型算法 反转 乱序
	if (false)
	{
		vector<int> MyList = { 1,2,3,4,5,6,7,8,9 };
		PRINT_ELEMENTS(MyList);

		// reverse 反转元素次序
		reverse(MyList.begin(), MyList.end());
		cout << "reverse : ";
		PRINT_ELEMENTS(MyList);

		// random_shuffle通用重新洗牌 其他还有三个方法.
		 random_shuffle(MyList.begin(), MyList.end());
		cout << "random_shuffle : ";
		PRINT_ELEMENTS(MyList);

		// sort  排序算法. stable_sort保证相等元素老顺序不变
		stable_sort(MyList.begin(), MyList.end());
		cout << "stable_sort : ";
		PRINT_ELEMENTS(MyList);
	}

	// heap算法集合
	if (false)
	{
		vector<int> MyList = { 1,2,3,4,5,6,7,8,9 };
		PRINT_ELEMENTS(MyList);

		// make_heap 将元素转为heap
		make_heap(MyList.begin(), MyList.end());
		cout << "make_heap : ";
		PRINT_ELEMENTS(MyList);

		// pop_heap 把最高元素移动到最后位置.
		pop_heap(MyList.begin(), MyList.end());
		cout << "pop_heap : ";
		PRINT_ELEMENTS(MyList);

		// sort_heap 将heap顺序转为一个已排序的.
		make_heap(MyList.begin(), MyList.end());
		sort_heap(MyList.begin(), MyList.end());
		cout << "sort_heap : ";
		PRINT_ELEMENTS(MyList);
	}

}
