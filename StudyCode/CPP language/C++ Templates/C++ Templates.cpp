//--------------------------------------------------------------------
// 文件名:		C++ Templates
// 内  容:		模板(mu ban)的学习,测试代码
// 说  明:		
// 创建日期:	2021年12月21日
// 整理日期:	2021年12月21日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "C++ Templates.h"

#include <stdio.h>  
#include <iostream>

using namespace std;

// 模板的一般形式如下:
// template <typename type> ret - type func - name(parameter list)


// 针对每种类型,从模板中产生一个实体(也叫模板的实例化instantiation)
//template<class T>  建议使用typename
template<typename T>
inline T const& max(T const& a, T const& b)
{
	return a > b ? a : b;
}

// 需要指定返回值类型 和 实参类型 (取消返回值的const&修饰)
// 把参数转型为返回类型的过程将会创建一个新的局部临时对象，
// 这导致了你不能通过引用来返回结果。 区别于: inline RT const& 
template<typename RT, typename T>
inline RT rt_max(T const& a, T const& b)
{
	return a > b ? a : b;
}

// 对外接口
void TestTemplates::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 模板函数(参数,演绎和显式指定等)
	if (1)
	{
		// 明确使用::调用全局的max函数,不然会调用STL中的std::max()
		cout << "::max(1,3) = " << ::max(1, 3) << endl;
		cout << "::max(1.1, 3.3) = " << ::max(1.1, 3.3) << endl;

		auto s1 = "ABCDE";
		auto s2 = "abcde";
		cout << "::max(s1, s2) = " << ::max(s1, s2) << endl;

		// 显式指定模板实参,不通过调用来演绎
		cout << "::max<double>(1, 3.3) = " << ::max<double>(1, 3.3) << endl;
		cout << "::max<int>(1, 3.3) = " << ::max<int>(1, 3.3) << endl;

		// 显式指定返回类型
		cout << "::rt_max<int>(1.1, 3.3) = " << ::rt_max<int>(1.1, 3.3) << endl;
		cout << "::rt_max<double, double>(1.1, 3.3) = " << ::rt_max<double, double>(1.1, 3.3) << endl;
		cout << "::rt_max<double, int>(1.1, 3.3) = " << ::rt_max<double, int>(1.1, 3.3) << endl;
	}
}