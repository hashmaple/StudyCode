/*!
 * \file GeneralUtilities.cpp
 * \date 2018/12/26 11:56
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief C++ ��׼���е�ͨ�ù���
 *
 * TODO: long description
 *
 * \note
*/
#include "GeneralUtilities.h"
#include <utility>
#include <string>
#include <iostream>
#include <tuple>
#include <memory>
#include <limits>
#include <stdlib.h>
#include <algorithm>
#include <chrono>

using namespace std;

GeneralUtilities::GeneralUtilities(void)
{
}

GeneralUtilities::~GeneralUtilities(void)
{
}


/////////////////////////////����ӿ�/////////////////////////////////////////////
// GeneralUtilities
void GeneralUtilities::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// pair 2��value��Ϊһ����Ԫ
	if (false)
	{
		pair<int, string> p1{ 1, "no1" };
		cout << " p1.first = " << p1.first << " second = " << p1.second << endl;
		cout << " get<0>(p1) = " << get<0>(p1) << " get<1>(p1) = " << get<1>(p1) << endl;

		auto b = make_pair(1, string{ "no1" }) == p1;
		cout << "make_pair() == p1 1 or 0 ? " << b << endl;
	}
	

	// tuple Ԫ�� ������������,֧�ֲ�ͬ���� make_tuple get tie�ؼ���������
	if (0)
	{
		// ����
		tuple<int, int, string> t1{ 1, 2, "no1" };
		// �����Ƶ�
		auto t2 = make_tuple(2, 4, "mike");

		// �����Ϣ
		cout << "tuple  get<0>(t1) = " << get<0>(t1) << endl;
		cout << "tuple  get<1>(t1) = " << get<1>(t1) << endl;
		cout << "tuple  get<2>(t1) = " << get<2>(t1) << endl;

		// ���
		int n1, n2;
		string name;
		tie(n1, n2, name) = t1;
		cout << "n1 = " << n1 << endl;
		cout << "n2 = " << n2 << endl;
		cout << "name = " << name << endl;

		// �ϲ�
		auto new_t = tuple_cat(t1, t2);

		// ��ȡԪ�鳤�� (decltype ���ز���������������)
		size_t sz = tuple_size<decltype(new_t)>::value;
		cout << "tuple_size = " << sz << endl;
	}
	
	// shared_ptr ����ʽӵ��ָ��
	if (false)
	{
		shared_ptr<string> p1 = make_shared<string>("maple");
		shared_ptr<string> p2 = p1;	// p2��p1��ָ��һ��string����.
		*p1 = "hello maple";	// p1 p2���ᱻ�޸�

		cout << "ʹ��*p1: " + *p1 << " �鿴ӵ�������� " << p1.use_count() << endl;

		shared_ptr<string> p3(new string("Mike"), [](string* p)
		{
			cout << "p3 auto dele will call here! " << *p << endl;
			delete p;
		});

		// �뿪ʱ,P3�ᴥ���Լ���deleter
		*p3 = "hello " + *p3;
	}

	// weak_ptr ������ָ����� ָ����һ��shared_ptr���������ָ��
	if (false)
	{
		weak_ptr<string> wp;

		{
			shared_ptr<string> p = make_shared<string>("hello world!\n");
			wp = p; //weak_ptr����Ҳ�󶨵�shared_ptr��ָ��Ķ���

			shared_ptr<string> p2 = wp.lock();	// ͨ��lock�����µ�shared_ptr
				
			cout << "use_count: " << wp.use_count() << endl;

		}

		//����p�Ѿ�����������ָ�Ķ���Ҳ�����ˣ���������0
		cout << "use_count: " << wp.use_count() << endl;

		// �����ͷ�
		wp.reset();
	}

	// unique_ptr ���жԶ���Ķ���Ȩ ����ʱ���Զ�deleʵ��ָ�����
	if (false)
	{
		std::unique_ptr<int> up1(new int(11));   // �޷����Ƶ�unique_ptr
		// unique_ptr<int> up2 = up1;			// err, ����ͨ������
		std::cout << *up1 << std::endl;   // 11

		std::unique_ptr<int> up3 = std::move(up1);    // ����p3�����ݵ�Ψһ��unique_ptr

		std::cout << *up3 << std::endl;   // 11
		//std::cout << *up1 << std::endl;   // err, ����ʱ����
		
		up3.reset();            // ��ʽ�ͷ��ڴ�
		up1.reset();            // ���ᵼ������ʱ����
		std::cout << up3.get() << std::endl;   // ��ӡ����ָ��

		std::unique_ptr<int> up4(new int(22));   // �޷����Ƶ�unique_ptr
		up4.reset(new int(44)); //"��"��̬����
		std::cout << *up4 << std::endl; // 44

		up4 = nullptr;	//��ʽ������ָ����ͬʱ����ָ���Ϊ��ָ�롣��up4.reset()�ȼ�

		std::unique_ptr<int> up5(new int(55));
		int *p = up5.release(); //ֻ���ͷſ���Ȩ�������ͷ��ڴ�

		cout << up5.get() << endl; // �ڲ�ָ��Ϊ����
		cout << *p << std::endl;
		delete p; //�ͷŶ�����Դ
	}

	// ��ֵ�ļ���
	if (false)
	{
		// �������͵Ĵ�С
		cout << numeric_limits<bool>::min() << endl;
		cout << numeric_limits<bool>::max() << endl;
		cout << numeric_limits<int>::min() << endl;
		cout << numeric_limits<int>::max() << endl;
		cout << numeric_limits<short>::max() << endl;
		cout << numeric_limits<double>::min() << endl;
		cout << numeric_limits<double>::max() << endl;

		// type trait ����ʶ�� ��ʶ������,ָ��,����,��,ö��.
		TypeTrait(int(3));
		TypeTrait(double(3));

		// min max minmaxʹ��
		cout << "min({ 1,2,3,4,5 }) " << min({ 1,2,3,4,5 }) << endl;
		cout << "max({ 1,2,3,4,5 }) " << max({ 1,2,3,4,5 }) << endl;
		cout << "minmax({ 1,2,3,4,5 }) min = " << minmax({ 1,2,3,4,5 }).first << endl;
		cout << "minmax({ 1,2,3,4,5 }) max = " << minmax({ 1,2,3,4,5 }).second << endl;

		// swap ��������
		int i = 1;
		int j = 2;
		swap(i, j);
		cout << i << j << endl;

		// ��ǰʱ��
		auto tp = std::chrono::system_clock::now();
		auto cur_time = std::chrono::system_clock::to_time_t(tp);
		char time[128];
		ctime_s(time, 128, &cur_time);
		std::cout << time << std::endl;
		
		// ʱ����
		auto begin = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		{
			int *p = new int(i);
			delete p;
		}
		auto end = std::chrono::steady_clock::now();
		auto diff = (end - begin).count(); // end-begin�õ�һ��duration����
		std::cout << "duration cost time is " << diff << std::endl;
	}

}

// �����Ϳ���ʶ��
template <typename T>
void GeneralUtilities::TypeTrait(T val)
{
	bool bIntType = is_integral<T>();
	if (bIntType)
	{
		cout << "val is_integral" << endl;
	}
	else
	{
		cout << "is_floating_point " << is_floating_point<T>() << endl;
	}
}



