//--------------------------------------------------------------------
// 文件名:		C++ Templates
// 内  容:		模(mu)板的学习,测试代码
// 说  明:		
// 创建日期:	2021年12月21日
// 整理日期:	2021年12月21日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "C++ Templates.h"

#include <stdio.h>  
#include <iostream>

using namespace std;

// 模板的一般形式如下:
// template <typename type> ret - type func - name(parameter list)

// 针对每种类型,从模板中产生一个实体(也叫模板的实例化instantiation)
//template<class T>  建议使用typename
template<typename T>
inline T const& max(T const& a, T const& b)
{
	return a > b ? a : b;
}

// 需要指定返回值类型 和 实参类型 (取消返回值的const&修饰)
// 把参数转型为返回类型的过程将会创建一个新的局部临时对象，
// 导致不能通过引用来返回结果。 不可用 inline RT const& 
template<typename RT, typename T>
inline RT rt_max(T const& a, T const& b)
{
	return a > b ? a : b;
}

// 全特化的函数
template<>
inline const char*  rt_max(int const& a, int const& b)
{
	return "nonsupport int vs int";
}

// 手动实例化: 显式实例化指示符（explicit instantiation directive）
template void nonref<int>(int);
template void nonref<double>(double);

// 对外接口
void TestTemplates::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 2 模板函数(参数,演绎和显式指定等) 
	if (0)
	{
		cout << " 2 模板函数(参数,演绎和显式指定等) " << endl;

		// 明确使用::调用全局的max函数,不然会调用STL中的std::max()
		cout << "::max(1,3) = " << ::max(1, 3) << endl;
		cout << "::max(1.1, 3.3) = " << ::max(1.1, 3.3) << endl;

		auto s1 = "ABCDE";
		auto s2 = "abcde";
		cout << "::max(s1, s2) = " << ::max(s1, s2) << endl;

		// 显式指定模板实参的类型,不用通过对调用时的实参来推导类型.
		cout << "::max<double>(1, 3.3) = " << ::max<double>(1, 3.3) << endl;
		cout << "::max<int>(1, 3.3) = " << ::max<int>(1, 3.3) << endl;

		// 虽然没有给出类型,强制使用模板推导. 避免调用非模板的函数max(int, int)
		cout << "::max<>(1, 3) = " << ::max<>(1, 3) << endl;

		// 因为模板是不允许自动类型转化的；
		// ::max(1, 3.3); 编译报错

		// 显式指定返回类型
		cout << "::rt_max<int>(1.1, 3.3) = " << ::rt_max<int>(1.1, 3.3) << endl;
		cout << "::rt_max<int, int>(1.1, 3.3) = " << ::rt_max<int, int>(1.1, 3.3) << endl;
		cout << "::rt_max<double, double>(1.1, 3.3) = " << ::rt_max<double, double>(1.1, 3.3) << endl;
		cout << "::rt_max<double, int>(1.1, 3.3) = " << ::rt_max<double, int>(1.1, 3.3) << endl;

		// 调用特化的模板函数
		const char* restr = ::rt_max<const char*, int>(1.1, 3.3);
		cout << "::rt_max<const char*, int>(1.1, 3.3) = " 
			<< ::rt_max<const char*, int>(1.1, 3.3) << endl;

		/* tips:
		•模板函数为不同的模板实参定义了一个函数家族。
		•当你传递模板实参的时候，可以根据实参的类型来对函数模板进行实例化。
		•你可以显式指定模板参数。 •你可以重载函数模板。
		•当重载函数模板的时候，把你的改变限制在：显式地指定模板参数。
		•一定要让函数模板的所有重载版本的声明都位于它们被调用的位置之前。
		*/
	}

	// 3 类模板
	if (0)
	{
		cout << "3 类模板 " << endl;

		// 使用模板容器
		cout << "模板容器 MyStack<int> stack" << endl;
		MyStack<int> stack;
		stack.push(1);
		stack.push(2);
		stack.push(3);

		// 遍历输出
		while (!stack.empty())
		{
			cout << "stack.top() = " << stack.top() << endl;
			stack.pop();
		}

		stack.push(99);
		
		if (!stack.empty())
		{
			cout << "stack.top() = " << stack.top() << endl;
		}
		else
		{
			cout << "stack is empty" << endl;
		}

		// 捕捉异常
		try
		{
			stack.pop();
			stack.pop();
		}
		catch (std::exception const& ex)
		{
			cout << "std::exception: " << ex.what() << endl;
		}

		// 使用特化的容器
		cout << "特化的容器 MyStack<string> strStack" << endl;
		MyStack<string> strStack;
		strStack.push("a");
		strStack.push("b");
		strStack.push("c");

		// 遍历输出
		while (!strStack.empty())
		{
			cout << "strStack.top() = " << strStack.top() << endl;
			strStack.pop();
		}

		// 使用模板容器-给出容器
		cout << "模板容器 MyStack<double, deque<double>> dequeStack" << endl;
		MyStack<double, deque<double>> dequeStack;
		dequeStack.push(1.1f);
		dequeStack.push(2.1f);
		dequeStack.push(3.1f);

		// 遍历输出
		while (!dequeStack.empty())
		{
			cout << "dequeStack.top() = " << dequeStack.top() << endl;
			dequeStack.pop();
		}

		/*
		•类模板:有一个或多个类型还没有被指定。
		•编译器将会基于该类型来实例化类模板。
		•只有那些被调用的成员函数才会被实例化。
		•可以用某种特定类型特化类模板。
		•可以用某种特定类型局部特化类模板。
		•可以为类模板的参数定义缺省值，这些值还可以引用之前的模板参数。
		*/
	}

	// 4 非类型模板参数
	if (0)
	{
		cout << "4 非类型模板参数 " << endl;
		FixedStack<int, 20> intFStack;

		try
		{
			// 填入和打印
			for (int i = 0; i < 25; i++)
			{
				intFStack.push(i);
				cout << "intFStack.top() = " << intFStack.top() << endl;
			}
		}
		catch (std::exception const& ex)
		{
			cout << "std::exception: " << ex.what() << endl;
		}

		// 非类型的函数模板使用
		int x = 100;
		auto y = addValue<int, 10>(100);
		cout << "addValue<int, 10>(100): " << y << endl;

		/*
		•模板可以具有值模板参数，而不仅仅是类型模板参数。 
		•对于非类型模板参数，你不能使用浮点数、class 类型的对象和
		内部链接对象（例如string）作为实参。*/
	}

	// 5 基础性技巧
	if (0)
	{
		cout << "5 基础性技巧 " << endl;

		// 打印容器
		vector<int> vct{ 1, 2, 3, 4, 5 };
		PrintSTLContainer(vct);

		// 模板子类调用基类
		Derived<int> derived;
		derived.sub_call();

		// 测试零初始化情况
		auto y = addValue<int, 10>(100);
		cout << "addValue<int, 10>(100): " << y << endl;

		// 类型为字符数组
		ref("hello");
		// 类型退化到字符指针
		nonref("hello");

		/*
		•如果要访问依赖于模板参数的类型名称，你应该在类型名称前添加关键字typename。
		•嵌套类和成员函数也可以是模板。
		•赋值运算符的模板版本并没有取代缺省赋值运算符。
		•类模板也可以作为模板参数，我们称之为模板的模板参数。
		•模板的模板实参必须精确地匹配。匹配时并不会考虑“模板的模板实参”的缺省模板实参（如std::deque的allocator）。
		•通过显式调用缺省构造函数，可以确保模板的变量和成员都已经用一个缺省值完成初始化，这种方法对内建类型的变量和成员也适用。
		•对于字符串，在实参演绎过程中，当且仅当参数不是引用时，才会出现数组到指针（array-to-pointer）的类型转换（称为decay）。*/
	}

	// 6 模板细节和模板术语
	if (0)
	{
		cout << " 6 模板细节和模板术语" << endl;

		// 我们把模板的定义也包含在声明模板的头文件里面，即让定义和声明都位于同一个头文件中。

		// 调用手动实例化的模板函数
		nonref(1);
		nonref(1.1f);
		
		// 有一种尝试提高C++编译器诊断信息的技术，它主要是通过在高层模板插入哑代码来实现的，
		// 我们可以参考Jeremy Siek的Concept Check Library（见[BCCL]）
		//——它是Boost库的一部分（见[Boost]）。

		// 类模板(class template)：该类是一个模板
		// 函数模板(function template) 该函数是一个模板

		// 声明（declaration) 是一种 C++构造（construct），
		// 引入（或重新引入）一个名称到某个 C++作用域中。

		// 定义 （definition) 必须提供一对花括号内部的实体。

		// 和全局变量与静态数据成员一样，
		// 在整个程序中，非内联函数和成员函数只能被定义一次。

		// 模板参数是指： T array[N];
		// 位于模板声明或定义内部，关键字template后面所列举的名称（譬如 T, N）。

		// 模板实参是指：ArrayInClass<double,10>
		// 用来替换模板参数的各个对象（如 double,10）。
		// 和模板参数不同的是，模板实参可以有不局限于“标识符名称”（就是有多种类型或值）。
	}
}