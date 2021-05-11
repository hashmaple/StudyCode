//--------------------------------------------------------------------
// �ļ���:		TestC17
// ��  ��:		
// ˵  ��:		
// ��������:	2021��5��7��
// ��������:	2021��5��7��
// ������:		Maple(������)
//--------------------------------------------------------------------
#include "C++17.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

// �Զ��Ƶ���������
template<typename T>
auto addByType(const T& t)
{
	// �����ж��� ���ʽ����Ϊ�������
	if constexpr(is_integral<T>::value)
	{
		return t + 1;
	}
	else
	{
		return t;
	}
}


// ǿ��ʵ����
template class vector<int>;
// ��ʵ����
extern template class vector<bool>;

class Base
{
public:
	int v1=0, v2=0;
	Base() { v1 = 1; };

	// = delete �����ܾ����������ɹ���
	Base& operator=(const Base&) = delete;

	// ί�и��޲ι��죬��ִ��
	Base(int v) :Base()
	{
		v2 = v;
	}

	virtual int foo(int i)
	{
		return i;
	}
};

// final��ȷ��ֹ�����̳к�����
class SubClass final:public Base
{
public:
	// �̳л���Ĺ��캯��
	using Base::Base;

	// override ��ȷ����
	virtual int foo(int i) override
	{
		return i;
	}

	// override ��ȷ���ر���û����д�κλ��෽��
	// virtual int foo2(int i) override;
};

// ��������
// class SubClass2 :public SubClass;

// ǿ����ö��
enum class MyEnum : unsigned int
{
	value1,
	value2,
	// �ɳ������
	value3 = 100,
	value4 = 100
};

// ����ӿ�
void TestC17::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// if�д����ʱ���� ��������Ϊ���� ���� ί�кͼ̳�
	if (0)
	{
		/* / if�д����ʱ���� ��Ҫ�� C++���Ա�׼  /std�� c + + 17
		vector<int> vct = { 1,2,3,4 };
		if (const vector<int>::iterator it = find(vct.begin(), vct.end(), 2); it!= vct.end())
		{
			*it = 1;
		} */

		// �ṹ����
		// tuple<int,double,string> [x,y,z] = make_tuple(1, 2.3, "123");
		// cout << x << y << z << endl;

		// ���ж���������Ϊ������Ч�ʸ���
		cout << "addByType 1 = " << addByType(1) << endl;
		cout << "addByType 1.1 = " << addByType(1.1f) << endl;
		
		// ������>>
		vector<int> vctInt = { 1,2,3 };
		vector<vector<int>> vctVctInt;

		// ���� ί�кͼ̳�
		Base base(2); // ʹ��ί�й���
		cout << "base.v1 = " << base.v1 << endl;
		cout << "base.v2 = " << base.v2 << endl;
		SubClass sub(3); // �û���Ĺ��캯��
		cout << "sub.v1 = " << sub.v1 << endl;
		cout << "sub.v2 = " << sub.v2 << endl;
	}

	// override  final delete
	if (0)
	{
		// override �� final ��������
		
		// = delete �����ܾ����������ɹ���

		// ǿ����ö�� ���ɺ�����ת��
		MyEnum e1 = MyEnum::value1;
		MyEnum e2 = MyEnum::value2;
		MyEnum e3 = MyEnum::value3;
		MyEnum e4 = MyEnum::value4;

		// ����ǿת
		cout << "e1 == " << (unsigned int)e1 << endl;
		cout << "e2 == " << (unsigned int)e2 << endl;
		cout << "e3 == " << (unsigned int)e3 << endl;

		// e1 == 0 ���󣬲���ֱ���ж�

		// ö��֮�䣬���ֵ��ͬ�����ԱȽ�
		if (e3 == e4)
		{
			cout << "e3 == e4 " << endl;
		}

		// case ��ǩֵ�Ѿ������ڴ˿��� �������� : 155 
		switch (MyEnum::value3)
		{
		case MyEnum::value3:
			cout << "switch MyEnum::value3" << endl;
			break;
		// case MyEnum::value4: ���벻��,��Ϊֵ��value3���
			cout << "switch MyEnum::value4" << endl;
			break;
		default:
			break;
		}

	}
}
