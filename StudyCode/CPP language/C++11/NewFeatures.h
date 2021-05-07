/*!
 * \file CNewFeatures.h
 * \date 2018/12/24 14:04
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
#pragma once

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
