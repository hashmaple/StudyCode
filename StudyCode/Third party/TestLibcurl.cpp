//--------------------------------------------------------------------
// 文件名:		TestLibcurl
// 内  容:		
// 说  明:		
// 创建日期:	2020年9月23日
// 整理日期:	2020年9月23日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "TestLibcurl.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>

// 默认不支持SSL ZLIB
#include "curl.h"

#include <string>
using namespace std;

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
	FILE *fp = (FILE *)user_p;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	cout << (char *)buffer << endl;
	return return_size;
}

TestLibcurl::TestLibcurl()
{
}

TestLibcurl::~TestLibcurl()
{
}

// 对外接口
void TestLibcurl::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 测试 获取打开的网页信息
	if (1)
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
