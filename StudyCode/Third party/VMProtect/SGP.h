#pragma once


enum start_type
{
	DEFAULTSTART = 0,
	NOSTARTTRAY = 0x1,					//不启动托盘
	NOSHOWNOTICE = 0x2,					//不使用自带提示,如果使用回调就可以不使用
	NOFLASHDLG = 0x4,					//不显示flash框
	TRAYSTART = 0x8						//托盘启动
};

typedef struct szLOADPROTECT
{
	char url[1024];
	DWORD starttype;
}PSZLOADPROTECT;


typedef struct szADDPROTECTPROCESS
{
	ULONG ProcessId;
	ULONG Client;
}PSZADDPROTECTPROCESS;

typedef struct szADDPROTECTWINDOW
{
	HWND hWnd;
}PSZADDPROTECTWINDOW;

typedef VOID(WINAPI *FCNTPROXY)(ULONG index, FARPROC farProc);
typedef BOOL(*WNPROXY)(FCNTPROXY proxy);

#define LOADPROTECT_INDEX 11
typedef BOOL(WINAPI * LOADPROTECT)(PBYTE buff);

#define ADDPROTECTPROCESS_INDEX 21
typedef BOOL(WINAPI * ADDPROTECTPROCESS)(PBYTE buff);

#define ADDPROTECTWINDOW_INDEX 31
typedef BOOL(WINAPI * ADDPROTECTWINDOW)(PBYTE buff);

#define ENCRYPTPACKAGE_INDEX 41
typedef BOOL(WINAPI * ENCRYPTPACKAGE)(PBYTE buff, SIZE_T length);

#define SAVEUSERINFO_INDEX 51
typedef BOOL(WINAPI *SAVEUSERINFO)(
	const char* Account,
	const char* AccountId,
	const char* Charactor,
	const char* Game,
	const char* Area);

#define ISRUNNING_INDEX 61
typedef BOOL(WINAPI *ISRUNNING)();

#define TERMINATEALL_INDEX 71
typedef BOOL(WINAPI *TERMINATEALL)();

#define COMMITCHEATINFO_INDEX 81
typedef BOOL(WINAPI *COMMITCHEATINFO)(int cheattype);

#define CHECKTHREAD_INDEX 91
typedef BOOL(WINAPI *CHECKTHREAD)(LPTHREAD_START_ROUTINE checkfunction);

#define NOTICEKERNEL_INDEX 101
typedef BOOL(WINAPI *NOTICEKERNEL)();

#define SETKEY_INDEX 111
typedef BOOL(WINAPI *SETKEY)(PBYTE buff, SIZE_T length);

#define ENCRYPTPACKAGE2_INDEX 121
typedef BOOL(WINAPI * ENCRYPTPACKAGE2)(PBYTE buff, SIZE_T length);
