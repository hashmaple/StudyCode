//--------------------------------------------------------------------
// �ļ���:		C++ Templates
// ��  ��:		
// ˵  ��:		
// ��������:	2021��12��21��
// ��������:	2021��12��21��
// ������:		Maple(������)
//--------------------------------------------------------------------
#pragma once
#include <vector>
#include <stdexcept>

class TestTemplates
{
public:
	TestTemplates(void) {};
	~TestTemplates(void) {};

	// ����ӿ�
	void BeginTest();
};

//template <typename T> ��ͬ
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

