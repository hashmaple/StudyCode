/********************************************************************
	filename: 	TestSTL
	purpose:	����STL
	created:	2014/10/17
	updated:	2014/10/17
	author:		maple(������)	
*********************************************************************/
#include "TestSTL.h"

#include <algorithm>
#include <functional>
#include <exception>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <ctime>

using namespace std;

// ���Ա�־
BOOL BTEST_SIGN = FALSE;

MySTL::MySTL(void)
{
}

MySTL::~MySTL(void)
{
}

// �������
#define SPRINT(container)	sPrint((container).begin(),(container).end());

//OP����
bool FindValue(int value)
{
	return value % 2 == 0;
}

// �ṹ����
struct TagMyStr
{
	int i;
	string str;

	TagMyStr()
	{
		i = 9527;
		str = "zsq";
	}
};

// ���� <<
ostream& operator << (ostream& s, const TagMyStr& z)
{
	return s << "TagMyStr: " << z.i << " " << z.str;

}

// λ��(���Ƕ���)
struct PPN
{
	int  : 32;
	int nnn: 8;
	bool B : 1;
	bool C : 1;
	int A : 22;
};

const char* PropNameArray[10] = 
{
	"BeAttackTalk",
	"BeginFightTalk",
	"EndFightTalk",
	"SummonTalk",
	"DieTalk",
	"FreeTalk",
	"BeginQiecuoTalk",
	"EndQiecuoTalk",
	"SpecialTalk"
};


/////////////////////////////����ӿ�/////////////////////////////////////////////
// STL
void MySTL::BeginTest()
{
	// io
	if (BTEST_SIGN)
	{
		// ����һ����д�ļ��� ׷��ģʽ
		fstream fs_m;
		fs_m.open("test.ini", ofstream::out | ofstream::in | ios::app);
		if (!fs_m)
		{
			return;
		}

		// д��һ���ַ�
		fs_m << GetTickCount() << endl;

		// ��λ���ļ�ͷ��ʼ��ȡ
		fs_m.clear();
		fs_m.seekp(ios_base::beg);

		string str1, str2;
		fs_m >> str1 >> str2;

		// ��ȡһ��
		getline(fs_m, str1);

		// ����ر� ���ظ�ʹ��fs_m
		fs_m.close();
		// clear any existing errors
		fs_m.clear();

		// string ��
		int val1 = 512, val2 = 1024; 
		stringstream format_message; 
		
		// ���뵽�ַ���
		format_message << "val1: " << val1 << "\n" << "val2: " << val2 << "\n";

		// ����ַ�����������
		format_message >> str1 >> str2;

		// ��ȡ�����ַ�
		string str3 = format_message.str();
	}

	// �ַ���
	if (BTEST_SIGN)
	{
		string s1("testTeSt");
		string s2(10, 'z');
		string s3;

		// sonsole type
		// cin >> s3;

		// תСд auto����Ϊ���� �޸ĺ�Ӱ��ԭ����
		for (auto& temp_char:s1)
		{
			// �Ǵ�д�ĲŴ���
			if (isupper(temp_char))
			{
				s3 += tolower(temp_char);
				temp_char = tolower(temp_char);
			}
		}

		// תСд ����&���� Ϊ���ƵĶ���
		for (auto temp_char:s1)
		{
			// �Ǵ�д�ĲŴ���
			if (islower(temp_char))
			{
				temp_char = toupper(temp_char);
			}
		}
		
		// �ַ�����Ĭ�����0 ����!! ֻ��9��
		for (int i = 0; i < 9 ; i ++)
		{
			const char* pStr = PropNameArray[i];
			string str = PropNameArray[i];
		}
	}

	// bitset
	if (BTEST_SIGN)
	{
		// ���ַ���� 00000000000...111000
		string s1("111000");
		bitset<32> bit(s1);
		cout << bit << endl;

		// ��ȫ0 && ��1
		if (bit.none() == false && bit.any())
		{
			cout << bit.count() << endl;
		}
	}

	// map
	if (BTEST_SIGN)
	{
		// ���ַ�Ҳ���Բ���MAP
		map<string, int> mapTest;
		mapTest[""] = 3;

		// �����ַ�������
		for (int i = 0; i < 1000; i++)
		{
			char buf[16] = {0};
			itoa(i, buf, 10);

			mapTest[buf] = i;
		}

		// ���¿��ַ����ᱻFIND
		string id;
		if (mapTest.find(id) != mapTest.end())
		{
			cout << "���ַ����ᱻFIND"<< endl;
		}
	}

	// VECTOR
	if (BTEST_SIGN)
	{
		int j;

		vector<int> vct1;
		// Ϊ��ʱ�� ��ָ�����һ��Ԫ�ص���һ��
		if (vct1.begin() == vct1.end())
		{
			vct1.push_back(1);
		}

		vector<int> vct_num(10, 5);
		// Խ��BUG
		// j = vct_num[-1];
		// �׳��쳣
		// j = vct_num.at(-1);

		vector<int>::iterator k = std::find(vct_num.begin(), vct_num.end(), 5);
		
	}

	// λ��(���Ƕ���) int���������ٶȿ�!
	if (BTEST_SIGN)
	{
		PPN my_test;
		my_test.A = 0;
		my_test.nnn = 0;
		my_test.B = 0;
		my_test.C = 1;
		int i = sizeof(my_test);

		i = sizeof(i);
	}

	// �ַ���
	if (BTEST_SIGN)
	{
		// �ַ����Χ
		string sas;
		string::size_type size = sas.max_size();

		// �������
		cerr << "x = 1" << '\n';

		// �Զ������
		TagMyStr my;
		cout << my;
	}

	// �쳣����
	if (BTEST_SIGN)
	{
		try
		{
			vector<int> vct;
			vct.resize(10,0);
			int i = vct.at(10);
		}
		catch (exception& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "error: ...";
		}
	}

	//vector
	if (BTEST_SIGN)
	{
		std::vector<int> vctInt;
		vctInt.reserve(10);
		vctInt.resize(10,0);
		for (size_t i = 0; i < 10 ; i ++)
		{
			vctInt.at(i) = i;
		}

		// 20λ1
		vctInt.clear();
		vctInt.resize(20,1);

		// 21λ5
		vctInt.assign(21, 5);
		SPRINT(vctInt);

		for (int i = 0; i < 9; i++)
		{
			vctInt.push_back(i);
		}

		//OP on the all values
		//for_each(vctInt.begin(),vctInt.end(),bind2nd<>(Add, 2));

		//find the counts of explicit value
		int nCount1 = std::count(vctInt.begin(), vctInt.end(), 2);
		int nCount2 = std::count_if(vctInt.begin(), vctInt.end(), FindValue);


		//find min or max value's point
		int minValue = *std::min_element(vctInt.begin(),vctInt.end());
		int maxValue = *std::max_element(vctInt.begin(),vctInt.end());


		//std::search_n(vctInt.begin(), vctInt.end(), vctInt.size(), int(2));

		std::list<int> vctInt2;


		std::copy(vctInt.begin(),vctInt.end(),std::front_inserter(vctInt2));
		std::swap_ranges(vctInt.begin(),vctInt.end(),vctInt2.begin());

		std::reverse(vctInt.begin(),vctInt.end());
		SPRINT(vctInt);
		std::random_shuffle(vctInt.begin(),vctInt.end());
		SPRINT(vctInt);
		std::sort(vctInt.begin(),vctInt.end());
		SPRINT(vctInt);
	}


	//�� last in first out
	if (BTEST_SIGN)
	{
		std::stack<int> stk;
		stk.push(1);
		stk.push(2);
		stk.push(3);
		stk.pop();
		stk.pop();

		if (stk.empty() == false)
		{
			std::stack<int>::value_type nTop = stk.top();
		}
	}
	

	//���� first in first out
	if (BTEST_SIGN)
	{
		std::queue<int> que;
		que.push(1);
		que.push(2);
		que.push(3);
		que.pop();
		que.pop();
		if (que.empty() == false)
		{
			std::queue<int>::value_type nTop = que.front();
			std::queue<int>::value_type nBack = que.back();
		}
	}
	


	//���ȶ��� first in first out
	if (BTEST_SIGN)
	{
		std::priority_queue<int> priQue;
		priQue.push(1);
		priQue.push(2);
		priQue.push(3);
		priQue.pop();
		priQue.pop();
		if (priQue.empty() == false)
		{
			std::queue<int>::value_type nTop = priQue.top();
		}
	}
	

	//bool array <set / reset>
	if (BTEST_SIGN)
	{
		std::bitset<10> bitSet;
		bitSet.set();

		// ��b����pos���Ķ�����λ��Ϊ0
		bitSet.reset(1);
		bool a0 = bitSet[0];
		bool a1 = bitSet[1];
		bool a2 = bitSet[2];

		bitSet[3] = 0;
		bool a3 = bitSet[3];
		bool a4 = bitSet[4];

		// b����Ϊ1�Ķ�����λ�ĸ���
		int n = bitSet.count();

		// b���Ƿ������Ϊ1�Ķ�����λ��
		int nn = bitSet.any();
	}

	//string
	if (BTEST_SIGN)
	{
		//����
		std::wstring str(L"zsqkyo0");
		std::wstring str1(L"zsqkyo1");
		std::wstring str2 = L"zsqkyo2";
		std::wstring str3 = L"zsqkyo3";
		std::wstring str4(L"zsqkyo4444444",7);
		std::wstring str5(str4,6);
		std::wstring str6(10,'a');

		// ֱ�Ӽ���ֵ �ض���BUG!!!
		string zsqsqs = "asdasd";
		zsqsqs += 123456;
		str += 123456;

		//Ѱ��
		std::wstring::size_type Idx1 = str.find(L"qk");
		std::wstring::size_type Idx2 = str.find('s');
		std::wstring::size_type Idx3 = str.find('t');
		
		//�Ҳ���
		if (Idx3 == std::wstring::npos)
		{
			Idx3 = str.find('q');
		}

		//��ȡ
		str4 = str.substr(0,3);


		//����
		str5 = L"zsqkyo " + str + L"." + L"111";
		const wchar_t* oldStr = str5.c_str();


		//��ȡ
		str6 = str5.substr(0,8);
		const wchar_t oldSubStr[] = L"Hello";
	
		//��С��Χ
		size_t wcharSize = sizeof(oldSubStr);
		size_t wcharLength = wcslen(oldSubStr);
		std::wstring::size_type Size = str6.size();
		std::wstring::size_type maxSize = str6.max_size();
		std::wstring::size_type capSize = str6.capacity();
		
	}

	//�з����޷���
	//�з��ź��޷��űȽ� �з���תΪ�޷���
	//Ϊ�����з����� һ���������޷��űȽ�
	//�޷��������з��ţ�ע���ж����
	if (BTEST_SIGN)
	{
		//���������� ��Ҫ��int ��size_t ���Ǵ����ŵ���
		//����size_tתΪint 
		int num = -5;
		size_t unum = 10;
		
		//�з��� �޷��űȽ�
		//�з�����Ϊ���ţ�����쳣
		bool b1 = num > unum;
		bool b2 = unum > num;

		int i = 1;
		i = int(unum);
	}




	//IOStream
	if (BTEST_SIGN)
	{
		//�������
	/*	size_t a,b;
		while (std::cin>> a >> b)
		{
			std::cout<< a << std::endl;
			std::cout<< b << std::endl;
		}*/

		//�ļ���д
		std::fstream file;
		file.open("1.txt");
		if (file)
		{
			file << "Maple" << std::endl << "Time:" << GetTickCount()/1000/60/24/365;
			file << "������";
		}

		char str[64];
		file.getline(str,64);

		FILE* fp;
		fp = fopen("2.txt", "w+");
		fprintf(fp, "%s", "�����澭");
		fclose(fp);
	}

	//function
	if (BTEST_SIGN)
	{
		//�Ƚ�ǰ��֤��Ϊ��
		const char *p1 = "zsq";
		const char *p2 = "kyo";
		int ret = strcmp(p1,p2);

		//i��ָ��  j�Ǳ���
		int* i,j;
		int z = 10;
		i = &z;
		j = z;

		int x[] = {1,2,3,4,5};
		int y[] = {0,2,3,4,5};
		i = find(x, x+ 5, 2);
		i = find_first_of(x, x+ 5, y, y+5);

		// �ӷ���������
		plus<string> plus_string;
		cout << plus_string("hello", " world1 ");
		cout << plus<string>()("hello", " world2 ");

		// ����������ʹ��,�����ڵ�����
		int a[11] = {2,3,22,12,1,3,4,5,6,7,8};
		sort(a, a+11);
		sort(a, a+11, less<int>());
		sort(a, a+11, greater<int>());

		// �󶨵����������(������)
		ostream_iterator<int> outit(cout, " ");
		copy(a, a+11, outit);

		// С��2��Ԫ�ظ���  �� ��С��10��Ԫ�ظ���
		cout << endl << count_if(a, a+11, bind2nd(less<int>(), 2));
		cout << endl << count_if(a, a+11, not1(bind2nd(less<int>(), 10)));

	}

	//Allocator
	if (BTEST_SIGN)
	{
		std::vector<int> vct;

		vct.push_back(1);
		vct.push_back(2);
		vct.push_back(1);
		std::vector<int>::_Alloc alloc = vct.get_allocator();
	}

	//safe function
	if (BTEST_SIGN)
	{
		//2005���� ��ȫ������_s����
		int i ;
		scanf_s("%d",&i);
		printf_s("scanf_s num = %d",i);
	}

	//runtime type information
	if (BTEST_SIGN)
	{
		int i =10;
		int *p = &i;

		//����ָ����߶�����ֵ
		if (typeid(*p) == typeid(i) && typeid(p) == typeid(&i))
		{
			std::cout<< "typeid(p) == typeid(&i)" <<std::endl;
		}
			
		//����ָ����߶�����ֵ
		if (typeid(*p) == typeid(int) && typeid(i) == typeid(int))
		{
			std::cout<< "typeid(p) == typeid(int)" <<std::endl;
		}
	}

	//template
	if (BTEST_SIGN)
	{
		double key = 11;
		float i = sPower(key);
	}

	//random num
	if (BTEST_SIGN)
	{
		//ͳ���漴��
		//�ȼ�¼
		std::vector<int> VctNums(100, 0);

		//����
		std::map<int, std::vector<int>> mapNums;
		//Ĭ�Ϲ���
		for (int i = 0; i < 10; i ++)
		{
			mapNums[i].resize(100, -1);
		}

		//ѡ���ȥ
		for (int i = 0; i < 100; i ++)
		{
			//��ѡ��Ϊ0~9
			int swtichNum = (VctNums[i])/100;
			mapNums[swtichNum].at(i) = VctNums[i];
		}

		//���д�ӡ
		std::map<int, std::vector<int>>::iterator it = mapNums.begin();
		while(it != mapNums.end())
		{
			//ֻ�ܴ�ӡ75��
			for (int i = 0 ; i < 75; i ++)
			{
				if (it->second.at(i) == -1)
				{
					std::cout << "-";
				}
				else
				{
					std::cout << "1";
				}
			}
			
			//������
			std::cout << std::endl;
			it++;
		}
		
	}

	//strstr
	if (BTEST_SIGN)
	{
		// �ַ�����
		const char* a1 = "zsqkyo!!!";
		static char* a2 = "zsqkyo!!!";
		const char a3[] = "zsqkyo!!!";
		static char a4[] = "zsqkyo!!!";

		// �����С����
		int i = sizeof(a1);
		i = sizeof(a2);
		i = sizeof(a3);
		i = sizeof(a4);

		// ��ȷ�ַ�����
		i = strlen(a1);
		i = strlen(a2);
		i = strlen(a3);
		i = strlen(a4);

		// ΪNULL������ֱ��[0]У��
		const char* secName = "a"; //NULL;
		if (secName[0] == 0)
		{
			int i=1;
		}

		// ���ܷ���
		std::wstring  str1 = GetWString();
		const TCHAR * q   = str1.c_str();

		// ��Ч�ַ�
		const TCHAR * p   = GetWString().c_str(); 

		// ���Ϸ���
		std::vector<int> vct1 = GetVector();
		std::vector<int> vct2 = GetVector(); 
		int nVar1 = vct1.at(2);
		int nVar2 = GetVector().at(2);

		// �ַ�����
		std::string p1 = "abcdefg";
		std::string p2 = "f";
		std::string p3 = std::strstr(p1.c_str(), p2.c_str());
	}

}


///////////////////////////////�ڲ�����///////////////////////////////////////////
//����
void MySTL::Add(int& value, int addvalue)
{
	value += addvalue;
}

// �������
template<class _FwdIt1>
inline bool MySTL::sPrint(_FwdIt1 _First1, _FwdIt1 _Last1)
{	

	for (;_First1 != _Last1; ++_First1 )
	{
		std::cout<< *_First1 <<"  ";
	}

	std::cout<<"\n";

	return true;
}

// ������У��ĳ˷�
template<class power>
power MySTL::sPower(power value)
{
	//RTTIУ������
	if (typeid(power) == typeid(int))
	{
		std::cout << "typeid(power) == typeid(int)" << std::endl;
	}
	return value * value;
}


// ����STRING
std::wstring MySTL::GetWString()
{
	std::wstring q = L"zsq";
	return q;
}
// ����VECTOR
std::vector<int> MySTL::GetVector()
{
	std::vector<int> q;
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);
	return q;
}

