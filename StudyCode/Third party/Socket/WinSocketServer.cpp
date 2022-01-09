//--------------------------------------------------------------------
// 文件名:		WinSocketServer
// 内  容:		WinSocketServer
// Winsocket:    https://www.cnblogs.com/zCoderJoy/p/3889495.html
// 线程介绍:     https://www.cnblogs.com/alinh/p/9648084.html
// TCP IP详解:   https://blog.csdn.net/qq_44714603/article/details/92694011
// TCP/IP协议:   https://www.cnblogs.com/LIUYANZUO/p/7302572.html
// 创建日期:	2021年7月20日
// 整理日期:	2021年7月20日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "../TestHeader.h"

#include <stdio.h>  
#include <iostream>
#include <string>
#include <thread>

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

void StartServer()
{
	cout << __FILE__ << "  thread: " << __FUNCTION__ << endl;

	// 第一步 通过WSAStartup函数完成对Winsock服务的初始化,调用socket必须初始化
	WSADATA wsaData;
	// Windows Sockets Asynchronous，Windows异步套接字
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return;
	}

	// 判断版本
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		// 释放
		WSACleanup();
		return;
	}

	//第二步 建立本地流式套接字，返回套接字号；af_inet地址族，用流式套接字，自动匹配
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);  

	//TCP IP的地址信息
	SOCKADDR_IN addrSrv;
	//允许套接字向任何分配给本地机器的IP地址发送或接收数据。
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// internetwork: UDP, TCP, etc.
	addrSrv.sin_family = AF_INET;
	//端口号
	addrSrv.sin_port = htons(6000);
	
	// 第三步 绑定套接字
	bind(sockSrv, (sockaddr*)&addrSrv, sizeof(SOCKADDR));

	// 第四步 监听本地套接字
	listen(sockSrv, 5);

	cout << "Server open.... " << endl;

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char revBuf[100] = {};
	char sendBuf[100] = "Hi...This is WinSocketServer..";


	// 循环内 接受连接请求 读写数据
	while (1)
	{
		// 等待客户端链接，返回客户套接字 阻塞中...
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);

		char str[128];
		inet_ntop(AF_INET, &addrClient.sin_addr, str, sizeof(str));

		cout << "Server accept: " << str << " "<< addrClient.sin_port << endl;

		cout << "Server Send：" << sendBuf << endl;

		// 发送
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);

		// 接受数据
		recv(sockConn, revBuf, 100, 0);

		cout << "Server recv：" << revBuf << endl;

		memset(revBuf, 0, 100);

		closesocket(sockConn);
	}

	closesocket(sockSrv);
}

// 对外接口
void WinSocketServer::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	/* Sever服务器端程序： 
	1、创建套接字（socket）。
	2、将套接字绑定到一个本地地址和端口上（bind）。
	3、将套接字设为监听模式，准备接收客户请求（listen）。
	4、等待客户请求；当请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字（accept）。
	5、用返回的套接字和客户端进行通信（send / recv）。 
	6、返回，等待另一客户请求。 
	7、关闭套接字。
	*/

	// 使用线程函数 避免卡死
	if (0)
	{
		thread t(StartServer);
		//t.join();		// 等待线程完成函数，主线程需要等待子线程运行结束了才可以结束
		t.detach();		// 分离线程函数，让线程在后台运行，即主线程不会等待子线程运行结束
	}

}
