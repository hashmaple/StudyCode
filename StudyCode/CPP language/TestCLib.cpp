//--------------------------------------------------------------------
// �ļ���:		TestCLib
// ��  ��:		C���Կ�
// ˵  ��:		https://zh.cppreference.com/w/cpp
// ��������:	2011��8��18��
// ������:		Maple(������)
// ��Ȩ����:	
//--------------------------------------------------------------------
#include <stdio.h>	// ���������
#include <math.h>	// ��ѧ������
#include <ctype.h>  // �ַ�������
#include <string.h>	// �ַ���������
#include <io.h>		// �������������
#include <conio.h>	// ����̨IO������
#include <assert.h>	// DEBUG��
#include <signal.h> // �źſ�
#include <time.h>   // ʱ���
#include <stdlib.h> // ��׼���߿�

#pragma warning(disable:4996)

#include <string>
#include <iostream>
using namespace std;

// ���Ժ���
bool TestCLib()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// ����
	int myint;
	float myfloat;
	double mydouble;

	// ��ȡ�ļ�
	FILE *pFile;
	char mystr[256] = {};

	// stdio��
	if (false)
	{
		// �ַ�����
		sprintf_s(mystr, "zsqsqsq%c", 'f');

		// д���ļ�
		fopen_s(&pFile, "test.txt", "wb");
		putc('s', pFile);
		putwc(65, pFile);

		// �ļ�ָ�����¶�λ����ͷ
		rewind(pFile); 

		fclose(pFile);

		// ��ȡ�ļ�
		fopen_s(&pFile, "test.txt", "rb");
		char ch = getc(pFile);
		char num = getc(pFile);
		fclose(pFile);

		// ɾ���ļ�
		remove("test.txt");

		//char ch = getc(stdin); // ��ȡ�ַ�
		//char ch = getchar();	 // ��ȡ�ַ�
		//putchar('s');			 // ����ַ�
		//puts("this is maple's test");/ ����ַ���
		gets_s(mystr);	// ��ȡ�����ַ���
		puts(mystr);	// ����ַ���������̨

		perror("���������Ϣ!!!");
	}

	// math��
	if (false)
	{
		// ��ƽ����
		mydouble = sqrt(16.0f);

		// ֱ��������б��
		mydouble = hypot(3, 4);

		// ����ƴ��
		//string py = pyfc("����ƴ��");

		// ȡ��
		myint = fmod(13.5, 2);    // 1
		mydouble = fmod(13.5, 2); // 1.5

		// ȡ��
		myint = ceil(1.7f);  // 2
		myint = floor(1.7f); // 1


		myint = asin(0.5f);
		myint = acos(0.5f);

		// ��������ֵ
		myint = abs(-11);

		// �������ֵ
		myfloat = fabs(-1.22f);
	}
	
	// �ַ�������
	if (false)
	{
		// ���ֻ��ַ�
		int is_char_num = isalnum('2');

		// Ӣ����ĸ
		int is_english = isalpha('s');
	}

	// �ַ���������
	if (false)
	{
		// �ַ�����
		myint = strlen("how long it is?");

		// �ַ�����
		myint = strcspn("this is maple", "maple");

		// ���Ϊ0 ����>0 С��<0
		myint = strcmp("this", "this");

		// ���Ϊ0 ����>0 С��<0 �����ִ�Сд
		myint = _stricmp("this", "tHis");

		// �ַ�׷��
		strcat(mystr, "this is");

		// �ַ���COPY
		strcpy(mystr, "asdasd");
	}
	
	// �������������
	if (false)
	{
		// �� �ر� �����ļ�
		myint = _open("test.txt", 1);
		myint = _creat("test.txt", 2);
	}

	// ����̨IO��
	if (false)
	{
		// ���
		_cputs("asdasd");

		// �޻��Ի�ȡ�ַ�
		char putch = _getch();
	}

	// DEBUG��
	if (false)
	{
		// ����
		assert(1);
	}
	
	// �ڴ�� mem.h
	if (false)
	{
		// �ڴ�����
		char chA[128];
		memset(chA, 's', 128);

		// �ڴ渳ֵ
		char chB[128] = {0};
		memcpy(chA, chB, 128);
	}
	
	// �źź�����
	if (false)
	{
		// �ȴ��ͷ���
		signal(1, NULL);
		raise(SIGABRT_COMPAT);
	}

	// ʱ���
	if (false)
	{
		// ȡʱ�����ʵ
		time_t now_time = time(NULL);
		string str = ctime(&now_time);

		// ȡʱ������
		tm* t_time = localtime(&now_time);
		str = asctime(t_time);
	}

	// ��׼���߿�
	if (false)
	{
		// ִ��DOS����
		system("dir");

		// ������ �̺���
		div_t my_div;
		my_div = div(10,3);

		// ת��
		myint = atoi("111.65");			// �ַ���תΪint
		long mylong = atoi("47523658");	// �ַ���תΪlong
		_itoa(111, mystr, 10);			// ����ת�ַ���

		// �쳣��ֹ
		abort();

		// ��ֹ����
		exit(0);

		// ��ʼ���������
		time_t t;
		srand((unsigned)time(&t));

		// ȥ�漴��
		for (int i = 0; i < 100; i ++)
		{
			printf("%d\t", rand()%100);
		}

		// �������洢���ڴ�
		char* ch_str = NULL;
		//ch_str = (char*)calloc(128, sizeof(char));  // �������洢���ڴ�
		ch_str = (char*)malloc(128);
		printf("point address: %p\n", ch_str);
		ch_str = (char*)realloc(ch_str, 24);
		printf("point address: %p\n", ch_str);
		strcpy(ch_str, "this is my str!!");
		free(ch_str);
	}

	return true;
}

// ���Ӿ�̬lib�� ������ ���� ���������(������Ҫ,lib���� ���ɺ�ʱ��:copy����)
// #pragma comment(lib,"MyStaticLib.lib") 
// 
// ������̬���еĺ���������������
#include "..\MyStaticLib\MyStaticLib.h"
#include "..\MyStaticLib\MyLibClass.h"

// ���Ծ�̬��
void TestMyStaticLib()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// ���Ծ�̬��
	if (0)
	{
		// ���þ�̬�⺯��
		cout << "call MyStaticLib.lib fnMyStaticLib:" << endl;

		fnMyStaticLib();

		cout << "call MyStaticLib.lib AddByStaticLib = " << AddByStaticLib(1, 2) << endl;

		// �������ٶ���MyLibClass �ᱨ��
		// ������ͬʱ����,����link��˭��˭.ֻ��һ��MyLibClass.
		// ���ޱ�����,����lib�еĶ���
		MyLibClass myclass;
		cout << "call MyStaticLib.lib MyStaticLibClass GetNumber() = " 
			<< myclass.GetNumber() << endl;

		// ������,�򱨴�	LNK1169	�ҵ�һ���������ض���ķ���
		// myclass.GetNumber2();
	}
}