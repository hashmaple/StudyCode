/********************************************************************
	filename: 	MyBoost
	purpose:	boost库学习
	created:	2014/10/21
	updated:	2014/10/21
	author:		maple(周树青)	
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


// 不可复制,赋值的类
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

	// 重载取指针/地址
	A* A::operator& ()const
		{
			return NULL;
		}

	// 重载小于
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

// 静态检测
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

// signals使用
void my_first_slot(std::string str) 
{  
	std::cout << "\n my_first_slot " << str;
}
// signals使用
class my_second_slot 
{
	public:  void operator()(std::string str) const 
		{
			std::cout << "\n operator() " << str;  
		}
};

// 字符生命区(单线程有效 后调会覆盖前结果)
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

///////////////////////////对外接口///////////////////////////////////////////////
// 开始测试
void MyBoost::BeginTest()
{
	// Smart_Ptr
	if (false)
	{
		//boost::scoped_ptr 用于确保动态分配的对象能够被正确地删除。
		//scoped_ptr 有着与std::auto_ptr类似的特性，而最大的区别在于它不能转让所有权而auto_ptr可以。
		//事实上，scoped_ptr永远不能被复制或被赋值！scoped_ptr 拥有它所指向的资源的所有权，并永远不会放弃这个所有权。
		//scoped_ptr的这种特性提升了我们的代码的表现，我们可以根据需要选择最合适的智能指针(scoped_ptr 或 auto_ptr)。
		scoped_ptr<CMyArray> p(new CMyArray());
		if (p.get() != NULL)
		{
			p->Add(11);
			(*p).Add(12);
			p.get()->Add(13);
			// 析构自动释放
		}
		

		// 自动释放集合
		scoped_array<CMyArray> ary(new CMyArray[10]);
		ary[0].Add(1);
		ary[2].Add(1);

		// 智能指针 带引用计数
		boost::shared_ptr<int> entity(new int(14));      
		*entity = 2;

		// 用于集合
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
		// 输入断言
		BOOST_STATIC_ASSERT(sizeof(int)==4);

		// 检测类完整
		//class as;
		//as *p;
		//checked_delete(p);

		// 不可复制 赋值 特别类内部有指针
		// the big three 规则 
		// 构造,析构,赋值 3者一起定义
		A a1;
		//A a2(a1);
		//A a3 = a1;

		// 获取地址 addressof 保证返回指针
		A* p1 = addressof(a1);
		A* p2 = &a1;
	}

	// operators
	if (false)
	{
		// 实现 < ,可以用上< > <= == !=
		// 继承less_than_comparable<A>,equivalent<A>
		A a1(10);
		A a2(5);
		a1 < a2;
		a1 <= a2;
		a1 > a2;
		a1 == a2;
	}

	// regex 字符匹配
	if (false)
	{
		// 定义匹配字符
		regex reg("(A.*)");
		// 全文匹配
		bool b = regex_match( "This expression could match from A and beyond.",  reg);
		b = regex_match( "AThis expression could match from A and beyond.",  reg);
		
		// 查找 数字个数
		reg = regex("\\d3");
		b = boost::regex_search( "AThis 123 could match from A and beyond.", reg);

		// 替换文本

		reg = regex("zsq");    
		std::string s = "zsq Have Zsqque name";  
		//s = boost::regex_replace(s, reg, "maple");
	}

	// any  定义个好的属性-值类 保存在一个集合内.
	if (false)
	{
		// 容易类型的存取
		boost::any a;
		a = std::string("A string");
		std::string str = any_cast<std::string>(a);

		// 获取类型
		if (!a.empty())
		{
			bool same_type = a.type() == typeid(std::string);
		}

		//集合
		std::vector<any> vct;
		vct.push_back(1);
		vct.push_back(1.2);
		vct.push_back(std::string("zsq"));

		// 放指针 无触发析构 建议shared_ptr保存
	}

	// variant
	if (false)
	{
		// 枚举类型的 可变类型
		boost::variant<int,double,std::string> my_first_variant("Hello world");
		my_first_variant = 1;
		my_first_variant = "zsq";

		// 取值
		std::string str = get<std::string>(my_first_variant);

		// 获取第几个类型
		int type_index = my_first_variant.which();
	}

	// Tuple 多值返回 pair扩充
	if (false)
	{
		// 构造访问
		boost::tuple<int,double,std::string>   triple(42, 3.14, "My first tuple!");
		int i = boost::tuples::get<0>(triple);  
		double d = triple.get<1>();  
		std::string s = boost::get<2>(triple);
	}

	// Bind bind1st bind2nd 的泛化
	if (false)
	{
		// 参数绑定
		int i1=1,i2=2,i3=3,i4=4,i5=5,i6=6,i7=7,i8=8,i9=9;  
		(boost::bind(&nine_arguments,_9,_2,_1,_6,_3,_8,_4,_5,_7))(i1,i2,i3,i4,i5,i6,i7,i8,i9);

		//boost::ref/boost::cref  传递引用 默认复制

		// 支持虚函数
		derived d;
		base b;
		boost::bind(&base::print,_1)(b);
		boost::bind(&base::print,_1)(d);

	}

	// lambda 你需要在调用函数时调整参数顺序或 arity 
	if (false)
	{
		using namespace boost::lambda;
		boost::function<void(int,int,int)> f = 
		std::cout << _1 << "*" << _2 << "+" << _3 << "=" <<_1*_2+_3 << "\n";
		f(1,2,3);
		f(3,2,1);
	}

	// function 可以用到泛化函数 你需要保存一个回调函数或函数对象
	if (false)
	{
		// 定义函数
		boost::function<bool (int)> f1;
		boost::function1<bool,int> f1_ex;
		// 等价定义
		boost::function<int (int,double)> f2;
		boost::function2<int, int,double> f2_ex;

		// 函数声明
		int some_func(int i,double d);

		// 函数赋值 不是引用!
		f2 = &some_func;

		// 传递引用
		f2 = boost::ref(some_func);

		// 使用函数
		if (!f2.empty())
		{
			int n = f2(3, 19.5f);
		}

	}

	// Signals 健壮的触发器及事件处理的机制
	if (false)
	{
		// 构造信号
		boost::signal<void (std::string)> sig;  
		// 链接信号/事件 给出组名(按less排序来保证调用顺序)
		sig.connect(1, &my_first_slot); 
		sig.connect(0, my_second_slot());  
		// 发出信号
		sig("zsq");
	}

	return;
}

// 函数
int some_func(int i,double d) 
{  
	return i + d;
}
*/