//--------------------------------------------------------------------
// �ļ���:		OOPClass
// ��  ��:		�������߼����DEMO
// ˵  ��:		Class with or without pointer member
// ��������:	2022��2��26��
// ��������:	2022��2��26��
// ������:		Maple(������)
//--------------------------------------------------------------------
// guard ��������(�������ظ�����)
#ifndef OOPClass_h__
#define OOPClass_h__

// guard ��������(�������ظ�����)
// #pragma once

class complex;	// ǰ������
class OOPClass
{
public:
	OOPClass(void) {};
	~OOPClass(void) {};

	// ����ӿ�
	void BeginTest();
};

// ǰ������
class complex;
complex& __doapl(complex* ths, const complex& r);
complex& __doami(complex* ths, const complex& r);

// ������ without pionter class
class complex
{
public:
	// ���캯�� + ��ֵ��,��ʼ��(�����ڸ�ֵ)
	complex(double r = 0, double i = 0): re(r), im(i) {}
	
	// ��������
	~complex() { re = 0; im = 0; }

	// ���������� (return by reference)
	complex& operator += (const complex&);
	complex& operator -= (const complex&);

	// const������Ա���� �˷��������޸��ڲ����� const����Ҳ���Ե���
	double real() const { return re; }
	// ��class body��ֱ�Ӷ���,�Զ���Ϊinline�ĺ�ѡ��
	double imag() const { return im; }

private:
	double re, im;

	// ��Ԫ(�����ڿ��Է���private member)
	friend complex& __doapl(complex*, const complex&);
	friend complex& __doami(complex*, const complex&);
};

// ��body����ඨ��(inline���հ�������Ϊ׼)
inline complex& __doapl(complex* ths, const complex& r)
{
	// ��ΪΪ��Ԫ,����ȡ��friend��private��Ա
	ths->re += r.re;
	ths->im += r.im;

	// ��������Ϊ complex&, ���ɷ�����ʱ����~
	return *ths;
}

// ���ص�+=������ ��__doaplȥʵ��. 
inline complex& complex::operator += (const complex& r)
{
	return __doapl(this, r);
}

// ��һ��������ı�,�ڶ�����������ı� ��������
inline complex& __doami(complex* ths, const complex& r)
{
	// ��������Ϊ complex&, ���ɷ�����ʱ����~
	ths->re -= r.re;
	ths->im -= r.im;
	return *ths;
}

// ���ص�-=������ ��__doamiȥʵ��. 
inline complex& complex::operator -= (const complex& r)
{
	return __doami(this, r);
}

// ȫ�ֺ��� �ṩ2��complex�� + ����
inline double imag(const complex& x) { return x.imag(); }

inline double real(const complex& x){ return x.real(); }

// ���ɷ���complex&, ��Ϊ���Ϊ��ʱ���� local object
inline complex operator + (const complex& x, const complex& y)
{
	return complex(real(x) + real(y), imag(x) + imag(y));
}

// ����������, �ǳ�Ա����
inline bool operator == (const complex& x, const complex& y)
{
	return real(x) == real(y) && imag(x) == imag(y);
}


// ������ with pionter class
class String
{
	// Big Three �������⺯��
public:
	// class with pointer ������ copy ctor �� op=
	String(const char* cstr = 0);
	String(const String& str); // �������캯��
	String& operator=(const String& str); // ������ֵ����
	// �����˶��ڴ�,�ͱ�������ʱ�ͷ�
	~String();
	
	char* get_c_str() const	{ return m_data; }

private:
	char* m_data;
};

// String�ඨ��
#include <cstring>
inline String::String(const char* cstr)
{
	// ��������
	if (cstr)
	{
		// heap���Ͽ��ռ�,��������
		m_data = new char[strlen(cstr) + 1];
		strcpy_s(m_data, strlen(cstr) + 1, cstr);
	}
	else
	{
		// ȷ������ɹ�,�����ݵ��ַ���
		m_data = new char[1];
		*m_data = '\0';
	}
}

inline String::String(const String& str)
{
	m_data = new char[strlen(str.m_data) + 1];
	strcpy_s(m_data, strlen(str.m_data) + 1, str.m_data);
}

inline String& String::operator =(const String& str)
{
	// ������Ҹ�ֵ self assignment
	if (this == &str)
	{
		return *this;
	}

	delete[] m_data;

	m_data = new char[strlen(str.m_data) + 1];
	strcpy_s(m_data, strlen(str.m_data) + 1, str.m_data);
	return *this;
}

#include <iostream>

inline String::~String()
{
	if (m_data)
	{
		delete[] m_data;
	}

	std::cout << "~String" << std::endl;
}

#endif // OOPClass_h__
