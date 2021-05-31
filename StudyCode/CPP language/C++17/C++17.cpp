//--------------------------------------------------------------------
// 文件名:		TestC17
// 内  容:		
// 说  明:		
// 创建日期:	2021年5月7日
// 整理日期:	2021年5月7日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "C++17.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

#include <iostream>
#include<filesystem>
using namespace std;

// 自动推导返回类型
template<typename T>
auto addByType(const T& t)
{
	// 条件判断中 表达式编译为常量结果
	if constexpr(is_integral<T>::value)
	{
		return t + 1;
	}
	else
	{
		return t;
	}
}


// 强制实例化
template class vector<int>;
// 不实例化
extern template class vector<bool>;

class Base
{
public:
	int v1=0, v2=0;
	Base() { v1 = 1; };

	// = delete 声明拒绝编译器生成构造
	Base& operator=(const Base&) = delete;

	// 委托给无参构造，再执行
	Base(int v) :Base()
	{
		v2 = v;
	}

	virtual int foo(int i)
	{
		return i;
	}
};

// final明确终止继续继承和重载
class SubClass final:public Base
{
public:
	// 继承基类的构造函数
	using Base::Base;

	// override 明确重载
	virtual int foo(int i) override
	{
		return i;
	}

	// override 明确重载报错，没有重写任何基类方法
	// virtual int foo2(int i) override;
};

// 不可派生
// class SubClass2 :public SubClass;

// 强类型枚举
enum class MyEnum : unsigned int
{
	value1,
	value2,
	// 可出现相等
	value3 = 100,
	value4 = 100
};

// 对外接口
void TestC17::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// if中存放临时变量 条件编译为常量 构造 委托和继承
	if (0)
	{
		/* / if中存放临时变量 需要打开 C++语言标准  /std： c + + 17
		vector<int> vct = { 1,2,3,4 };
		if (const vector<int>::iterator it = find(vct.begin(), vct.end(), 2); it!= vct.end())
		{
			*it = 1;
		} */

		// 结构化绑定
		// tuple<int,double,string> [x,y,z] = make_tuple(1, 2.3, "123");
		// cout << x << y << z << endl;

		// 让判断条件编译为常量，效率更好
		cout << "addByType 1 = " << addByType(1) << endl;
		cout << "addByType 1.1 = " << addByType(1.1f) << endl;
		
		// 连续的>>
		vector<int> vctInt = { 1,2,3 };
		vector<vector<int>> vctVctInt;

		// 构造 委托和继承
		Base base(2); // 使用委托构造
		cout << "base.v1 = " << base.v1 << endl;
		cout << "base.v2 = " << base.v2 << endl;
		SubClass sub(3); // 用基类的构造函数
		cout << "sub.v1 = " << sub.v1 << endl;
		cout << "sub.v2 = " << sub.v2 << endl;
	}

	// override  final delete
	if (0)
	{
		// override 和 final 见上类里
		
		// = delete 声明拒绝编译器生成构造

		// 强类型枚举 不可和数字转换
		MyEnum e1 = MyEnum::value1;
		MyEnum e2 = MyEnum::value2;
		MyEnum e3 = MyEnum::value3;
		MyEnum e4 = MyEnum::value4;

		// 必须强转
		cout << "e1 == " << (unsigned int)e1 << endl;
		cout << "e2 == " << (unsigned int)e2 << endl;
		cout << "e3 == " << (unsigned int)e3 << endl;

		// e1 == 0 错误，不可直接判断

		// 枚举之间，如果值相同，可以比较
		if (e3 == e4)
		{
			cout << "e3 == e4 " << endl;
		}

		// case 标签值已经出现在此开关 所在行数 : 155 
		switch (MyEnum::value3)
		{
		case MyEnum::value3:
			cout << "switch MyEnum::value3" << endl;
			break;
		// case MyEnum::value4: 编译不过,因为值和value3相等
			cout << "switch MyEnum::value4" << endl;
			break;
		default:
			break;
		}
	}

	// std::filesystem
	if (0)
	{
		// path 类：说白了该类只是对字符串（路径）进行一些处理，这也是文件系统的基石。

		// directory_entry 类：功如其名，文件入口，这个类才真正接触文件。 

		// directory_iterator 类：获取文件系统目录中文件的迭代器容器，其元素为 directory_entry对象（可用于遍历目录）

		// file_status 类：用于获取和修改文件（或目录）的属性

		/* path str("C:\\Windows");
		//必须先检测目录是否存在才能使用文件入口.
		if (!exists(str))
		{
			return 1;
		}

		//文件入口
		directory_entry entry(str);		

		//这里用了C++11的强枚举类型
		if (entry.status().type() == file_type::directory)	
			cout << "该路径是一个目录" << endl;

		//文件入口容器
		directory_iterator list(str);	        

		//通过文件入口（it）获取path对象，再得到path对象的文件名，将之输出
		for (auto& it : list)
		{
			cout << it.path().filename() << endl;
		} */
	}
}
