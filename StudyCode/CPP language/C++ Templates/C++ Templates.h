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

class TestTemplates
{
public:
	TestTemplates(void) {};
	~TestTemplates(void) {};

	// 对外接口
	void BeginTest();
};

//template <typename T> 等同
template <class T>
class MyStack
{
private:
	std::vector<T> elems;

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

	bool empty() const
	{
		return elems.empty();
	}
};

