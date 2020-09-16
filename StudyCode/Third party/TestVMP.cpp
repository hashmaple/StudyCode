//--------------------------------------------------------------------
// �ļ���:		TestVMP
// ��  ��:		
// ˵  ��:		
// ��������:	2017��5��8��
// ��������:	2020��4��11��
// ������:		Maple(������)
// ��Ȩ����:	������ţ���ֿƼ��ɷ����޹�˾
//--------------------------------------------------------------------
#include "TestVMP.h"

#include <stdio.h>  
#include <iostream>
#include <process.h>
#include <windows.h>

#include "VMProtectSDK.h"

#include "SgpProtect.h"
#include "SGP.h"

/* 
//��ʼ��������ǣ���Ӧ�ڹ������ã������ԡ��ڴ汣���ȵȣ�
VMProtectBegin(const char *);
//��ʼ���⻯���봦��ǣ������������ã�
VMProtectBeginVirtualization(const char *);
//��ʼ������봦��ǣ������������ã�
VMProtectBeginMutation(const char *);
//��ʼ����+��������Ǵ�
VMProtectBeginUltra(const char *);
VMProtectBeginVirtualizationLockByKey(const char *);
VMProtectBeginUltraLockByKey(const char *);
//�������������
VMProtectEnd(void);
//������
BOOL VMProtectIsDebuggerPresent(BOOL);
//��������
BOOL VMProtectIsVirtualMachinePresent(void);
//ӳ���ļ�CRCУ��
BOOL VMProtectIsValidImageCRC(void);
//���ܱ���������Ϊ�ַ���A
char * VMProtectDecryptStringA(const char *value);
//���ܱ���������Ϊ�ַ���W
wchar_t * VMProtectDecryptStringW(const wchar_t *value);
*/
using namespace std;

TestVMP::TestVMP()
{

}

TestVMP::~TestVMP()
{

}

// ����ӿ�
void TestVMP::BeginTest()
{

	// ��������򵥵ĺ���
	if (0)
	{
		VMProtectBegin("checkcrc");
		BOOL bRet = VMProtectIsValidImageCRC();
		VMProtectEnd();

		// �Ƿ��ڵ���
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

	// ����SGP
	if (0)
	{
		BOOL bstart = StartProtect("http://10.200.30.76/", DEFAULTSTART);

		cout << "====StartProtect===== " << bstart << endl;

		// �����˺Ž�ɫ
		BOOL bsave = SaveUserInfo("zhousq", "wn0123", "mike", "9yzj", "89��");
		cout << "====SaveUserInfo===== " << bsave << endl;
	}
}