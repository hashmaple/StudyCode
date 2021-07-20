/*!
 * \file STLContainer.h
 * \date 2019/01/14 17:24
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief C++11的 容器
 *
 * TODO: long description
 *
 * \note
*/
#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

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

