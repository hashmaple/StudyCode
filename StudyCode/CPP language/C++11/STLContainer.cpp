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
#include "C++11.h"

#include <array>
#include <vector>
#include <string>
#include <list>
#include <forward_list>

#include <iostream>
#include <set>
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

/////////////////////////////����ӿ�/////////////////////////////////////////////
// NewFeatures
void STLContainer::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// array ���� �̶���С. ��ȡ,�жϵȸ��Ѻ�
	if (0)
	{
		// Ԫ�ز�Ϊ0,ע��
		array<int, 10> ArrayInt = {};

		// ֧��for_range,�ڲ����ݲ�Ϊ0
		for (auto& i : ArrayInt)
		{
			cout << "ArrayInt element = " << i << endl;
		}

		// ͨ��{},���ʼ��Ϊ0
		array<int, 10> x1 = {1,2,3,4,5,9,8,7,6,0};
		PRINT_ELEMENTS(x1);

		// ͨ��sort+lambda����
		sort(x1.begin(), x1.end(), [](int a, int b) {return b < a; });
		PRINT_ELEMENTS(x1);
		
		// Ĭ������ ����
		sort(x1.begin(), x1.end());
		PRINT_ELEMENTS(x1);

		// ��ȡ��С
		cout << x1.size() << endl;
		cout << x1.max_size() << endl;

		// ֱ�ӷ��� Ԫ��Ϊ�ձ���,Ҫ�жϷǿ�
		array<int, 0> x2;
		if (x2.empty())
		{
			cout << x2.front() << endl;
			cout << x2.back() << endl;
		}
	}

	// vector
	if (false)
	{
		// ƫ�ػ� template <class _Alloc>	class vector<bool, _Alloc>;
		vector<bool> boolVctor{1,0,0,false,0,true};
		PRINT_ELEMENTS(boolVctor);

		// c/c++ ���������: /Zc:__cplusplus- ������ȷ��ʶ
		cout << __cplusplus << endl;

		// ����
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

		// ���췽ʽ
		vector<int> intVct1(3); // 0 0 0
		vector<int> intVct2(3, 1); // 1 1 1
		// ��ʼ���б�֧��
		vector<int> intVct3{ 1,2,3 }; // 1,2,3
		vector<int> intVct4 = { 10,20,30 }; // 10,20,30

		vector<int> intVct[3]{ {1, 1}, {1, 2}, {1, 3} }; // 3��vct
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

	// unordered_set/map hash_map�������汾 ��ѯΪ����ʱ�� HASH��������
	// �ԱȲο�:https://blog.csdn.net/stpeace/article/details/81283650
	if (0)
	{
		unordered_map<string, int>UnorderedMap{ { "a", 1 },
		{ "b", 2 },
		{ "c", 3 } };
		
		UnorderedMap["c"] = 4;
		UnorderedMap["d"] = 5;
		PRINT_MAP_ELEMENTS(UnorderedMap);

		UnorderedMap.erase("b");

		cout << "UnorderedMap.at(a) = " << UnorderedMap.at("a") << endl;
		cout << "UnorderedMap.bucket_count = " << UnorderedMap.bucket_count() << endl;
		cout << "UnorderedMap.max_bucket_count = " << UnorderedMap.max_bucket_count() << endl;

		// �Զ���KEY���� ���ṩhash����
		unordered_map<pair<int, int>, int> UnordMapPairs;
		UnordMapPairs[pair<int, int>(1, 1)] = 2;
		UnordMapPairs[pair<int, int>(2, 2)] = 4;

		for (auto& it : UnordMapPairs)
		{
			cout << "UnordMapPairs it.first.first = " << it.first.first << endl;
			cout << "UnordMapPairs it.first.second = " << it.first.second << endl;
			cout << "UnordMapPairs it.first.second = " << it.second << endl;
		}
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
		

		// �������ϵĵ�һ��Ԫ��5
		cout << "top and pop: "<< my_stack.top() << endl;
		my_stack.pop();

		cout << "top and pop: " << my_stack.top() << endl;
		my_stack.pop();
		my_stack.push(6);
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


		// pop ��һ��Ԫ�� 1
		cout << "front and pop: " << my_queue.front() << endl;
		my_queue.pop();

		// ����������6
		cout << "back is: " << my_queue.back() << endl;
		my_queue.push(6);
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
