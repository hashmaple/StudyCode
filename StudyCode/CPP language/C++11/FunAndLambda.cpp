/*!
 * \file FunAndLambda.cpp
 * \date 2019/02/15 10:28
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief STL���������lambda
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

// �� ��ӡ����
#define PRINT_ELEMENTS_C(CONTAINER)  cout << "Container "<< #CONTAINER << ": "; \
for (const auto& it : CONTAINER) { cout << it.name << " " ; }; cout << endl;

// �� ��ӡ����
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

// ��������Ϊ�������
class StudentSortCriterion 
{
public:
	bool operator() (const Student& s1, const Student& s2) const 
	{
		// ����С�ںŹ���
		return s1.score < s2.score || (s1.score == s2.score && s1.age < s2.age);
	}
};

// �������󱣴���ֵ,ÿ�η���+1��ֵ
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

// ���������for_each������ƽ����
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


/////////////////////////////����ӿ�/////////////////////////////////////////////
// FunAndLambda
void FunAndLambda::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// Lambda���ʽ ���ִ��ݷ��� ����Ϊ������������Ч
	if (0)
	{
		// [�����б�] (�����б�) mutable(��ѡ)�쳣����->�������� { ������}

		// ���ݶ���
		int value = 1;

		// 1 ֵ����  �ڴ�����ʱ�򿽱�����,�ǵ���ʱ. ���1
		auto transfer_value = [value]{return value;};
		value = 2;
		cout << "ֵ���� transfer_value[value] = " << transfer_value() << endl;

		// 2 ���ò��� �����������, ���100
		auto transfer_quote = [&value] {return value; };
		value = 100;
		cout << "���ô��� transfer_quote[&value] = " << transfer_quote() << endl;

		// 3 symbol����,�����Ƶ���Щ��Ҫ����,�÷�����ȷ��ֵ��������
		int other_value = 10;
		value = 1;
		auto symbol_value1 = [=] {return value + other_value; };
		value = 2;
		auto symbol_value2 = [&] {return value + other_value; };
		value = 3;
		cout << "symbol���� symbol_value1[=] = " << symbol_value1() << endl; // 11
		cout << "symbol���� symbol_value2[&] = " << symbol_value2() << endl; // 13
	}

	// �������Ϊ�������
	if (false)
	{
		// ͨ���������� ������. ���Զ����������
		set<Student, StudentSortCriterion> MySet;
		MySet.insert(Student("a", 3, 3));
		MySet.insert(Student("b", 2, 3));
		MySet.insert(Student("c", 1, 3));

		PRINT_ELEMENTS_C(MySet);
	}

	// �������󱣴�״̬
	if (false)
	{
		// ����9���� ����Ϊ���������ڲ�����ֵ
		vector<int> MyVct;
		generate_n(back_inserter(MyVct), 9, IntSquence(1));
		PRINT_ELEMENTS(MyVct);
	}

	// ���������for_each������ƽ����
	if (false)
	{
		vector<int> MyVct{ 1,3,5,7,9,2,4,6,8,10,111 };

		MeanValue mean_value = for_each(MyVct.begin(), MyVct.end(), MeanValue());
		
		PRINT_ELEMENTS(MyVct);

		cout << "ƽ����Ϊ: " << mean_value.value() << endl;

		// ѭ�����,�����޸�������������+1
		for_each(MyVct.begin(), MyVct.end(), 
			[](int& elem)
		{
			cout << elem++ << " ";
		}
		);
		cout << endl;

		PRINT_ELEMENTS(MyVct);

	}

	// lambda���ʽ
	// lambda���ʽ�ı��ʾ���������()��������࣬������ͨ������Ϊfunctor��
	// ����Ϊ�������ࡣ���lambda���ʽ������ʵ����һ��������functor��
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

	// �Ǹ������㷨  ���޸����ݵ��㷨.
	if (false)
	{
		vector<int> MyVct{ 1,3,5,7,9,2,4,6,8,10,3,3 };
		PRINT_ELEMENTS(MyVct);

		cout << "3's cout = " << count(MyVct.begin(), MyVct.end(), 3) << endl;

		// �����СԪ��
		cout << "min_element = " << *min_element(MyVct.begin(), MyVct.end()) << endl;
		cout << "max_element = " << *max_element(MyVct.begin(), MyVct.end()) << endl;
		cout << "minmax_element.first = " << *minmax_element(MyVct.begin(), MyVct.end()).first << endl;
		cout << "minmax_element.second = " << *minmax_element(MyVct.begin(), MyVct.end()).second << endl;

		// ����ĳ��
		auto find_it = find(MyVct.begin(), MyVct.end(), 5);
		if (find_it != MyVct.end())
		{
			cout << "find(MyVct.begin(), MyVct.end(),VALUE) = " << *find_it  << endl;
		}

		// Ѱ�������ļ���VALUE
		auto search_n_it = search_n(MyVct.begin(), MyVct.end(), 2,3);
		if (search_n_it != MyVct.end())
		{
			cout << "search_n(MyVct.begin(), MyVct.end(),2,3) = " << *search_n_it << endl;
		}

		// ���ҵ�һ������  ����/����Ϊ find_first/find_end
		auto range = { 5,7,9 };
		auto search_range = search(MyVct.begin(), MyVct.end(), range.begin(), range.end());
		if (search_range != MyVct.end())
		{
			cout << "search(MyVct.begin(), MyVct.end(), range.begin(), range.end()) = " << *search_range << endl;
		}

		// ����������ȵ�Ԫ�� 3,3
		auto adjacent_find_it = adjacent_find(MyVct.begin(), MyVct.end());
		if (adjacent_find_it != MyVct.end())
		{
			cout << "adjacent_find(MyVct.begin(), MyVct.end()) = " << *adjacent_find_it << endl;
		}

		// �ж������Ƿ���� 1,3,5,7�Ƿ��ڽ�����MyVct.begin������.
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

		// �ж������Ƿ�����
		auto sort_list = { 1,3,5,7,9 };
		auto sort_list2 = { 1,3,5,7,6 };
		cout << "{ 1,3,5,7,9 } is_sorted is = " << is_sorted(sort_list.begin(), sort_list.end()) << endl;
		cout << "{ 1,3,5,7,6 } is_sorted is = " << is_sorted(sort_list2.begin(), sort_list2.end()) << endl;
	}

	// �������㷨  �䶯,�Ķ����ݵ��㷨.
	if (false)
	{
		vector<int> MyList = { 1,2,3,4,5 };

		// copy ��Ҫ�пռ�5��Ԫ��.  ����ѡ��󲿲���
		vector<int> MyList2(5);
		vector<int> MyList3;
		copy(MyList.begin(), MyList.end(), MyList2.begin());
		copy(MyList.begin(), MyList.end(), back_inserter(MyList3));
		PRINT_ELEMENTS(MyList2);
		PRINT_ELEMENTS(MyList3);

		// fill fill_n ��Ҫ��֤�ռ� ���������ֵ
		fill(MyList2.begin(), MyList2.end(), 2);
		fill_n(MyList3.begin(), 3, 0);	// ��N�����޸�ΪT
		PRINT_ELEMENTS(MyList2);
		PRINT_ELEMENTS(MyList3);

		// iotaȫ����ֵ Ϊ��������T T+1 T+2
		PRINT_ELEMENTS(MyList);
		iota(MyList.begin(), MyList.end(), 10);
		cout << "=== after iota, from: 10 ===" << endl;
		PRINT_ELEMENTS(MyList);

		// replace �滻Ԫ�� T->N_T
		PRINT_ELEMENTS(MyList);
		replace(MyList.begin(), MyList.end(), 10, 100);
		cout << "=== after replace, 10 -> 100 ===" << endl;
		PRINT_ELEMENTS(MyList);

	}

	// �Ƴ����㷨 remove unique
	if (false)
	{
		vector<int> MyList = { 1,1,2,2,3,3,4,4,5,5 };
		PRINT_ELEMENTS(MyList);

		// remove�Ƴ�Ԫ�� ���������޸�����������,��Ҫ�Լ�ɾ�����.
		auto pos = remove(MyList.begin(), MyList.end(), 1);
		cout << "remove 1 and erase(pos, end): " <<endl;
		MyList.erase(pos, MyList.end());
		PRINT_ELEMENTS(MyList);

		// �Ƴ��ظ� ����������
		pos = unique(MyList.begin(), MyList.end());
		cout << "unique and erase(pos, end): " << endl;
		MyList.erase(pos, MyList.end());
		PRINT_ELEMENTS(MyList);

	}

	// ����/�������㷨 ��ת ����
	if (false)
	{
		vector<int> MyList = { 1,2,3,4,5,6,7,8,9 };
		PRINT_ELEMENTS(MyList);

		// reverse ��תԪ�ش���
		reverse(MyList.begin(), MyList.end());
		cout << "reverse : ";
		PRINT_ELEMENTS(MyList);

		// random_shuffleͨ������ϴ�� ����������������.
		 random_shuffle(MyList.begin(), MyList.end());
		cout << "random_shuffle : ";
		PRINT_ELEMENTS(MyList);

		// sort  �����㷨. stable_sort��֤���Ԫ����˳�򲻱�
		stable_sort(MyList.begin(), MyList.end());
		cout << "stable_sort : ";
		PRINT_ELEMENTS(MyList);
	}

	// heap�㷨����
	if (false)
	{
		vector<int> MyList = { 1,2,3,4,5,6,7,8,9 };
		PRINT_ELEMENTS(MyList);

		// make_heap ��Ԫ��תΪheap
		make_heap(MyList.begin(), MyList.end());
		cout << "make_heap : ";
		PRINT_ELEMENTS(MyList);

		// pop_heap �����Ԫ���ƶ������λ��.
		pop_heap(MyList.begin(), MyList.end());
		cout << "pop_heap : ";
		PRINT_ELEMENTS(MyList);

		// sort_heap ��heap˳��תΪһ���������.
		make_heap(MyList.begin(), MyList.end());
		sort_heap(MyList.begin(), MyList.end());
		cout << "sort_heap : ";
		PRINT_ELEMENTS(MyList);
	}

}
