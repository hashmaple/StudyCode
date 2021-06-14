//--------------------------------------------------------------------
// �ļ���:		MyArray
// ��  ��:		����(Array)
// ˵  ��:		��������ͬ���͵����ɱ����������֯��һ��ļ��ϡ�
// ˵  ��:		ʵ�ֳ����㷨: ���,����,ɾ��,����,����,����.
// ˵  ��:		��֧�ֲ�ͬ����,��̬���ݺ���С.�Ա�vector
// ��������:	2021��6��14��
// ��������:	2021��6��14��
// ������:		Maple(������)
//--------------------------------------------------------------------
#pragma once

// ׷���ڴ����
#ifdef _DEBUG
#include <crtdbg.h>
#define NEW ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW ::new
#endif // _DEBUG

// �ڴ������
class TMyAlloc
{
public:
	TMyAlloc() {}
	~TMyAlloc() {}

	// �����ڴ�
	void* Alloc(size_t size) { return NEW char[size]; }
	// �ͷ��ڴ�
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

	/////////////////////////////���캯��//////////////////////////////////////////////
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

	// �ο�vectorʵ�ֺ���
public:
	bool push_back(const TYPE& value);

	bool remove(const TYPE& value);

	bool Delete(const TYPE& value);

	bool Find(const TYPE& value);

	bool Insert(size_t index, const TYPE& value);

	bool SetValue(size_t index, const TYPE& value);

	// �ɴ��������㷨
	bool Sort();

	/////////////////////////////�ڲ�����/////////////////////////////////////////////
private:
	size_t m_nSize;
	size_t m_nCapacity;

	TYPE* m_pData;
	TMyAlloc m_TAlloc;
};
