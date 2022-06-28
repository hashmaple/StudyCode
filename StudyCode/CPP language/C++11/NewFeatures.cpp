#include "C++11.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

// NewFeatures
void NewFeatures::BeginTest()
{
	cout << __FILE__ << "  " <<  __FUNCTION__ << endl;

	// nullptr auto range-based for move
	if (0)
	{
		// nullptr 基础类型 不会转为整形,会转为各种指针类型.
		// 可以用来避开NULL为0时候，调用int类型的重载函数
		int* p = nullptr;

		// 判断是否同类型
		if (is_same<decltype(p), int*>::value)
		{
			cout << "decltype(p) ==  int*" << endl;
		}

		// constexpr 常量表达式 用于数组初始化等
		constexpr int len = 1 + 1;
		char arr[len];

		// auto 类型自动推导. 原先意义为某变量是局部的.
		auto i = 20;

		// 一致性的初始化 都可以使用大括号
		int j{}; // j = 0 会初始化
				 // int k; 未初始化编译不通过
		int values[]{ 1,2,3 };
		vector<int> v = { 2,3,4,5,6 };
		vector<string> vstr = { "zsq", "kyo" };

		// range-based for循环
		for (auto element : v) {}			   // 会赋值给element,产生一份副本
		for (auto& element : v) { ++element; } // element是引用,可以修改
		for (const auto& element : v) {}	   // element是常量引用,不可修改

		// std::move() 搬迁语义 适用于变量搬迁后不再使用的情形.
		vector<int> v_int1{ 1,2,3,4 };
		vector<int> v_int2(2);

		v_int2 = move(v_int1); // 直接移动内容过来,减少了一次复制消耗. 

		v_int2.size(); // 4
		v_int1.size(); // 0 处于未指定,但有效的状态 move后不用此容器,用法正确!
	}
	
	// lambda
	if (0)
	{
		int lambda_i = 8;
		int lambda_j = 8;

		// l=函数对象 []=获取上下文变量     ()输入参数        ->返回值
		auto l = [lambda_i, &lambda_j](int i, const string& s) -> int
		{
			cout << "lambda functon call! input args i-s = " << i << s << endl;
			cout << "lambda_i = " << lambda_i << endl;
			cout << "lambda_j = " << lambda_j << endl;

			lambda_j++;

			return 9527;
		};

		// 先调用l函数,在输出返回值
		cout << "lambda call return = " << l(1, "maple") << endl;
		cout << "lambda_j = " << lambda_j << endl;	// 在函数传递引用后已经被修改
	}

	// 智能指针 shared,unique,weak
	if (0)
	{
		// shared_ptr:记录数量是一种智能指针， 它能够记录多少个 shared_ptr 共同指向一个对象， 
		// 从而消除显示的调用 delete ， 当引用计数变为零的时候就会将对象自动删除
		auto shared_pointer = make_shared<int>(10);
		cout << "shared_pointer = " << *shared_pointer << endl;

		// 获取原始的指针
		auto original_pointer = shared_pointer.get();
		cout << "shared_pointer = " << shared_pointer.get() << endl;
		cout << "original_pointer = " << original_pointer << endl;

		// 查看对象的引用计数
		auto shared_pointer2 = shared_pointer;
		cout << "use_count = " << shared_pointer.use_count() << endl;

		// 释放 减少一个数量
		shared_pointer2.reset();
		cout << "use_count = " << shared_pointer.use_count() << endl;

		// 全释放后 再查看原始指针数据已重置
		cout << "original_pointer = " << *original_pointer << endl;
		shared_pointer.reset();
		cout << "original_pointer = " << *original_pointer << endl;


		// unique_ptr 独占的智能指针， 它禁止其他智能指针与其共享同一个对象，从而保证代码的安全
		auto unique_pointer = make_unique<int>(20);
		cout << "unique_pointer = " << *unique_pointer << endl;

		// 非法的获取
		//auto unique_pointer2 = unique_pointer;

		// 可使用move转移 转移后旧指针失效
		auto unique_pointer2 = move(unique_pointer);
		cout << "unique_pointer = " << *original_pointer << endl;
		cout << "unique_pointer2 = " << *unique_pointer2 << endl;

		// 释放控制权，不释放内存
		auto p = unique_pointer2.release();
		cout << "p = release() = " << *p << endl;

		// 释放内存
		unique_pointer2.reset();
		// 释放内存
		unique_pointer2 == nullptr;

		// weak_ptr 配合shared_ptr而引入，解决shared_ptr的相互引用
		// 不拥有资源的所有权，不能直接使用。无 * 和 ->
		// 通过lock获取，和expired检测是否过期。
		auto shared_p = make_shared<string>("This is shared_ptr!");

		// 不增加计数
		weak_ptr<string> weak_p = shared_p;

		// 没有过期，输出内容
		if (!weak_p.expired())
		{
			weak_p.lock();
			cout << "*weak_p.lock() = " << *weak_p.lock() << endl;
		}

		// 清空
		weak_p.reset();
	}

	// dynamic_cast static_cast const_cast
	if (false)
	{
		// static_cast 用于数值类型转换 或类的上行下行转换
		int i = static_cast<int>(1.1f);
		
		// 类的上行下行转换
		auto pSon = make_shared<SonNewFeatures>();
		auto pFaClass = static_cast<NewFeatures*>(pSon.get());	// 子转父 可以
		auto pSonClass = static_cast<SonNewFeatures*>(pFaClass);// 父转子 不推荐
		cout << "pFaClass virFunc = " << pFaClass->virFunc() << endl;
		cout << "pSonClass virFunc = " << pSonClass->virFunc() << endl;
		
		// dynamic_cast 类之间的转换 至少包含1个虚函数
		pFaClass = dynamic_cast<NewFeatures*>(pSonClass);
		pSonClass = dynamic_cast<SonNewFeatures*>(pFaClass);

		// const_cast 脱const
		string s1 = "abcdefg";
		char* str1 = const_cast<char*>(s1.c_str());
		str1[1] = 0;	// 非常危险！尽量别用

		// 导致 输出只有a， 长度仍然为7
		cout << "s1 = " << s1.c_str() << endl;
		cout << "s1.size = " << s1.size() << endl;
		cout << "str1 = " << str1 << endl;
	}

	// 其他杂项 字面量R
	if (0)
	{
		// 包含特殊字符的字符串
		std::string str = R"(C:\File\To\Path)";
		std::cout << str << std::endl;
	}

	return;
}
