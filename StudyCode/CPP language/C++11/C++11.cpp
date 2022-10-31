/*!
 * \file C++11.cpp
 * \date 2018/12/24 14:05
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief learn c++11 standard code
 *
 * TODO: long description
 *
 * \note
*/
#include "C++11.h"

using namespace std;

/////////////////////////////����ӿ�/////////////////////////////////////////////
// CPP11
void CPP11::BeginTest()
{
	/* https://zh.cppreference.com/w/cpp/11
	�������Թ�������
	auto �� decltype
	Ԥ�������õĺ���
	final �� override
	β�淵������
	��ֵ����
	�ƶ����캯�����ƶ���ֵ�����
	��������ö��
	constexpr ����������
	�б��ʼ��
	ί����̳еĹ��캯��
	�����Ż�Ⱥų�ʼ����
	nullptr
	long long
	char16_t �� char32_t
	���ͱ���
	�����ģ��
	�ƹ�ģ���ƽ����������
	�ƹ�� POD ��ƽ���������׼�������ͣ�
	Unicode �ַ���������
	�û�����������
	����
	lambda ���ʽ
	noexcept ˵������ noexcept �����
	alignof �� alignas
	���߳��ڴ�ģ��
	�ֲ߳̾��洢
	GC �ӿ�
	��Χ for ������ Boost �⣩
	static_assert ������ Boost �⣩
	*/

	NewFeatures NF;
	NF.BeginTest();

	GeneralUtilities GU;
	GU.BeginTest();

	STLContainer container;
	container.BeginTest();

	FunAndLambda funLambda;
	funLambda.BeginTest();

	NewString newString;
	newString.BeginTest();

	MultiThread multiThread;
	multiThread.BeginTest();

	return;
}
