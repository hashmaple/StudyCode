/*!
 * \file NewFeatures.cpp
 * \date 2018/12/24 14:05
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief learn c++11 NewFeatures 
 *
 * TODO: long description
 *
 * \note
*/
#include "NewFeatures.h"

#include <vector>
#include <string>

#include <iostream>

using namespace std;

NewFeatures::NewFeatures(void)
{
}

NewFeatures::~NewFeatures(void)
{
}


/////////////////////////////����ӿ�/////////////////////////////////////////////
// NewFeatures
void NewFeatures::BeginTest()
{
	if (false)
	{
		// nullptr �������� ����תΪ����,��תΪ����ָ������. 
		int *p = nullptr;

		// auto �����Զ��Ƶ�. ԭ������Ϊĳ�����Ǿֲ���.
		auto i = 20;

		// һ���Եĳ�ʼ�� ������ʹ�ô�����
		int j{}; // j = 0 ���ʼ��
				 // int k; δ��ʼ�����벻ͨ��
		int values[]{ 1,2,3 };
		vector<int> v = { 2,3,4,5,6 };
		vector<string> vstr = { "zsq", "kyo" };

		// range-based forѭ��
		for (auto it : v) {} // �ḳֵ��it,����һ�ݸ���
		for (auto& it : v) { ++it; } // it������,�����޸�
		for (const auto& it : v) {} // it�ǳ�������,�����޸�

		// std::move() ��Ǩ���� �����ڱ�����Ǩ����ʹ�õ�����.
		int i_move = 1;
		vector<int> v_int1{ 1,2,3,4 };
		vector<int> v_int2(4);
		v_int2 = move(v_int1); // ֱ���ƶ����ݹ���,������һ�θ�������. 
		v_int2.size(); // 4
		v_int1.size(); // 0 ����δָ��,����Ч��״̬ move���ô�����,�÷���ȷ!

					   // �ַ������泣��
		cout << R"(/N)" << endl;
	}
	
	if (false)
	{
		// lambda []=��ȡ�����ı���   ()�������   ->����ֵ
		int lambda_i = 8;
		int lambda_j = 8;
		auto l = [lambda_i, &lambda_j](int i, const string& s) -> int
		{
			cout << "lambda functon call! input args i/s = " << i << s << endl;
			cout << "lambda_i = " << lambda_i << endl;
			lambda_j++;
			cout << "lambda_j = " << lambda_j << endl;
			return 9527;
		};
		// �ȵ���l����,���������ֵ
		cout << "lambda call return = " << l(1, "maple") << endl;
		cout << "lambda_j = " << lambda_j << endl;	// �ں����������ú��Ѿ����޸�
	}

	return;
}
