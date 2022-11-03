﻿//--------------------------------------------------------------------
// 文件名:		Algorithm
// 内  容:		算法测试程序库
// 说  明:		
// 创建日期:	2022年10月31日
// 整理日期:	2022年10月31日
// 创建人:		Mike(周树青)
//--------------------------------------------------------------------
#include "Algorithm.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 宏 打印容器
#define PRINT_ELEMENTS(CONTAINER)  cout << "Container["<< #CONTAINER << "]: "; \
for (const auto& it : CONTAINER) { cout << it << " " ; }; cout << endl << endl;

// 乱序
void rand_array(int A[], int size)
{
	cout << " rand_array " << endl;

	srand((int)time(0));

	for (auto i = 0; i < size; i++)
	{
		auto ex_i = rand() % size;

		auto temp = A[i];
		A[i] = A[ex_i];
		A[ex_i] = temp;
	}
}

// 快速排序
int Paritition1(int A[], int low, int high) 
{
	// 使用low作为哨兵
	int pivot = A[low];

	// low 不超过 high
	while (low < high) 
	{
		// 若右侧大于哨兵 右侧向左移
		while (low < high && A[high] >= pivot) 
		{
			--high;
		}

		// 把右侧的小数 换到low位置(首次为哨兵位置)
		A[low] = A[high];

		// 若左侧小于哨兵 左侧向右移
		while (low < high && A[low] <= pivot)
		{
			++low;
		}

		// 把左侧的大数 换到high位置。
		A[high] = A[low];
	}

	// 
	A[low] = pivot;

	return low;
}

// 快排母函数
void QuickSort(int A[], int low, int high) 
{
	if (low < high)
	{
		// 按标志分左右部分 返回标志位置
		int pivot = Paritition1(A, low, high);

		// 排左边(递归)
		QuickSort(A, low, pivot - 1);

		// 排右边(递归)
		QuickSort(A, pivot + 1, high);
	}
}

// 冒泡排序
void BubbleSort(int A[], int size)
{
	// 每轮的最大者放到最后
	for (auto i = 0; i < size - 1; i++)
	{
		// 每轮 两两对比 大者后移
		for (auto j = 0; j < size - i - 1; j++)
		{
			// 大者后移
			if (A[j] > A[j + 1])
			{
				auto temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
}

// 选择排序
void SelectSort(int A[], int size)
{
	// 每轮的找1个最小的放在头部
	for (auto i = 0; i < size; i++)
	{
		auto min_i = i;

		// 记录最小的坐标
		for (auto j = i + 1; j < size; j++)
		{
			if (A[j] < A[min_i])
			{
				min_i = j;
			}
		}

		// 交换到i的位置
		if (min_i != i)
		{
			auto temp = A[min_i];
			A[min_i] = A[i];
			A[i] = temp;
		}
	}
}

// 对外接口
void Algorithm::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 创建数组
	int nArray[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	int size = sizeof(nArray) / sizeof(int);
	rand_array(nArray, size);
	PRINT_ELEMENTS(nArray);

	// 快速排序 数组 首下标 未下标
	cout << " QuickSort nlogn" << endl;
	QuickSort(nArray, 0, size - 1);
	PRINT_ELEMENTS(nArray);

	rand_array(nArray, size);
	PRINT_ELEMENTS(nArray);

	cout << " BubbleSort n*n" << endl;
	BubbleSort(nArray, size);
	PRINT_ELEMENTS(nArray);

	rand_array(nArray, size);
	PRINT_ELEMENTS(nArray);

	cout << " SelectSort n*n" << endl;
	SelectSort(nArray, size);
	PRINT_ELEMENTS(nArray);
}
