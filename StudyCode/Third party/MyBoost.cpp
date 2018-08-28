/********************************************************************
	filename: 	MyBoost
	purpose:	boost��ѧϰ
	created:	2014/10/21
	updated:	2014/10/21
	author:		maple(������)	
*********************************************************************/
/*
#include "MyBoost.h"
#include <string>

#include "boost/scoped_ptr.hpp"
#include "boost/scoped_array.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/checked_delete.hpp"
#include "boost/Utility.hpp"
#include "boost/operators.hpp"
#include "boost/regex.hpp"
#include "boost/any.hpp"
#include "boost/variant.hpp"
#include "boost/tuple/tuple.hpp"
#include "boost/bind.hpp"
#include "boost/lambda/lambda.hpp"
#include "boost/function.hpp"
#include "boost/signals.hpp"


using namespace boost;


// ���ɸ���,��ֵ����
class A:noncopyable,less_than_comparable<A>,equivalent<A>
{
private:
	int m_value;
public:
	A(void)
	{

	}

	A(int init_value)
	{
		m_value = init_value;
	}

	~A(void)
	{
		std::cout << "~A()" << std::endl;
	}

	void A::Call()
	{
		std::cout << "A.Call()" << std::endl;
	}

	// ����ȡָ��/��ַ
	A* A::operator& ()const
		{
			return NULL;
		}

	// ����С��
	friend bool A::operator<(const A& lhs, const A& rhs)
	{
		return lhs.m_value < rhs.m_value;
	}
};

MyBoost::MyBoost(void)
{
}

MyBoost::~MyBoost(void)
{
}

// ��̬���
#include "boost/type_traits.hpp"
#include "boost/static_assert.hpp"
template <typename T> class only_compatible_with_integral_types 
{  
	BOOST_STATIC_ASSERT(boost::is_float<T>::value);
};
only_compatible_with_integral_types<float> m_asa;


// bind
void nine_arguments(  int i1,int i2,int i3,int i4,int i5,int i6,int i7,int i8, int i9) 
{  
	std::cout << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << i9 << '\n';
}

// signalsʹ��
void my_first_slot(std::string str) 
{  
	std::cout << "\n my_first_slot " << str;
}
// signalsʹ��
class my_second_slot 
{
	public:  void operator()(std::string str) const 
		{
			std::cout << "\n operator() " << str;  
		}
};

// �ַ�������(���߳���Ч ����Ḳ��ǰ���)
inline char * ToLow(const char * string)
{
	static char temp[256];

	memcpy(temp, string, strlen(string) + 1);

	for (char * cp=temp; *cp; ++cp)
	{
		if ('A' <= *cp && *cp <= 'Z')
			*cp += 'a' - 'A';
	}

	return temp;
}

///////////////////////////����ӿ�///////////////////////////////////////////////
// ��ʼ����
void MyBoost::BeginTest()
{
	// Smart_Ptr
	if (false)
	{
		//boost::scoped_ptr ����ȷ����̬����Ķ����ܹ�����ȷ��ɾ����
		//scoped_ptr ������std::auto_ptr���Ƶ����ԣ���������������������ת������Ȩ��auto_ptr���ԡ�
		//��ʵ�ϣ�scoped_ptr��Զ���ܱ����ƻ򱻸�ֵ��scoped_ptr ӵ������ָ�����Դ������Ȩ������Զ��������������Ȩ��
		//scoped_ptr�������������������ǵĴ���ı��֣����ǿ��Ը�����Ҫѡ������ʵ�����ָ��(scoped_ptr �� auto_ptr)��
		scoped_ptr<CMyArray> p(new CMyArray());
		if (p.get() != NULL)
		{
			p->Add(11);
			(*p).Add(12);
			p.get()->Add(13);
			// �����Զ��ͷ�
		}
		

		// �Զ��ͷż���
		scoped_array<CMyArray> ary(new CMyArray[10]);
		ary[0].Add(1);
		ary[2].Add(1);

		// ����ָ�� �����ü���
		boost::shared_ptr<int> entity(new int(14));      
		*entity = 2;

		// ���ڼ���
		typedef std::vector<boost::shared_ptr<A> > container_type;
		typedef container_type::iterator iterator;
		container_type container;
		for (int i=0;i<10;++i) 
		{    
			boost::shared_ptr<A> p(new A(i));
			container.push_back(p);  
		}  

	}

	// utility
	if (false)
	{
		// �������
		BOOST_STATIC_ASSERT(sizeof(int)==4);

		// ���������
		//class as;
		//as *p;
		//checked_delete(p);

		// ���ɸ��� ��ֵ �ر����ڲ���ָ��
		// the big three ���� 
		// ����,����,��ֵ 3��һ����
		A a1;
		//A a2(a1);
		//A a3 = a1;

		// ��ȡ��ַ addressof ��֤����ָ��
		A* p1 = addressof(a1);
		A* p2 = &a1;
	}

	// operators
	if (false)
	{
		// ʵ�� < ,��������< > <= == !=
		// �̳�less_than_comparable<A>,equivalent<A>
		A a1(10);
		A a2(5);
		a1 < a2;
		a1 <= a2;
		a1 > a2;
		a1 == a2;
	}

	// regex �ַ�ƥ��
	if (false)
	{
		// ����ƥ���ַ�
		regex reg("(A.*)");
		// ȫ��ƥ��
		bool b = regex_match( "This expression could match from A and beyond.",  reg);
		b = regex_match( "AThis expression could match from A and beyond.",  reg);
		
		// ���� ���ָ���
		reg = regex("\\d3");
		b = boost::regex_search( "AThis 123 could match from A and beyond.", reg);

		// �滻�ı�

		reg = regex("zsq");    
		std::string s = "zsq Have Zsqque name";  
		//s = boost::regex_replace(s, reg, "maple");
	}

	// any  ������õ�����-ֵ�� ������һ��������.
	if (false)
	{
		// �������͵Ĵ�ȡ
		boost::any a;
		a = std::string("A string");
		std::string str = any_cast<std::string>(a);

		// ��ȡ����
		if (!a.empty())
		{
			bool same_type = a.type() == typeid(std::string);
		}

		//����
		std::vector<any> vct;
		vct.push_back(1);
		vct.push_back(1.2);
		vct.push_back(std::string("zsq"));

		// ��ָ�� �޴������� ����shared_ptr����
	}

	// variant
	if (false)
	{
		// ö�����͵� �ɱ�����
		boost::variant<int,double,std::string> my_first_variant("Hello world");
		my_first_variant = 1;
		my_first_variant = "zsq";

		// ȡֵ
		std::string str = get<std::string>(my_first_variant);

		// ��ȡ�ڼ�������
		int type_index = my_first_variant.which();
	}

	// Tuple ��ֵ���� pair����
	if (false)
	{
		// �������
		boost::tuple<int,double,std::string>   triple(42, 3.14, "My first tuple!");
		int i = boost::tuples::get<0>(triple);  
		double d = triple.get<1>();  
		std::string s = boost::get<2>(triple);
	}

	// Bind bind1st bind2nd �ķ���
	if (false)
	{
		// ������
		int i1=1,i2=2,i3=3,i4=4,i5=5,i6=6,i7=7,i8=8,i9=9;  
		(boost::bind(&nine_arguments,_9,_2,_1,_6,_3,_8,_4,_5,_7))(i1,i2,i3,i4,i5,i6,i7,i8,i9);

		//boost::ref/boost::cref  �������� Ĭ�ϸ���

		// ֧���麯��
		derived d;
		base b;
		boost::bind(&base::print,_1)(b);
		boost::bind(&base::print,_1)(d);

	}

	// lambda ����Ҫ�ڵ��ú���ʱ��������˳��� arity 
	if (false)
	{
		using namespace boost::lambda;
		boost::function<void(int,int,int)> f = 
		std::cout << _1 << "*" << _2 << "+" << _3 << "=" <<_1*_2+_3 << "\n";
		f(1,2,3);
		f(3,2,1);
	}

	// function �����õ��������� ����Ҫ����һ���ص�������������
	if (false)
	{
		// ���庯��
		boost::function<bool (int)> f1;
		boost::function1<bool,int> f1_ex;
		// �ȼ۶���
		boost::function<int (int,double)> f2;
		boost::function2<int, int,double> f2_ex;

		// ��������
		int some_func(int i,double d);

		// ������ֵ ��������!
		f2 = &some_func;

		// ��������
		f2 = boost::ref(some_func);

		// ʹ�ú���
		if (!f2.empty())
		{
			int n = f2(3, 19.5f);
		}

	}

	// Signals ��׳�Ĵ��������¼�����Ļ���
	if (false)
	{
		// �����ź�
		boost::signal<void (std::string)> sig;  
		// �����ź�/�¼� ��������(��less��������֤����˳��)
		sig.connect(1, &my_first_slot); 
		sig.connect(0, my_second_slot());  
		// �����ź�
		sig("zsq");
	}

	return;
}

// ����
int some_func(int i,double d) 
{  
	return i + d;
}
*/