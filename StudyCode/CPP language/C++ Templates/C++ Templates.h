//--------------------------------------------------------------------
// 文件名:		C++ Templates
// 内  容:		
// 说  明:		
// 创建日期:	2021年12月21日
// 整理日期:	2021年12月21日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#pragma once
#include <vector>
#include <stdexcept>
#include <deque>

class TestTemplates
{
public:
	TestTemplates(void) {};
	~TestTemplates(void) {};

	// 对外接口
	void BeginTest();
};

//template <typename T> 等同
template <class T, class CONT = std::vector<T>>
class MyStack
{
private:
	CONT elems;

public:
	void push(T const& value)
	{
		elems.push_back(value);
	}

	void pop()
	{
		if (elems.empty())
		{
			throw std::out_of_range("MyStack<>::pop: empty stack");
		}
		elems.pop_back();
	}

	T top() const
	{
		if (elems.empty())
		{
			throw std::out_of_range("MyStack<>::top: empty stack");
		}
		return elems.back();
	}

	// 被调用,才会实例化函数代码
	bool empty() const
	{
		return elems.empty();
	}

	// 某些类模板中的成员函数会使用operator<来排序元素；
	// 如果不调用这些“使用operator<的”成员函数，
	// 那么对于没有定义operator<的类型，也可以被用来实例化该类模板。
};

// 模板的特化
template <>
class MyStack<std::string>
{
private:
	// 改为deque管理内部元素
	std::deque<std::string> elems;

public:
	void push(std::string const& value)
	{
		elems.push_back(value);
	}

	void pop()
	{
		if (elems.empty())
		{
			throw std::out_of_range("MyStack<std::string>::pop: empty stack");
		}
		elems.pop_back();
	}

	std::string top() const
	{
		if (elems.empty())
		{
			throw std::out_of_range("MyStack<>::top: empty stack");
		}
		return elems.back();
	}

	// 被调用,才会实例化函数代码
	bool empty() const
	{
		return elems.empty();
	}
};


// 非类型的类模板(指定数组的大小)
template <class T, int MAXSIZE>
class FixedStack
{
private:
	T elems[MAXSIZE] = {};
	int numElems = 0;

public:
	void push(T const& value)
	{
		if (numElems >= MAXSIZE)
		{
			throw std::out_of_range("FixedStack is full");
		}
		elems[numElems] = value;
		++numElems;
	}

	void pop()
	{
		if (numElems <= 0)
		{
			throw std::out_of_range("FixedStack is empty");
		}

		--numElems;
	}

	T top() const
	{
		if (numElems <= 0)
		{
			throw std::out_of_range("FixedStack is empty");
		}
		return elems[numElems-1];
	}

	// 被调用,才会实例化函数代码
	bool empty() const
	{
		return numElems == 0;
	}
};

// 非类型的函数模板(浮点类型和类对象,不可做参数)
template<typename T, int ADDVAL>
T addValue(T const& x)
{
	// 初始化
	T emptyT = T();

	return x + ADDVAL + emptyT;
}

// 打印STL容器的元素 类型说明
template<typename T>
void PrintSTLContainer(T const& container)
{
	cout << "PrintSTLContainer begin" << endl;

	// typename 说明:模板内部的类型,而非静态成员
	typename T::const_iterator it = container.begin();

	// auto 可以直接使用,YYOY.
	//auto it = container.begin();

	for (; it != container.end(); ++it)
	{
		cout << *it << endl;
	}

	cout << "PrintSTLContainer end" << endl;
}

// 模板基类
template<typename T>
class Base
{
private:
	T m_value;
public:
	void exit(){cout << "Base:base_call  " << endl;}
};

// 模板子类
template<typename T>
class Derived:Base<T>
{
private:
	T m_value;
public:
	void sub_call()
	{ 
		exit(); // 易混淆
		this->exit(); // 清晰
		Base<T>::exit(); // 清晰
		cout << "Derived:sub_call  " << endl; 
	}
};

// decay 退化
template <typename T>
void ref(T const& x) 
{ 
	std::cout << "x in ref(T const&): " << typeid(x).name() << '\n';
} 

/*对于非引用类型的参数，在实参演绎的过程中，
会出现数组到指针（array-to-pointer）的类型转换
（这种转型通常也被称为decay）。*/
template <typename T> 
void nonref(T x) 
{ 
	std::cout << "x in nonref(T): " << typeid(x).name() << '\n'; 
}