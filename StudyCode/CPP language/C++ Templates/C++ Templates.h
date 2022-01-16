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
	return x + ADDVAL;
}

class MyInt 
{ 
public: 
	MyInt(int i); 
}; 

MyInt operator– (MyInt const&); 
bool operator> (MyInt const&, MyInt const&); 

typedef MyInt Int; 

template <typename T> 
void f(T i)
{
	if (i > 0)
	{
		g(-i);
	}
}

void g(Int) 
{ 
	f<Int>(42);
} 
