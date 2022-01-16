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
#include <deque>

class TestTemplates
{
public:
	TestTemplates(void) {};
	~TestTemplates(void) {};

	// ����ӿ�
	void BeginTest();
};

//template <typename T> ��ͬ
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

	// ������,�Ż�ʵ������������
	bool empty() const
	{
		return elems.empty();
	}

	// ĳЩ��ģ���еĳ�Ա������ʹ��operator<������Ԫ�أ�
	// �����������Щ��ʹ��operator<�ġ���Ա������
	// ��ô����û�ж���operator<�����ͣ�Ҳ���Ա�����ʵ��������ģ�塣
};

// ģ����ػ�
template <>
class MyStack<std::string>
{
private:
	// ��Ϊdeque�����ڲ�Ԫ��
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

	// ������,�Ż�ʵ������������
	bool empty() const
	{
		return elems.empty();
	}
};


// �����͵���ģ��(ָ������Ĵ�С)
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

	// ������,�Ż�ʵ������������
	bool empty() const
	{
		return numElems == 0;
	}
};

// �����͵ĺ���ģ��(�������ͺ������,����������)
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

MyInt operator�C (MyInt const&); 
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
