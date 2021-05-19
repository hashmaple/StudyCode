//--------------------------------------------------------------------
// 文件名:		TestCLib
// 内  容:		C语言库
// 说  明:		
// 创建日期:	2011年8月18日
// 创建人:		Maple(周树青)
// 版权所有:	
//--------------------------------------------------------------------
#pragma once

// 若无别人用,会被lib中函数覆盖
class MyLibClass
{
public:
	inline int GetNumber() { return 1; };
};

// 测试函数
bool TestCLib();

void TestMyStaticLib();