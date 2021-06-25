#pragma once

#include "IMyDLL.h"
namespace MyDLL_SPACE
{
	class MyDLL :public IMyDLL
	{
	public:
		virtual const wchar_t* OutputText();
	};

}
