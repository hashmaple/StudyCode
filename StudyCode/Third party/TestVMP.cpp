//--------------------------------------------------------------------
// 文件名:		TestVMP
// 内  容:		
// 说  明:		
// 创建日期:	2017年5月8日
// 整理日期:	2020年4月11日
// 创建人:		Maple(周树青)
// 版权所有:	苏州蜗牛数字科技股份有限公司
//--------------------------------------------------------------------
#include "TestVMP.h"

#include <stdio.h>  
#include <iostream>
#include <process.h>
#include <windows.h>

#include "VMProtectSDK.h"

/* 
//开始保护处标记（对应于功能设置：反调试、内存保护等等）
VMProtectBegin(const char *);
//开始虚拟化代码处标记（包括保护设置）
VMProtectBeginVirtualization(const char *);
//开始变异代码处标记（包括保护设置）
VMProtectBeginMutation(const char *);
//开始虚拟+代码变异标记处
VMProtectBeginUltra(const char *);
VMProtectBeginVirtualizationLockByKey(const char *);
VMProtectBeginUltraLockByKey(const char *);
//保护结束处标记
VMProtectEnd(void);
//检测调试
BOOL VMProtectIsDebuggerPresent(BOOL);
//检测虚拟机
BOOL VMProtectIsVirtualMachinePresent(void);
//映像文件CRC校验
BOOL VMProtectIsValidImageCRC(void);
//解密被保护的名为字符串A
char * VMProtectDecryptStringA(const char *value);
//解密被保护的名为字符串W
wchar_t * VMProtectDecryptStringW(const wchar_t *value);
*/
using namespace std;

TestVMP::TestVMP()
{

}

TestVMP::~TestVMP()
{

}

// 对外接口
void TestVMP::BeginTest()
{
	if (0)
	{
		VMProtectBegin("checkcrc");
		BOOL bRet = VMProtectIsValidImageCRC();
		VMProtectEnd();

		// 是否在调试
		if (VMProtectIsDebuggerPresent(true))
		{
			cout << "====VMProtectIsDebuggerPresent(true)=====" << endl;
		}
		
		if (VMProtectIsDebuggerPresent(false))
		{
			cout << "====VMProtectIsDebuggerPresent(false)=====" << endl;
		}

		VMProtectBegin(__FUNCTION__);

		cout << "====VMProtectBegin=====" << endl;

		if (VMProtectIsVirtualMachinePresent())
		{
			cout << "====VMProtectIsVirtualMachinePresent=====" << endl;
		}

		VMProtectEnd();

		cout << "====end=====" << endl;
	}
}
