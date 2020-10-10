/*!
 * \file STLContainer.cpp
 * \date 2019/01/14 17:24
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief C++11�� ����
 *
 * TODO: long description
 *
 * \note
*/
#include "STLContainer.h"

#include <array>
#include <vector>
#include <string>
#include <list>
#include <forward_list>

#include <iostream>
#include <set>
#include <xfunctional>
#include <map>
#include <utility>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

// �� ��ӡ����
#define PRINT_ELEMENTS(CONTAINER)  cout << "Container "<< #CONTAINER << ": "; \
for (const auto& it : CONTAINER) { cout << it << " " ; }; cout << endl;

// �� ��ӡ����
#define PRINT_MAP_ELEMENTS(CONTAINER)  cout << "Container "<< #CONTAINER << ": "; \
for (const auto& it : CONTAINER) { cout << it.first << "-" << it.second << " "; }; cout << endl;

STLContainer::STLContainer(void)
{
}

STLContainer::~STLContainer(void)
{
}

/////////////////////////////����ӿ�/////////////////////////////////////////////
// NewFeatures
void STLContainer::BeginTest()
{
	// array ����
	if (0)
	{
		// Ԫ�ز�Ϊ0,ע��
		array<int, 10> x;
		cout << x[1] << endl; // �����

		// ͨ��{},���ʼ��Ϊ0
		array<int, 10> x1 = {1, 2, 3, 4};
		PRINT_ELEMENTS(x1);

		// ��ȡ��С
		cout << x1.size() << endl;
		cout << x1.max_size() << endl;

		// ֱ�ӷ��� ������Ƿ����
		cout << x1.front() << endl;
		cout << x1.back() << endl;

	}

	// vector
	if (false)
	{
		vector<string> myVctor;
		myVctor.reserve(10);

		myVctor.push_back("Hello,");
		myVctor.insert(myVctor.end(), { "how", "are", "you", "?" });

		PRINT_ELEMENTS(myVctor);

		cout << "size " << myVctor.size() << endl;	// ��ǰԪ�ظ���
		cout << "capacity " << myVctor.capacity() << endl;	// ��ǰ�ռ�������
		cout << "max_size " << myVctor.max_size() << endl;	// �����ܸ���

		// ֱ���޸�ǰ��,����֤��ȫ
		myVctor.back() = "!";
		myVctor.front() = "Hi,";
		PRINT_ELEMENTS(myVctor);

		myVctor.pop_back();
		myVctor.pop_back();
		PRINT_ELEMENTS(myVctor);

		cout << "size " << myVctor.size() << endl;	// ��ǰԪ�ظ���
		cout << "capacity " << myVctor.capacity() << endl;	// ��ǰ�ռ�������

		// ������������ǰԪ�ظ��� capacity��С��size,but����֤���.
		myVctor.shrink_to_fit();
		cout << "after shrink_to_fit() capacity: " << myVctor.capacity() << endl;

	}

	// list
	if (false)
	{
		list<int> myList;
		myList = { 1,2,3,4,5 };
		myList.push_back(0);
		myList.push_front(10);
		PRINT_ELEMENTS(myList);

		cout << "size " << myList.size() << endl;	// ��ǰԪ�ظ���
		cout << "max_size " << myList.max_size() << endl;	// �����ܸ���

		// �ڲ����� �ٶȿ�
		myList.sort();

		// ��������������
		auto it = myList.cbegin();
		for (; it != myList.cend(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;

		// �ų�ͷ��β
		myList.pop_back();
		myList.pop_front();
		// ��������Ԫ��
		myList.insert(myList.end(), { 2,4,6,8 });
		// �����ת
		myList.sort();
		myList.reverse();
		PRINT_ELEMENTS(myList);

		// ɾ������ 2 Ԫ��
		myList.remove(2);
		PRINT_ELEMENTS(myList);

		// ������С
		myList.resize(6);
		PRINT_ELEMENTS(myList);

		// ���� ��7����
		myList.resize(10, 7);
		PRINT_ELEMENTS(myList);

		// ȥ�������ظ���Ԫ�� ��sort���һ����
		myList.sort();
		myList.unique();
		PRINT_ELEMENTS(myList);
	}

	// forward_list
	if (false)
	{
		forward_list<int> flist1 = { 3,5,7,9 };
		forward_list<int> flist2 = { 2,4,8,6 };
		PRINT_ELEMENTS(flist1);
		PRINT_ELEMENTS(flist2);

		flist1.push_front(0);
		flist1.insert_after(flist1.begin(), 1);
		PRINT_ELEMENTS(flist1);	// 0 1 3 5 7 
		PRINT_ELEMENTS(flist2);

		// ��Ҫ2���������������
		flist2.sort(); // ������ ��һ�����ж�
		flist1.merge(flist2);
		PRINT_ELEMENTS(flist1);
	}

	// set multiset
	if (false)
	{
		set<int, greater<int>> conSet = {1,3,5,7,9};
		conSet.insert({2,4,6,8});
		conSet.insert(5);
		PRINT_ELEMENTS(conSet);

		conSet.erase(3);
		PRINT_ELEMENTS(conSet);

		if (conSet.find(2) != conSet.cend()) 
		{
			cout << "conSet find 2 inside!" << endl;
		}

		if (conSet.count(2) > 0)
		{
			cout << "element 2 count > 0 !" << endl;
		}

		// ��Ϊop��ͬ ����ֱ�ӹ���
		//set<int, less<int>> conSet2(conSet);
		set<int, less<int>> conSet2(conSet.cbegin(), conSet.cend());
		PRINT_ELEMENTS(conSet2);
	}

	// map
	if (false)
	{
		map<string, int>MyMap{  {"a", 1},
								{ "b", 2 },
								{ "c", 3 }};
		PRINT_MAP_ELEMENTS(MyMap);

		MyMap["c"] = 4;
		MyMap["d"] = 5;
		MyMap.erase("b");
		PRINT_MAP_ELEMENTS(MyMap);

		multimap<string, int> Mymultimap{ { "a", 1 },
		{ "b", 2 },
		{ "c", 3 } };
		PRINT_MAP_ELEMENTS(Mymultimap);

		Mymultimap.insert(make_pair("c", 4));
		Mymultimap.insert(make_pair("c", 5));
		Mymultimap.insert(make_pair("b", 22));
		Mymultimap.erase("b");
		PRINT_MAP_ELEMENTS(Mymultimap);
	}

	// unordered_set/map
	if (false)
	{
		unordered_map<string, int>UnorderedMap{ { "a", 1 },
		{ "b", 2 },
		{ "c", 3 } };

		UnorderedMap["c"] = 4;
		UnorderedMap["d"] = 5;
		UnorderedMap.erase("b");
		PRINT_MAP_ELEMENTS(UnorderedMap);

		cout << "UnorderedMap.at(a) = " << UnorderedMap.at("a") << endl;
		cout << "UnorderedMap.bucket_count = " << UnorderedMap.bucket_count() << endl;
		cout << "UnorderedMap.max_bucket_count = " << UnorderedMap.max_bucket_count() << endl;
	}

	// stack LIFO���� ����ȳ� ���Ϊ����Ͱ Ĭ���ڲ�Ϊdeque.
	if (0)
	{
		stack<int> my_stack;
		my_stack.push(3);
		my_stack.push(2);
		my_stack.push(1);
		my_stack.push(4);
		my_stack.push(5);
		
		PRINT_ELEMENTS(my_stack._Get_container());

		// �������ϵĵ�һ��Ԫ��5
		cout << "top and pop: "<< my_stack.top() << endl;
		my_stack.pop();
		PRINT_ELEMENTS(my_stack._Get_container());

		cout << "top and pop: " << my_stack.top() << endl;
		my_stack.pop();
		my_stack.push(6);
		PRINT_ELEMENTS(my_stack._Get_container());
	}

	// Queue FIFO���� �Ƚ��ȳ� ���Ϊ�Ŷ��ϳ� Ĭ���ڲ�Ϊdeque.
	if (0)
	{
		queue<int> my_queue;
		my_queue.push(1);
		my_queue.push(2);
		my_queue.push(3);
		my_queue.push(4);
		my_queue.push(5);

		PRINT_ELEMENTS(my_queue._Get_container());

		// pop ��һ��Ԫ�� 1
		cout << "front and pop: " << my_queue.front() << endl;
		my_queue.pop();
		PRINT_ELEMENTS(my_queue._Get_container());

		// ����������6
		cout << "back is: " << my_queue.back() << endl;
		my_queue.push(6);
		PRINT_ELEMENTS(my_queue._Get_container());
	}

	// priority_queue���� �����ȼ�������,���ṩ�Լ���������
	if (0)
	{
		list<int> tlist = { 2,4,6,8 };
		priority_queue<int> my_priority_queue(tlist.begin(), tlist.end());

		my_priority_queue.push(5);
		my_priority_queue.push(3);
		my_priority_queue.push(1);

		// ������˳���ӡ���Ƴ�
		while (!my_priority_queue.empty())
		{
			cout << "top(remove latter) is: " << my_priority_queue.top() << endl;
			my_priority_queue.pop();
		}
	}
	
	return;
}
