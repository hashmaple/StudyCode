/*!
 * \file C++11.cpp
 * \date 2018/12/24 14:05
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief learn c++11 standard code
 *
 * TODO: long description
 *
 * \note
*/
#include "C++11.h"

using namespace std;

/////////////////////////////对外接口/////////////////////////////////////////////
// CPP11
void CPP11::BeginTest()
{
	/* https://zh.cppreference.com/w/cpp/11
	核心语言功能特性
	auto 与 decltype
	预置与弃置的函数
	final 与 override
	尾随返回类型
	右值引用
	移动构造函数与移动赋值运算符
	有作用域枚举
	constexpr 与字面类型
	列表初始化
	委托与继承的构造函数
	花括号或等号初始化器
	nullptr
	long long
	char16_t 与 char32_t
	类型别名
	变参数模板
	推广的（非平凡）联合体
	推广的 POD （平凡类型与标准布局类型）
	Unicode 字符串字面量
	用户定义字面量
	属性
	lambda 表达式
	noexcept 说明符与 noexcept 运算符
	alignof 与 alignas
	多线程内存模型
	线程局部存储
	GC 接口
	范围 for （基于 Boost 库）
	static_assert （基于 Boost 库）
	*/

	NewFeatures NF;
	NF.BeginTest();

	GeneralUtilities GU;
	GU.BeginTest();

	STLContainer container;
	container.BeginTest();

	FunAndLambda funLambda;
	funLambda.BeginTest();

	NewString newString;
	newString.BeginTest();

	MultiThread multiThread;
	multiThread.BeginTest();

	return;
}
