#include "pch.h"
#include "MyLibClass.h"
#include <iostream>

int m_MyLibClassNum = 9527;

int MyLibClass::GetNumber()
{
	std::cout << __FILE__ << "  " << __FUNCTION__ << std::endl;
	return 9527;
}

int MyLibClass::GetNumber2()
{
	std::cout << __FILE__ << "  " << __FUNCTION__ << std::endl;
	return 9528;
}
