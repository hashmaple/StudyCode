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

// 对外接口
void TestTemplates::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// chapter 2 模板函数(参数,演绎和显式指定等) 
	if (0)
	{
		cout << "chapter 2 模板函数(参数,演绎和显式指定等) " << endl;

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

	// chapter 3 类模板
	if (0)
	{
		cout << "chapter 3 类模板 " << endl;

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

	// chapter 4 非类型模板参数
	if (0)
	{
		cout << "chapter 4 非类型模板参数 " << endl;
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

	// chapter 5 基础性技巧
	if (1)
	{
		cout << "chapter 4 非类型模板参数 " << endl;

	}
}