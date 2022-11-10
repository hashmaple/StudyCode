//--------------------------------------------------------------------
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

inline void printArray(int A[], int size)
{
	cout << "printArray : ";

	for (auto i = 0; i < size; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

// 乱序
void rand_array(int A[], int size)
{
	cout << " rand_array " << endl;

	Sleep(2);
	srand((int)time(0));

	for (auto count = 0; count < 7; count++)
	{
		for (auto i = 0; i < size; i++)
		{
			auto ex_i = rand() % size;

			auto temp = A[i];
			A[i] = A[ex_i];
			A[ex_i] = temp;
		}
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

		printArray(A, size);
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

		printArray(A, size);
	}
}

// 插入排序
void InsertSort(int A[], int size)
{
	// 一个数据插入到已排序的数据中（模拟扑克抓牌）
	for (auto i = 1; i < size; i++)
	{
		// 等待插入的数值
		int insert_value = A[i];
		int j = i;

		// 从尾端判断，若小就移出来
		while (j > 0 && A[j-1] > insert_value)
		{
			// 不断后移，空出位置
			A[j] = A[j - 1];
			j--;
		}

		// 空位放入
		A[j] = insert_value;

		printArray(A, size);
	}
}

// 递归recursion
int Fibonacci(size_t n)
{
	if (n == 0)
	{
		return 0;
	}

	if (n == 1)
	{
		return 1;
	}

	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

// 动态规划Dynamic Programming
int FibonacciDP(size_t n)
{
	if (n == 0)
	{
		return 0;
	}

	if (n == 1)
	{
		return 1;
	}

	int a = 0, b = 1;

	for (size_t i = 0; i < n - 1; i++)
	{
		b = b + a; // b为前2值相加
		a = b - a; // a为前b值
	}

	return b;
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

	// 排序算法
	if (1)
	{
		// 快速排序 数组 首下标 未下标
		cout << " QuickSort nlogn" << endl;
		QuickSort(nArray, 0, size - 1);
		PRINT_ELEMENTS(nArray);

		rand_array(nArray, size);
		PRINT_ELEMENTS(nArray);

		// 冒泡排序 每次找最大值换到最前面
		cout << " BubbleSort n*n" << endl;
		BubbleSort(nArray, size);
		PRINT_ELEMENTS(nArray);

		rand_array(nArray, size);
		PRINT_ELEMENTS(nArray);

		// 选择排序 每次找1个最大/小值 换1次位置
		cout << " SelectSort n*n" << endl;
		SelectSort(nArray, size);
		PRINT_ELEMENTS(nArray);

		rand_array(nArray, size);
		PRINT_ELEMENTS(nArray);

		// 插入排序 每次插入1个 一直保持有序
		cout << " InsertSort n*n" << endl;
		InsertSort(nArray, size);
		PRINT_ELEMENTS(nArray);

		rand_array(nArray, size);
		PRINT_ELEMENTS(nArray);
	}

	// 其他算法
	if (0)
	{
		// Fibonacci数列
		for (size_t i = 0; i < 10; i++)
		{
			cout << "Fibonacci " << i << " = " << Fibonacci(i) << endl;
			cout << "FibonacciDP " << i << " = " << FibonacciDP(i) << endl;
		}
	}
}
