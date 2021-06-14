//--------------------------------------------------------------------
// 文件名:		MyArray
// 内  容:		数组(Array)
// 说  明:		将具有相同类型的若干变量有序地组织在一起的集合。
// 说  明:		实现常用算法: 添加,插入,删除,查找,更新,排序.
// 说  明:		可支持不同类型,动态扩容和缩小.对比vector
// 创建日期:	2021年6月14日
// 整理日期:	2021年6月14日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#pragma once

// 追踪内存分配
#ifdef _DEBUG
#include <crtdbg.h>
#define NEW ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW ::new
#endif // _DEBUG

// 内存分配器
class TMyAlloc
{
public:
	TMyAlloc() {}
	~TMyAlloc() {}

	// 申请内存
	void* Alloc(size_t size) { return NEW char[size]; }
	// 释放内存
	void Free(void* ptr, size_t size) { delete[](char*)ptr; }
};

template<typename TYPE>
class MyArray
{
	enum MyEnum
	{
		ARRAY_SIZE = 8,
	};

private:
	typedef MyArray<TYPE> self_type;

	/////////////////////////////构造函数//////////////////////////////////////////////
public:
	MyArray()
	{
		m_nSize = 0;
		m_nCapacity = ARRAY_SIZE;
		m_pData = (int*)m_TAlloc.Alloc(ARRAY_SIZE * sizeof(TYPE));
	}

	MyArray(size_t num = 8)
	{
		m_nSize = num;
		m_nCapacity = num;
		m_pData = (int*)m_TAlloc.Alloc(num * sizeof(int));
	}

	// 参考vector实现函数
public:
	bool push_back(const TYPE& value);

	bool remove(const TYPE& value);

	bool Delete(const TYPE& value);

	bool Find(const TYPE& value);

	bool Insert(size_t index, const TYPE& value);

	bool SetValue(size_t index, const TYPE& value);

	// 可传入排序算法
	bool Sort();

	/////////////////////////////内部数据/////////////////////////////////////////////
private:
	size_t m_nSize;
	size_t m_nCapacity;

	TYPE* m_pData;
	TMyAlloc m_TAlloc;
};
