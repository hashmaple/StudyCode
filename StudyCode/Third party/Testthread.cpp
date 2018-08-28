//--------------------------------------------------------------------
// �ļ���:		Testthread
// ��  ��:		ʹ��ͨ�õ�PTHREAD��д���԰���
// ˵  ��:		�Ա� C++thread����ѧϰ
// ��������:	2017��5��8��
// ��������:	2017��5��8��
// ������:		Maple(������)
// ��Ȩ����:	������ţ���ֿƼ��ɷ����޹�˾
//--------------------------------------------------------------------
#include "Testthread.h"

#include <stdio.h>  
#include <iostream>
#include <process.h>
#include <windows.h>

using namespace std;

// 1 VC++Ŀ¼->����Ŀ¼ include
#include <pthread.h>

// 2 ����lib���ӿ� Ҳ���԰����� ������->����->����������
//#pragma comment(lib, "pthreadVC2.lib")

// 3 ��dll�ļ����������ɵ�.exe���ڵ��ļ�����


void* Function_t(void* Param)
{
	pthread_t myid = pthread_self();
	cout << "pthread-" << (int)myid.p%100 << endl;
	return NULL;
}

pthread_key_t p_key;

// ִ�к���
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

// ����ӿ�
void Testthread::BeginTest()
{

	// ��������򵥵ĺ���
	if (false)
	{
		pthread_t tid1, tid2;
		int a = 1;
		int b = 2;
		printf("hello\n");

		// �����߳�����
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

		// �����߳� ID, �߳�����, �̺߳���,��������
		pthread_create(&tid1, &attr, childFun, &a);
		pthread_create(&tid2, NULL, childFun, &b);

		// ���ڴ����߳�˽�е�����
		// pthread_key_create();
		// pthread_key_delete();


		Sleep(1000);

		printf("main thread exit\n");
	}

	if (false)
	{
		cout << "====begin===== " << endl;

		// �����̵߳Ĳ���
		pthread_t pids[10];
		pthread_attr_t attrs[10];
		for (int i = 0; i < 10; i++)
		{
			pthread_t& pid = pids[i];

			// �����߳�����
			pthread_attr_t& attr = attrs[i];
			pthread_attr_init(&attr);
			pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

			pthread_create(&pid, &attr, Function_t, NULL);
		}

		for (int i = 0; i < 10; i++)
		{
			// �����߳�
			pthread_attr_destroy(&attrs[i]);
		}

		cout << "====end=====" << endl;
	}
}
