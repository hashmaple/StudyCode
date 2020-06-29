//--------------------------------------------------------------------
// �ļ���:		C++98
// ��  ��:		ѧϰC++98�ı�׼�������ܵ�
// ˵  ��:		https://zh.cppreference.com/w/cpp
// ��������:	2017��5��2��
// ��������:	2017��5��2��
// ������:		Maple(������)
// ��Ȩ����:	������ţ���ֿƼ��ɷ����޹�˾
//--------------------------------------------------------------------
#include "CPP98.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h> 
#include <set>

// Ϊ��ͨ��������VS2015
#pragma warning(disable:4996)

#include<windows.h>
#include<winbase.h>

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <random>

using namespace std;


// ���ش����ŵ��ַ�
#define to_string( s ) #s

// ����ǰ������
#define abc 100

#define concatenate( a, b ) a##b

// ���ؾ���ֵ
#define absolute_value( x ) ( ((x) < 0) ? -(x) : (x) )

// ���㳤��
#define query_sizeof( x ) #x<< " size is " << sizeof(x) << endl

// ����������
#if !defined(__cplusplus)
#error C++ compiler required.

#endif


CPP98::CPP98(void)
{
}

CPP98::~CPP98(void)
{
}

unsigned long ulrand(void) {
	return (
		(((unsigned long)rand() << 24) & 0xFF000000ul)
		| (((unsigned long)rand() << 12) & 0x00FFF000ul)
		| (((unsigned long)rand()) & 0x00000FFFul));
}



void exit_function(void)

{
	printf("Exit function  called\n");
}

/////////////////////////////����ӿ�/////////////////////////////////////////////
void CPP98::BeginTest()
{
	// �����﷨ �� Ԥ�������  #pragma 
	if (1)
	{
		cout << to_string(HEELO MAPLE!) << endl;


		int xy = 10;
		cout << "print the abc value = " << abc << endl; 
		cout << "print the xy value = " << concatenate(x, y) << endl; // print the xy value = 10;

		cout << "absolute_value is " << absolute_value(-10) << endl;

		cout << " __LINE__ " << __LINE__ << endl <<
			"  __FILE__ " << __FILE__ << endl <<
			"  __DATE__ " << __DATE__ << endl <<
			"  __TIME__ " << __TIME__ << endl;

		cout << query_sizeof(bool) <<
			query_sizeof(char) <<
			query_sizeof(unsigned char) <<
			query_sizeof(signed char) <<
			query_sizeof(int) <<
			query_sizeof(unsigned int) <<
			query_sizeof(signed int) <<
			query_sizeof(short int) <<
			query_sizeof(unsigned short int) <<
			query_sizeof(signed short int) <<
			query_sizeof(long int) <<
			query_sizeof(unsigned long int) <<
			query_sizeof(signed long int) <<
			query_sizeof(float) <<
			query_sizeof(double) <<
			query_sizeof(long double) <<
			query_sizeof(wchar_t);
	}

	// ��׼ C I/O 
	if (false)
	{
		FILE* pFile = fopen("cpp98.ini", "w+");
		if (pFile == NULL)
		{
			return;
		}

		if (fputs("this is cpp98.ini", pFile) == EOF)
		{
			fclose(pFile);
			return;
		}

		// ��ȡǰָ���ƶ����ļ�ͷ
		rewind(pFile);

		// ��ȡ
		char c = fgetc(pFile);
		while (c != EOF)
		{

			cout << c;
			c = fgetc(pFile);
		}

		fclose(pFile);
	}

	// ��׼c�ַ����ַ���
	if (false)
	{
		cout << atof("42.01is_the_answer") << endl;
		cout << atoi("42.91is_the_answer") << endl; // ����������

		char buff[32] = "China have the";
		cout << "�ַ������� strcat " << strcat(buff, " the Great") << endl; //catenate string

		char* p = strstr(buff, " the Great"); // �Ҳ������ؿ�ָ��
		if (p)
		{
			cout << "�ַ������� strstr(buff, \" the Great\") result is " << p << endl; //find the string pos 
		}

		// С��С��0 ����Ϊ0 ���ڴ���0
		cout << "�ַ����Ƚ� strcmp " << strcmp("zsq", "zsqkyo") << endl;

		cout << "�ַ�Сд�� strlwr " << _strlwr(buff) << endl;	
	} 

	// Standard C Math
	if (false)
	{
		cout << "abs -1 is " << abs(-1) << endl;
		cout << "fabs -1.2 is " << fabs(-1.2) << endl;
		cout << "acos -0.5 is " << acos(-0.5) << endl;
		cout << "asin -0.5 is " << asin(-0.5) << endl;
		cout << "sin -0.5 is " << sin(-0.5) << endl;


		cout << "���ز�С��num ����С���� ceil 8.5 is " << ceil(8.5) << endl;
		cout << "���ز�����num ����С���� floor 8.5 is " << floor(8.5) << endl;

		cout << "��ģ fmod 10, 3 is " << fmod(10, 3) << endl;
		cout << "����� pow 8, 2 is " << pow(8, 2) << endl;
		cout << "��ƽ���� sqrt 9 is " << sqrt(9) << endl;

		// ���ز���numerator / denominator���̺�����
		div_t temp;
		temp = div(10, 3);
		printf("%d divided by %d yields %d with a remainder of %d\n", 10, 3, temp.quot, temp.rem);
	}

	// ��׼cʱ�������ں���
	if (false)
	{
		time_t now_time = time(NULL);

		//  localtime��������
		// ���ܣ��Ѵ�1970 - 1 - 1������(�������Ǵ�1900�꿪ʼ���)
		// ����ǰʱ��ϵͳ��ƫ�Ƶ�����ʱ��ת��Ϊ����ʱ�䡣
		// ˵�����˺�����õ�tm�ṹ���ʱ�䣬�Ѿ����й�ʱ��ת������Ϊ�˱���ʱ�䡣
		tm* t1 = localtime(&now_time);
		cout << "localtime(����ʱ��) is " << asctime(t1) << endl;

		// gmtime�ǰ����ں�ʱ��ת��Ϊ��������(GMT)ʱ��ĺ���
		// localtime������õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ�䡣
		tm* t2 = gmtime(&now_time);
		cout << "gmtime(��������GMT) is " << asctime(t2) << endl;


		// ��ȡ���صĵ�ǰϵͳ���ں�ʱ�䡣
		SYSTEMTIME st1 = { 0 };
		GetLocalTime(&st1);

		// ��Эͬ����ʱ�䡱����UTC��Ҳ����GMT����ʽ
		SYSTEMTIME st2 = { 0 };
		GetSystemTime(&st2);
	}

	// ��׼c�ڴ溯��
	if (false)
	{
		// ����,����ָ�������ڴ���ԭ����������ȫ��������
		double* p1 = (double *)malloc(1);
		*p1 = 1.1;

		// ����С�����ڴ� �������ڴ�û�г�ʼ�� �������
		int* p2 = (int *)malloc(sizeof(int));
		*p2 = 2;

		// ���� �� 1 X 4����
		int* p3 = (int *)calloc(1, 4);
		*p3 = 3;

		free(p3);
		p3 = NULL;

		free(p2);
		p2 = NULL;

		free(p1); // ��Ϊʹ��Խ��,�����ͷ�ʱ��assert
		p1 = NULL;
	}

	// ������׼c����
	if (0)
	{
		// mainִ�н�������õĺ��� (_exit��_Exit �����������ֹ����
		atexit(exit_function);

		// �����
		srand(time(NULL));    
		for (int i = 0; i < 10000; i++)
		{
			//printf("Random number %d: %d\n", i, rand()%100000);
		}

		// use current time as seed for random generator  #define RAND_MAX 0x7fff
		std::srand(std::time(0)); 
		int uniform_random_variable = std::rand();
		std::cout << "Uniform random value on [0 " << RAND_MAX << "]: "
			<< uniform_random_variable << '\n';

		// 20W�β����������,������Լ��86000������.
		srand(time(NULL));
		set<int> setNum;
		for (int i = 0; i < 200000; i++) 
		{
			int random_num = ulrand() % 100000;
			setNum.insert(random_num);
		}

		cout << "use ulrand 20W count gen " << setNum.size() << endl;

		// C++ 11���������
		set<int> setNum2;
		std::random_device rd;
		std::mt19937 mt(rd());
		for (int n = 0; n < 200000; n++)
		{
			setNum2.insert(mt() % 100000);
		}
		cout << "use C++ 11 mt19937 20W count gen " << setNum2.size() << endl;

		assert(1);

		//exit(0);

		// abort the current program by raising SIGABRT
		//abort();
	}

	return;
}
