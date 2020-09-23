//--------------------------------------------------------------------
// 文件名:		TestLibcurl
// 内  容:		
// 说  明:		
// 创建日期:	2020年9月23日
// 整理日期:	2020年9月23日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#pragma once

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

class TestLibcurl
{
public:
	TestLibcurl(void);
	~TestLibcurl(void);

	// 对外接口
	void BeginTest();
};
