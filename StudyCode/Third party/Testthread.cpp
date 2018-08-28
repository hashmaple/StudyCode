//--------------------------------------------------------------------
// 文件名:		Testthread
// 内  容:		使用通用的PTHREAD来写测试案例
// 说  明:		对比 C++thread库来学习
// 创建日期:	2017年5月8日
// 整理日期:	2017年5月8日
// 创建人:		Maple(周树青)
// 版权所有:	苏州蜗牛数字科技股份有限公司
//--------------------------------------------------------------------
#include "Testthread.h"

#include <stdio.h>  
#include <iostream>
#include <process.h>
#include <windows.h>

using namespace std;

// 1 VC++目录->包含目录 include
#include <pthread.h>

// 2 加载lib链接库 也可以包含在 链接器->输入->附加依赖项
//#pragma comment(lib, "pthreadVC2.lib")

// 3 将dll文件拷贝到生成的.exe所在的文件夹中


void* Function_t(void* Param)
{
	pthread_t myid = pthread_self();
	cout << "pthread-" << (int)myid.p%100 << endl;
	return NULL;
}

pthread_key_t p_key;

// 执行函数
void * childFun(void *args)
{
	pthread_t tid = pthread_self();
	printf("thread %d enter\n", tid);

	int* num = (int*)args;
	cout << "args num = " << *num << endl;

	for (int i = 0; i < 99; i++)
	{
		(*num)++;
	}

	cout << "after num = " << *num << endl;

	return NULL;
}

Testthread::Testthread()
{

}

Testthread::~Testthread()
{

}

// 对外接口
void Testthread::BeginTest()
{

	// 测试最近简单的函数
	if (false)
	{
		pthread_t tid1, tid2;
		int a = 1;
		int b = 2;
		printf("hello\n");

		// 设置线程属性
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

		// 启动线程 ID, 线程属性, 线程函数,函数参数
		pthread_create(&tid1, &attr, childFun, &a);
		pthread_create(&tid2, NULL, childFun, &b);

		// 用于创建线程私有的数据
		// pthread_key_create();
		// pthread_key_delete();


		Sleep(1000);

		printf("main thread exit\n");
	}

	if (false)
	{
		cout << "====begin===== " << endl;

		// 创建线程的参数
		pthread_t pids[10];
		pthread_attr_t attrs[10];
		for (int i = 0; i < 10; i++)
		{
			pthread_t& pid = pids[i];

			// 设置线程属性
			pthread_attr_t& attr = attrs[i];
			pthread_attr_init(&attr);
			pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

			pthread_create(&pid, &attr, Function_t, NULL);
		}

		for (int i = 0; i < 10; i++)
		{
			// 销毁线程
			pthread_attr_destroy(&attrs[i]);
		}

		cout << "====end=====" << endl;
	}
}
