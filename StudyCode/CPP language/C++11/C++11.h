/*!
 * \file C++11.h
 * \date 2018/12/24 14:04
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
#pragma once
#include <type_traits>
#include <utility>


class CPP11
{
public:
	// ����ӿ�
	void BeginTest();
};

class NewString
{
public:
	// ����ӿ�
	void BeginTest();
};


class FunAndLambda
{
public:
	// ����ӿ�
	void BeginTest();
};


class GeneralUtilities
{
public:
	GeneralUtilities(void);
	~GeneralUtilities(void);

	// ����ӿ�
	void BeginTest();

private:
	template <typename T>
	void TypeTrait(T val);
};


class MultiThread
{
public:
	// ����ӿ�
	void BeginTest();

	MultiThread() {};
	MultiThread(int) = delete;
};

class NewFeatures
{
public:
	NewFeatures(void);
	~NewFeatures(void);

	// ����ӿ�
	void BeginTest();

	// Ϊ��֧��dynamic_cast �����麯��
	virtual int virFunc()
	{
		return 1;
	}
};

// ����
class SonNewFeatures :public NewFeatures
{
public:
	virtual int virFunc()
	{
		return 2;
	}
};

class NewCPP
{
public:
	NewCPP(void);
	~NewCPP(void);

	// ����ӿ�
	void BeginTest();
};

namespace std
{
	template<> class hash<std::pair<int, int>>
	{
	public:
		size_t operator()(const pair<int, int>& pair_id) const
		{
			return hash<int>()(pair_id.first) ^ hash<int>()(pair_id.second);
		}
	};
}

class STLContainer
{
public:
	STLContainer(void);
	~STLContainer(void);

	// ����ӿ�
	void BeginTest();
};
