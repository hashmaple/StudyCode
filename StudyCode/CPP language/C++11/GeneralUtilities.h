/*!
 * \file GeneralUtilities.h
 * \date 2018/12/26 11:56
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief C++ 标准库中的通用工具
 *
 * TODO: long description
 *
 * \note

*/#pragma once


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
