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
