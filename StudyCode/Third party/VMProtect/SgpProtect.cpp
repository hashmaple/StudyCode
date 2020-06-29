
#include <windows.h>
#include "SgpProtect.h"
#include "SGP.h"
#include "VMProtectSDK.h"

LOADPROTECT g_loadprotect;
ADDPROTECTPROCESS g_addProtectProcess;
SAVEUSERINFO g_saveUserInfo;
ADDPROTECTWINDOW g_addProtectWindow;
ISRUNNING g_isRunning;
ENCRYPTPACKAGE g_encryptPackage;
TERMINATEALL g_terminateAll;
COMMITCHEATINFO g_commitCheatInfo;
CHECKTHREAD g_checkThread;
NOTICEKERNEL g_noticeKernel;
ENCRYPTPACKAGE2 g_encryptPackage2;
SETKEY g_setkey;

int KeyNumData[] = {

	0x01229344,
	0x09998377,
	0x02887388,
	0x03776366,
	0x04665355,
	0x05554322,
	0x06443311,
	0x01332322,
	0x09992333,
	0x08821311,
	0x07720322,
	0x01669344

};

VOID WINAPI MyProxy(ULONG index, FARPROC farProc)
{
#ifdef RELEASE_VERSION
	VMProtectBegin("MyProxyu");
#endif
	if(index == LOADPROTECT_INDEX)
		g_loadprotect = (LOADPROTECT)farProc;
	
	if (index == ADDPROTECTPROCESS_INDEX)
		g_addProtectProcess = (ADDPROTECTPROCESS)farProc;
		
	if (index == ADDPROTECTWINDOW_INDEX)
		g_addProtectWindow = (ADDPROTECTWINDOW)farProc;
		
	if (index == ENCRYPTPACKAGE_INDEX)
		g_encryptPackage = (ENCRYPTPACKAGE)farProc;

	if (index == SAVEUSERINFO_INDEX)
		g_saveUserInfo = (SAVEUSERINFO)farProc;
		
	if (index == ISRUNNING_INDEX)
		g_isRunning = (ISRUNNING)farProc;
		
	if (index == TERMINATEALL_INDEX)
		g_terminateAll = (TERMINATEALL)farProc;
		
	if (index == COMMITCHEATINFO_INDEX)
		g_commitCheatInfo = (COMMITCHEATINFO)farProc;
		
	if (index == CHECKTHREAD_INDEX)
		g_checkThread = (CHECKTHREAD)farProc;
		
	if (index == NOTICEKERNEL_INDEX)
		g_noticeKernel = (NOTICEKERNEL)farProc;
		
	if (index == ENCRYPTPACKAGE2_INDEX)
		g_encryptPackage2 = (ENCRYPTPACKAGE2)farProc;
	
	if (index == SETKEY_INDEX)
		g_setkey = (SETKEY)farProc;

#ifdef RELEASE_VERSION
	VMProtectEnd();
#endif
	
}
BOOL EnKeyNum(int keynum, unsigned char *outbuf)
{
	BOOL bRet = FALSE;
	if (keynum >= 1 && keynum < 13)
	{
		*(int *)outbuf = keynum ^ KeyNumData[keynum - 1];
		bRet = TRUE;
	}
	return bRet;
}
BOOL SetKey(int index)
{
	BYTE data[8] = { 0 };
	
	EnKeyNum(index, (unsigned char *)data);
	g_setkey(data,8);

	return TRUE;
}
DWORD WINAPI CheckFunction(
	LPVOID lpThreadParameter
	)
{
	while (TRUE)
	{
		g_noticeKernel();
		Sleep(2000);
	}
	return 0;
}

BOOL StartProtect(char * url, DWORD starttype)
{
	HMODULE hModule;
	WNPROXY wnProxy;
	BOOL bResult = FALSE;

#ifdef RELEASE_VERSION
	VMProtectBegin("StartProtectu");
#endif
#ifdef _WIN64
	hModule = LoadLibrary(L"spdc_x64.dll");
#else
	hModule = LoadLibrary(L"spdc_x86.dll");
#endif


	if (hModule)
	{
		wnProxy = (WNPROXY)GetProcAddress(hModule, "WnProxy");
		if (wnProxy && wnProxy(MyProxy))
		{
			PSZLOADPROTECT st;
			memset(&st, 0, sizeof(PSZLOADPROTECT));
			st.starttype = DEFAULTSTART;
			
			memcpy(st.url, url, strlen(url));
		
			bResult = g_loadprotect((PBYTE)&st);
			if (bResult)
			{
				g_checkThread(CheckFunction);
			}
		}
	}

#ifdef RELEASE_VERSION
	VMProtectEnd();
#endif
	return bResult;
}

BOOL  AddProtectProcess(ULONG ProcessId, ULONG Client)
{
//#ifdef RELEASE_VERSION
//	VMProtectBegin("111AddProtectProcessU");
//#endif
	BOOL bRet = FALSE;
	PSZADDPROTECTPROCESS st;
	st.ProcessId = ProcessId;
	st.Client = Client;

	bRet = g_addProtectProcess((PBYTE)&st);

//#ifdef RELEASE_VERSION
//	VMProtectEnd();
//#endif
	return bRet;
}

BOOL ADdProtectWindow(HWND hWnd)
{
	BOOL bRet = FALSE;
#ifdef RELEASE_VERSION
	VMProtectBegin("ADdProtectWindow");
#endif
	PSZADDPROTECTWINDOW st;
	st.hWnd = hWnd;

	bRet = g_addProtectWindow((PBYTE)&st);
#ifdef RELEASE_VERSION
	VMProtectEnd();
#endif
	return bRet;
}

BOOL SaveUserInfo(
	const char* Account,
	const char* AccountId,
	const char* Charactor,
	const char* Game,
	const char* Area)
{
	BOOL bRet = FALSE;
	bRet = g_saveUserInfo(Account, AccountId, Charactor, Game, Area);

	return bRet;
}

BOOL IsRunning()
{
	return g_isRunning();
}

BOOL EncryptPackage(PBYTE buff, SIZE_T length)
{
	return g_encryptPackage(buff, length);
}

BOOL TerminateAll()
{
	return g_terminateAll();
}

BOOL CommitCheatInfo(int cheattype)
{
	return g_commitCheatInfo(cheattype);
}