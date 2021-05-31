/*!
 * \file GeneralUtilities.cpp
 * \date 2018/12/26 11:56
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief C++ 标准库中的通用工具
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


/////////////////////////////对外接口/////////////////////////////////////////////
// GeneralUtilities
void GeneralUtilities::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// pair 2个value视为一个单元
	if (false)
	{
		pair<int, string> p1{ 1, "no1" };
		cout << " p1.first = " << p1.first << " second = " << p1.second << endl;
		cout << " get<0>(p1) = " << get<0>(p1) << " get<1>(p1) = " << get<1>(p1) << endl;

		auto b = make_pair(1, string{ "no1" }) == p1;
		cout << "make_pair() == p1 1 or 0 ? " << b << endl;
	}
	

	// tuple 元组 不定数的数组,支持不同类型 make_tuple get tie关键三个函数
	if (0)
	{
		// 定义
		tuple<int, int, string> t1{ 1, 2, "no1" };
		// 类型推导
		auto t2 = make_tuple(2, 4, "mike");

		// 输出信息
		cout << "tuple  get<0>(t1) = " << get<0>(t1) << endl;
		cout << "tuple  get<1>(t1) = " << get<1>(t1) << endl;
		cout << "tuple  get<2>(t1) = " << get<2>(t1) << endl;

		// 拆包
		int n1, n2;
		string name;
		tie(n1, n2, name) = t1;
		cout << "n1 = " << n1 << endl;
		cout << "n2 = " << n2 << endl;
		cout << "name = " << name << endl;

		// 合并
		auto new_t = tuple_cat(t1, t2);

		// 获取元组长度 (decltype 返回操作数的数据类型)
		size_t sz = tuple_size<decltype(new_t)>::value;
		cout << "tuple_size = " << sz << endl;
	}
	
	// shared_ptr 共享式拥有指针
	if (false)
	{
		shared_ptr<string> p1 = make_shared<string>("maple");
		shared_ptr<string> p2 = p1;	// p2和p1是指向一个string对象.
		*p1 = "hello maple";	// p1 p2都会被修改

		cout << "使用*p1: " + *p1 << " 查看拥有者数量 " << p1.use_count() << endl;

		shared_ptr<string> p3(new string("Mike"), [](string* p)
		{
			cout << "p3 auto dele will call here! " << *p << endl;
			delete p;
		});

		// 离开时,P3会触发自己的deleter
		*p3 = "hello " + *p3;
	}

	// weak_ptr 弱智能指针对象 指向由一个shared_ptr管理的智能指针
	if (false)
	{
		weak_ptr<string> wp;

		{
			shared_ptr<string> p = make_shared<string>("hello world!\n");
			wp = p; //weak_ptr对象也绑定到shared_ptr所指向的对象

			shared_ptr<string> p2 = wp.lock();	// 通过lock来给新的shared_ptr
				
			cout << "use_count: " << wp.use_count() << endl;

		}

		//这里p已经析构，其所指的对象也析构了，因此输出是0
		cout << "use_count: " << wp.use_count() << endl;

		// 主动释放
		wp.reset();
	}

	// unique_ptr 持有对对象的独有权 销毁时会自动dele实际指针对象
	if (false)
	{
		std::unique_ptr<int> up1(new int(11));   // 无法复制的unique_ptr
		// unique_ptr<int> up2 = up1;			// err, 不能通过编译
		std::cout << *up1 << std::endl;   // 11

		std::unique_ptr<int> up3 = std::move(up1);    // 现在p3是数据的唯一的unique_ptr

		std::cout << *up3 << std::endl;   // 11
		//std::cout << *up1 << std::endl;   // err, 运行时错误
		
		up3.reset();            // 显式释放内存
		up1.reset();            // 不会导致运行时错误
		std::cout << up3.get() << std::endl;   // 打印数据指针

		std::unique_ptr<int> up4(new int(22));   // 无法复制的unique_ptr
		up4.reset(new int(44)); //"绑定"动态对象
		std::cout << *up4 << std::endl; // 44

		up4 = nullptr;	//显式销毁所指对象，同时智能指针变为空指针。与up4.reset()等价

		std::unique_ptr<int> up5(new int(55));
		int *p = up5.release(); //只是释放控制权，不会释放内存

		cout << up5.get() << endl; // 内部指针为空了
		cout << *p << std::endl;
		delete p; //释放堆区资源
	}

	// 数值的极限
	if (false)
	{
		// 各个类型的大小
		cout << numeric_limits<bool>::min() << endl;
		cout << numeric_limits<bool>::max() << endl;
		cout << numeric_limits<int>::min() << endl;
		cout << numeric_limits<int>::max() << endl;
		cout << numeric_limits<short>::max() << endl;
		cout << numeric_limits<double>::min() << endl;
		cout << numeric_limits<double>::max() << endl;

		// type trait 类型识别 可识别整形,指针,函数,类,枚举.
		TypeTrait(int(3));
		TypeTrait(double(3));

		// min max minmax使用
		cout << "min({ 1,2,3,4,5 }) " << min({ 1,2,3,4,5 }) << endl;
		cout << "max({ 1,2,3,4,5 }) " << max({ 1,2,3,4,5 }) << endl;
		cout << "minmax({ 1,2,3,4,5 }) min = " << minmax({ 1,2,3,4,5 }).first << endl;
		cout << "minmax({ 1,2,3,4,5 }) max = " << minmax({ 1,2,3,4,5 }).second << endl;

		// swap 交换变量
		int i = 1;
		int j = 2;
		swap(i, j);
		cout << i << j << endl;

		// 当前时间
		auto tp = std::chrono::system_clock::now();
		auto cur_time = std::chrono::system_clock::to_time_t(tp);
		char time[128];
		ctime_s(time, 128, &cur_time);
		std::cout << time << std::endl;
		
		// 时间跨度
		auto begin = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		{
			int *p = new int(i);
			delete p;
		}
		auto end = std::chrono::steady_clock::now();
		auto diff = (end - begin).count(); // end-begin得到一个duration类型
		std::cout << "duration cost time is " << diff << std::endl;
	}

}

// 多类型可以识别
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



