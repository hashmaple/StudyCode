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
	// 对外接口
	void BeginTest();
};

class NewString
{
public:
	// 对外接口
	void BeginTest();
};


class FunAndLambda
{
public:
	// 对外接口
	void BeginTest();
};


class GeneralUtilities
{
public:
	GeneralUtilities(void);
	~GeneralUtilities(void);

	// 对外接口
	void BeginTest();

private:
	template <typename T>
	void TypeTrait(T val);
};


class MultiThread
{
public:
	// 对外接口
	void BeginTest();

	MultiThread() {};
	MultiThread(int) = delete;
};

class NewFeatures
{
public:
	NewFeatures(void);
	~NewFeatures(void);

	// 对外接口
	void BeginTest();

	// 为了支持dynamic_cast 增加虚函数
	virtual int virFunc()
	{
		return 1;
	}
};

// 子类
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

	// 对外接口
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

	// 对外接口
	void BeginTest();
};
