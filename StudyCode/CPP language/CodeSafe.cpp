/********************************************************************
	filename: 	CodeSafe
	purpose:	C C++ ��ȫ����
	created:	2014/10/21
	updated:	2014/10/21
	author:		maple(������)	
*********************************************************************/
#include <float.h>
#include <math.h>
#include <time.h>
#include <windows.h>

// ������Χ����
#include "limits.h"

#include <stdarg.h>

#include <iostream>
#include <fstream>

#include <map>
#include <string>
using namespace std;

/// \brief  ���64λ�ĵ�ǰʱ��,��ȷ��ms��ע���ȡ������UTCʱ��
__time64_t util_get_time_64()
{
	SYSTEMTIME stm;
	FILETIME ftm;
	::GetSystemTime(&stm);
	::SystemTimeToFileTime(&stm, &ftm);

	__time64_t now = ftm.dwHighDateTime;
	now = ((now << 32) | ftm.dwLowDateTime) / 10000;

	return now;
}


// ��κ��� ��ȡ�ͻ�ȡ!!
bool test_args(int begin, ...)
{
	va_list arglist;

	va_start(arglist, begin);

	char* arg1 = va_arg(arglist, char*);
	int arg2   = va_arg(arglist, int);
	char* arg3 = va_arg(arglist, char*);
	int arg4   = va_arg(arglist, int);

	va_end(arglist);

	return false;
}

struct TagTest
{
	int nNum;
	char p;

	TagTest()
	{
		nNum =1;
		p = 0;
	}
	~TagTest()
	{
		p = 1;
	}
};

struct TagTestEx
{
	int nNum;
	char p;

	~TagTestEx()
	{
		p = 1;
	}
};


TagTest GetStructA()
{
	TagTest tag;
	tag.nNum = 9527;
	return tag;
}

TagTest& GetStructB()
{
	TagTest tag;
	tag.nNum = 9528;
	return tag;
}

const TagTest& GetStructC()
{
	TagTest tag;
	tag.nNum = 9529;
	return tag;
}

const TagTest& GetStructD()
{
	TagTest tag;
	tag.nNum = 9530;
	return tag;
}

int getInt()
{
	int i = 1234;
	return i;
}

// ����ָ������
typedef int* intpoint;

// ��֯�ַ���
inline void Port_SafeSprintf(char* buf, size_t byte_size, const char* info, ...)
{
	va_list args;

	va_start(args, info);

	_vsnprintf(buf, byte_size - 1, info, args);

	buf[byte_size - 1] = 0;
}

// �ַ�������
int FindSubStr(char* main_str, char* sign_str)
{
	// safe check
	if (main_str == NULL || sign_str == NULL || 
		strlen(sign_str) <= 0 || strlen(sign_str) <= 0 ||
		std::strlen(sign_str) >= strlen(main_str))
	{
		return -1;
	}

	// loop find
	int sing_length = strlen(sign_str);
	char* main_p = main_str;
	char* sign_p = sign_str;
	int inc_index = 0;
	for (; *main_p != NULL; ++main_p)
	{
		// seek 2point find
		char a = *main_p;
		char b = *sign_p;
		if (a == b)
		{
			inc_index++;

			if (inc_index == sing_length)
			{
				return main_p - main_str;
			}
			else
			{
				++sign_p;
				continue;
			}
		}
		else
		{
			sign_p = sign_str;
		}
	}

	return -1;
}

struct MyStruct
{
	string name;
	string sex;
	string age;

	MyStruct() : 
		name(""),
		sex(""),
		age(0) // �ض�����
	{}
};

// ����ս�ʱ��
struct ShipBattleTimeData
{
	ShipBattleTimeData()
		: nDay(0),
		nSignUpStart(0),
		nAdjustStart(0),
		nApplyStart(0),
		nMatchStart(0),
		nGameStart(0),
		nGameOver(0)
	{

	}
	int			nDay;					// �ܼ�
	int			nSignUpStart;			// �Ǽǿ�ʼ
	int			nAdjustStart;			// ���俪ʼ
	int			nApplyStart;			// ������ʼ
	int			nMatchStart;			// ƥ�俪ʼ
	int			nGameStart;				// ս����ʼ
	int			nGameOver;				// ս������
};

// Ѫ��������ɫ
enum HideBarNameColor:unsigned int
{
	NAME_COLOR_WHITE = 0xffffffff, // ��ɫ
	NAME_COLOR_RED = 0xfffa646e, // ��ɫ
	NAME_COLOR_YELLOW = 0xffe9e9b1, // ��ɫ
	NAME_COLOR_GREEN = 0xff73e8d8, // ��ɫ
};


// ���Ժ���
bool SafeTest()
{

	int* p = NULL;
	free(p);



	if (false)
	{
		// string��ֵ0 ����
		// string name = 0;

		// �ַ�ָ���'0'�Ƚ�
		const char* szTargetConfigId = "";
		int i = strlen(szTargetConfigId);
		if (NULL == szTargetConfigId || '\0' == szTargetConfigId[0])
		{
			cout << "szTargetConfigId[0]�����ַ�" << endl;
		}
	}
	


	// �����������μ���
	if (false)
	{
		__time64_t begin = GetTickCount64();

		for (int i = 2; i < 100000000; i++)
		{
			double x = (i+i+1.22f) / 1.025f;
		}

		std::cout << "����������: " << GetTickCount64() - begin << endl;

		begin = GetTickCount64();

		for (int i = 2; i < 100000000; i++)
		{
			int x = (i + i + 3) / i;
		}

		std::cout << "��������: " << GetTickCount64() - begin << endl;
	}

	// ���������� ++it ���ܼ���һ��
	if (false)
	{
		map<string, MyStruct> mapTest;
		MyStruct ms;
		ms.name = "maple";
		ms.sex = "male";
		ms.age = "100";
		char buff[32];

		for (int i = 0; i < 1000000; i++)
		{
			sprintf_s(buff, "id=%d", i);
			mapTest.insert(make_pair(buff, ms));
		}

		// ���Ե�������ȡ
		__time64_t begin = GetTickCount64();

		map<string, MyStruct>::iterator it = mapTest.begin();
		for (int i = 0; it != mapTest.end(); ++it)
		{
			i++;
		}

		std::cout << "++it ����: " << GetTickCount64() - begin << endl;

		begin = GetTickCount64();

		it = mapTest.begin();
		for (int i = 0; it != mapTest.end(); it++)
		{
			i++;
		}

		std::cout << "it++ ����: " << GetTickCount64() - begin << endl;
	}

	// �ַ�������
	if (false)
	{
		__time64_t begin = GetTickCount64();

		string name;
		for (int i = 0; i < 1000000; i++)
		{
			name = "kyooooo";
		}

		__time64_t end = GetTickCount64();

		cout << "ѭ���ⶨ��string����������: " << end - begin << endl;

		//////////////////////////////////////////////////////////////////////////
		begin = GetTickCount64();

		for (int i = 0; i < 1000000; i++)
		{
			string name = "kyooooo";
		}

		end = GetTickCount64();

		cout << "ѭ���ڶ���string����������: " << end - begin << endl;
	}

	// strstr
	if (false)
	{
		int i1 = FindSubStr("zsqkyozsqkyo", "sq");
		int i2 = FindSubStr("zsqkyozsqkyo", "f");
	}

	// �ַ�����ȫ

	if (false)
	{
		const char* pStr = "abcdefghijklmn";

		char ch[10],*p = NULL;
		char *q = NULL;

		strncpy(ch, pStr, 10);


		p = strrchr(ch,'e');

		q = strrchr(ch,'h');

		int i1 = strlen(ch);
		int i2 = strlen(p);
		int i3 = strlen(q);
		int i4 = strlen(pStr);


		string temp1 = p;
		string temp2 = q;

		string abc = temp1 + temp2;


	}

	// ��������ʧ����
	if (false)
	{
		float f1 = 12345129.999f;
		float f2 = 12345129.99f;
		float subf1f2 = f1 - f2;

		double df1 = 12345.12999f;
		double df2 = 12345.1299f;
		double subdf1df2 = df1 - df2;

		double d1 = 12345.12999;
		double d2 = 12345.1299;
		double subd1d2 = d1 - d2;

		bool b3 = (f1 < (f2 + 0.00001f)) && (f1 > (f2 - 0.00001f));
		bool b32 = (f1 < (f2 + FLT_EPSILON)) && (f1 > (f2 - FLT_EPSILON));

		double f2p = f2 + 0.00001f;
		double f2s = f2 - 0.00001f;

		bool b4 = fabs(f1 - f2) < FLT_EPSILON;

		cout << f1 << endl << f2 ;

		bool b5 = memcmp(&f1, &f2, sizeof(f2)) == 0;

		// ��ֵ��ȫ
		f1 = f1 - 1.0f;
		f1 = f1 - 10.0f;
		f1 = f1 - 100.0f;

		f2 = f2 - 1.0f;
		f2 = f2 - 10.0f;
		f2 = f2 - 100.0f;
	}
	
	// ���Ͷ���
	if (false)
	{
		// AB����ָ��
		intpoint A, B;

		// a��ָ�� b������
		int* a, b;
	}

	// ���ʻ�
	if (false)
	{
		locale loc0;
		locale loc1 = locale();
		locale loc2("");
		locale loc3("C");
	}

	// ���Է���
	if (false)
	{
		TagTest& tagA = GetStructA();

		// BCD����ֺ���������� ��Ϊָ��ջ�ϵ�ַ.
		TagTest& tagB = GetStructB();
		const TagTest& tagC = GetStructC();
		const TagTest& tagD = GetStructD();
		// ������ BCD��ָ��ΪD.

		// ���ᵼ��BCD�����쳣
		int temp_i = getInt();

		tagA.nNum++;
		tagB.nNum++;
	}

	// ���ȼ�  .��[] > *
	if (false)
	{
		TagTest* p = new TagTest();
		int i = (*p).nNum++;	// iΪnNum��ֵ ���ú��
		int j = ++(*p).nNum;	// jΪnNum+1��ֵ �ȼӺ���
	}

	// [2011/9/2 Maple(������)]
	// [needfix �����ַ�����ȫ]
	if (false)
	{
		// ����BUG
		char ch[3];
		cin.width(3+1); // ������Ҫ:��������
		cin>>ch;
		cout << ch;
		puts(ch);
		int str_lengh = strlen(ch);

		// �ս�β
		char a[16];
		strcpy(a, "1234567890123456");
		printf("a = %s", a);\

		// ֱ������Խ�� 
		a[16] = 'a';
	}

	// gets
	char buff[12];
	if (false)
	{
		// ���±���
		// gets(buff);		

		// ��ȫ���(�ض�)
		if (fgets(buff, 12, stdin) == NULL)
		{
			abort();
		}

		// ��ȫ���(λ������ ����)
		if (gets_s(buff, 12) == NULL)
		{
			abort();
		}
	}
	
	// memcpy
	if (false)
	{
		char buff1[2];
		string str = "abcdef";

		// ȫ������(��BUG)
		memcpy(buff1, str.c_str(), 13);

		// �޷��ŵĵط� ������ܴ�
		int len = atoi("-2");
		memcpy(buff1, "123456789", len);

		// ����������(������BUG)
		memcpy_s(buff1, 3, str.c_str(), 3);
	}

	#define SPRINTF_S(buf, str, ...) sprintf_s(buf, sizeof(buf), str, __VA_ARGS__)
	
	// strcpy
	// strcat
	if (false)
	{
		try
		{
			char a[3];
			strncpy_s(a, 8, "scsidesk", 8);

			// ����ȫ ��������
			sprintf_s(a, 2, "a");

			// ����
			strcpy(a, "abcde"); // ����
			strcat(a, "ABCDE"); // ׷��

			// �д��󱨸� ����ַ�������
			strcpy_s(a, 2, "abcde");

			// �д��󱨸� ����ַ�������
			strcat_s(a, 4, "AB");

			// ��ȫ
			strncpy(a, "abcde", 4);
			a[4] = '\0';

			// ��ȫ
			strncat(a, "abcde", 4);
			a[4] = '\0';

			strncpy_s(a, 2 + 1, "ab", 2); // DES�ĳ��� ����Ϊ ���Ƶĳ��� + 1 ���������.
			// ��ȫ �Զ��ӽ�β 
			strncpy_s(a, "abcde", 5-1);

			// ��ȫ �Զ��ӽ�β
			strncat_s(a, "abcde", 5-1);
		}
		catch (...)
		{
			int NeverComeHere = 0;
			return false;
		}
		
	}

	// stllen
	if (false)
	{
		char a[2];
		strcpy(a, "abcde"); 
		a[5] = 's';

		// �޽������� ������
		int str_count = strlen(a);
		str_count = strnlen(a, 10);
		str_count = strnlen_s(a, 10);
	}

	// ��ȫ����
	if (false)
	{
		// STL��
		string str;
		cin >> str;

		// �е�����
		const char* pstr1 = str.data();
		const char* pstr2 = str.c_str();
	}


	// �ǵ�ע��
	if (false)
	{
		// �ַ��Ƚ�
		const char* pStr = "";
		if (pStr == "")
		{
			int NeverComingHere = 0;
			NeverComingHere++;
		}

		// �ַ��Ƚ�
		const char* pStr2 = "zsq";
		if (pStr2 == "zsq")
		{
			int NeverComingHere = 0;
			NeverComingHere++;
		}

		// ��κ�������
		test_args(1, "zsq", 3, "maple", 5, 6);

		// �����ʽ
		for (int i = 0 ; i < 100 ; i ++)
		{
			// ת����ʾ��: 
			// d/i=������ʮ����
			// f/F=������double
			// s=�ַ������ָ��ֱ�����ַ�Ϊֹ
			// ����� 8λ�� ���㲻��..��2λ����
			printf("%-8.2f",1234.5678);
		}

		// ����
		char* pBuff = new char[2];
		sprintf(pBuff, "12");
		delete(pBuff);

		// ȱ�ٲ��� �Ҷ���ַ����
		printf("%s");
	}

	// ��ȫ�ļ�����
	if (false)
	{
		string filename;
		ifstream ifs;

		cin >> filename;
		ifs.open(filename.c_str());

		if (ifs.fail())
		{
			cout << "error open: " << filename << endl;
		}
		else
		{
			cout << ifs.width(); // ???
		}

		ifs.close();
	}

	TagTestEx m_TagTestEx;

	return true;
}


