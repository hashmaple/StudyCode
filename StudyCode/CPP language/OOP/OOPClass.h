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

// ������
class complex
{
public:
	// ���캯�� + ��ʼ���б�
	complex(double r = 0, double i = 0): re(r), im(i) {}

	// ����������
	complex& operator += (const complex&);
	complex& operator -= (const complex&);

	// const�����˷��������޸��ڲ����� const����Ҳ���Ե���
	double real() const { return re; }
	double imag() const { return im; }

private:
	double re, im;

	// �Ѻ���(�����ڿ��Է���private member)
	friend complex& __doapl(complex*, const complex&);
	friend complex& __doami(complex*, const complex&);
};

// �ඨ��(inline����, ���հ�������Ϊ׼)
inline complex& __doapl(complex* ths, const complex& r)
{
	// ��������Ϊ complex&, ���ɷ�����ʱ����~
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}

// ���ص�+=������ ��__doaplȥʵ��. 
inline complex& complex::operator += (const complex& r)
{
	return __doapl(this, r);
}

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

// ���ɷ���complex&, ��Ϊ���Ϊ��ʱ����
inline complex operator + (const complex& x, const complex& y)
{
	return complex(real(x) + real(y), imag(x) + imag(y));
}

#endif // OOPClass_h__
