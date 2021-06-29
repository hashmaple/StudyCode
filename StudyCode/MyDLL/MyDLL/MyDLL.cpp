#include "pch.h"
#include "MyDLL.h"

namespace MyDLL_SPACE
{
	const wchar_t* MyDLL::OutputText()
	{
		return L"This is form MyDLL_SPACE::MyDLL::OutputText";
	}

	IMyDLL* GetInterface()
	{
		static MyDLL_SPACE::MyDLL mydll;
		return &mydll;
	}
}

int GetNum()
{
	return 110;
}

