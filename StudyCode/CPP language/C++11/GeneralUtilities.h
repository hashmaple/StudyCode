/*!
 * \file GeneralUtilities.h
 * \date 2018/12/26 11:56
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief C++ ��׼���е�ͨ�ù���
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

	// ����ӿ�
	void BeginTest();

private:
	template <typename T>
	void TypeTrait(T val);
};
