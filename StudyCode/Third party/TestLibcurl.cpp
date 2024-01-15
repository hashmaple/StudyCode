//--------------------------------------------------------------------
// 文件名:		TestLibcurl
// 内  容:		
// 说  明:		
// 创建日期:	2020年9月23日
// 整理日期:	2020年9月23日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
/* 使用步骤
1. 调用curl_global_init()初始化libcurl
2. 调用curl_easy_init()函数得到 easy interface型指针
3. 调用curl_easy_setopt()设置传输选项
4. 根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务
5. 调用curl_easy_perform()函数完成传输任务
6. 调用curl_easy_cleanup()释放内存
7.调用curl_global_cleanup()析构libcurl
在整过过程中设置curl_easy_setopt()参数是最关键的，几乎所有的libcurl程序都要使用它。

在基于LibCurl的程序里，主要采用callback function （回调函数）的形式完成传输任务，
用户在启动传输前设置好各类参数和回调函数，当满足条件时libcurl将调用用户的回调函数实现特定功能。
*/

#include "TestHeader.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>

// 默认不支持SSL ZLIB
#include "curl.h"

#include <string>
using namespace std;

// 宽字符串转换到UTF8
inline const char* Port_WideStrToUTF8(const wchar_t* info, char* buf, size_t byte_size)
{
	int res = WideCharToMultiByte(CP_UTF8, 0, info, -1, buf, int(byte_size),
		NULL, NULL);

	if (0 == res)
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			buf[byte_size - 1] = 0;
		}
		else
		{
			buf[0] = 0;
		}
	}

	return buf;
}

// UTF8转换到宽字符串
inline const wchar_t* Port_UTF8ToWideStr(const char* info, wchar_t* buf, size_t byte_size)
{
	const size_t len = byte_size / sizeof(wchar_t);
	int res = MultiByteToWideChar(CP_UTF8, 0, info, -1, buf, int(len));

	if (res == 0)
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			buf[len - 1] = 0;
		}
		else
		{
			buf[0] = 0;
		}
	}

	return buf;
}

// 接收返回值
size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	FILE *fp = (FILE *)user_p;
	size_t return_size = fwrite(buffer, size, nmemb, fp);

	// UTF8 转宽字符
	wchar_t wstrbuff[1024] = {};
	Port_UTF8ToWideStr((char *)buffer, wstrbuff, 1023);

	return return_size;
}

// 对外接口
void TestLibcurl::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 测试 获取打开的网页信息
	if (0)
	{
		cout << "==TestLibcurl::BeginTest===" << endl;

		// 初始化libcurl
		auto return_code = curl_global_init(CURL_GLOBAL_WIN32);
		if (CURLE_OK != return_code)
		{
			cerr << "init libcurl failed." << endl;
			return;
		}

		// 获取easy handle
		CURL *easy_handle = curl_easy_init();
		if (NULL == easy_handle)
		{
			cerr << "get a easy handle failed." << endl;
			curl_global_cleanup();
			return;
		}
		 
		// 设置easy handle属性  (https 需要libcurl 编译时选择 DLL-OPENSSL
		curl_easy_setopt(easy_handle, CURLOPT_URL, "http://localhost:8888"); 

		curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data);

		// 数据写入 data.html文件
		FILE *fp;
		fopen_s(&fp, "data.html", "ab+");
		curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);

		// 设置表头和post内容
		if (1)
		{
			// 设置表头，表头内容可能不同
			struct curl_slist* headerlist = NULL;
			curl_slist_append(headerlist, "Content-Type:application/x-www-form-urlencoded");
			curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headerlist);
			// 设置参数，比如"ParamName1=ParamName1Content&ParamName2=ParamName2Content&..."
			curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
			// 设置为Post
			curl_easy_setopt(easy_handle, CURLOPT_POST, 1);
		}

		// 超时时间
		curl_easy_setopt(easy_handle, CURLOPT_TIMEOUT, 3);

		// 传输时间和速度控制
		curl_easy_setopt(easy_handle, CURLOPT_LOW_SPEED_TIME, 100);
		curl_easy_setopt(easy_handle, CURLOPT_LOW_SPEED_LIMIT, 10);

		// 执行数据请求
		auto code = curl_easy_perform(easy_handle);
		if (code != CURLE_OK)
		{
			cerr << "curl_easy_perform failed! return: " << code << endl;
		}

		// 释放资源
		fclose(fp);
		curl_easy_cleanup(easy_handle);
		curl_global_cleanup();

		cout << "==TestLibcurl::End===" << endl;
	}
}
