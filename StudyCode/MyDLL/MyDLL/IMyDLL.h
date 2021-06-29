//--------------------------------------------------------------------
// 文件名:		IMyDLL.h
// 内  容:		自定义DLL的头文件
// 说  明:		
// 更新日期:	2021/06/25
// 更新人:		周树青（MIKE)
// 版权所有:	
//--------------------------------------------------------------------

#ifndef _INTERFACE_MYDLL_H
#define _INTERFACE_MYDLL_H

#ifdef MYDLL_EXPORTS
#define  MYDLL_API __declspec(dllexport)
#else
#define  MYDLL_API __declspec(dllimport)
#endif

extern "C" MYDLL_API int GetNum();

namespace MyDLL_SPACE
{
	class IMyDLL
	{
	public:
		virtual const wchar_t* OutputText() = 0;
	};

	extern "C" MYDLL_API IMyDLL * GetInterface();


}
#endif //_INTERFACE_MYDLL_H