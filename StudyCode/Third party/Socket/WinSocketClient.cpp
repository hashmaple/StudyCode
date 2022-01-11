//--------------------------------------------------------------------
// 文件名:		WinSocketClient
// 内  容:		WinSocketClient
// 说  明:		socket:https://www.cnblogs.com/zCoderJoy/p/3889495.html
// 线程介绍:     https://www.cnblogs.com/alinh/p/9648084.html
// 创建日期:	2021年7月21日
// 整理日期:	2021年7月21日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "../TestHeader.h"

#include <stdio.h>  
#include <iostream>
#include <string>
#include <thread>

#include <WS2tcpip.h>

#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

void StartClient()
{
	cout << __FILE__ << "  thread: " << __FUNCTION__ << endl;

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return;
	}

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	inet_pton(AF_INET, "127.0.0.1", &addrSrv.sin_addr.S_un.S_addr);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	// 构造发送数据
	auto threadID = GetCurrentThreadId();
	char recvBuf[100] = {};
	char sendBuf[100] = {};
	sprintf_s(sendBuf, "I am WinSocketClient(threadID = %d).....", threadID);

	while (true)
	{
		auto ret = recv(sockClient, recvBuf, 100, 0);
		if (ret <= 0)
		{
			// 断开
			break;
		}

		if (strlen(recvBuf) > 0)
		{
			cout << "Client recv：" << recvBuf << endl;
		}

		memset(recvBuf, 0, 100);


		send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		cout << "Client send：" << sendBuf << endl;

		Sleep(1000);
	}

	closesocket(sockClient);

	WSACleanup();
}

// 对外接口
void WinSocketClient::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	if (0)
	{
		// 使用线程函数 避免卡死
		thread t(StartClient);
		//t.join();		// 等待线程完成函数，主线程需要等待子线程运行结束了才可以结束
		t.detach();		// 分离线程函数，让线程在后台运行，即主线程不会等待子线程运行结束

		thread t2(StartClient);
		t2.detach();

		thread t3(StartClient);
		t3.detach();
	}
}
