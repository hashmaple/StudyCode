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
#include <list>
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

// 求N个质数
void CountPrime(size_t n)
{
	std::list<size_t> primes{ 2,3,5,7 };

	// 0,1,2无须处理  3+2+2+2
	for (size_t i = 9; primes.size() < n; i = i + 2)
	{
		bool bPrime = true;

		// 确保都不可整除
		for (auto p : primes)
		{
			if (i % p == 0)
			{
				bPrime = false;
				break;
			}
		}

		if (bPrime)
		{
			primes.push_back(i);
		}
	}

	PRINT_ELEMENTS(primes);
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

constexpr int CHESS_SIZE = 5;
static int FIND_COUNT = 0;
void PrintChess(int A[CHESS_SIZE][CHESS_SIZE])
{
	cout << "==PrintChess==";

	for (int i = 0; i < CHESS_SIZE; i++)
	{
		cout << endl;

		for (int j = 0; j < CHESS_SIZE; j++)
		{
			cout << A[i][j] << " ";
		}
	}

	cout << endl;
}

// 八皇后check
bool CheckSafe(int A[CHESS_SIZE][CHESS_SIZE], int row, int col)
{
	for (auto i = 0; i < CHESS_SIZE; i++)
	{
		// 同列排除
		if (A[row][i] > 0 && i != col)
		{
			return false;
		}

		// 同行排除
		if (A[i][col] > 0 && i != row)
		{
			return false;
		}
	}

	// 正对角线排除
	for (auto i = row - 1,j = col - 1; 
		i >= 0  && j >= 0; i--,j--)
	{
		if (A[i][j] > 0 && i != row && j != col)
		{
			return false;
		}
	}

	// 反对角线排除
	for (auto i= row - 1, j = col + 1;
		i >= 0 && j < CHESS_SIZE; i--, j++)
	{
		if (A[i][j] > 0 && i != row && j != col)
		{
			return false;
		}
	}
	
	return true;
}

// 八皇后
void PlaceChess(int A[CHESS_SIZE][CHESS_SIZE], int row)
{
	// 一行一行的找位置摆放
	for (auto i = 0; i < CHESS_SIZE; i++)
	{
		// 先放下棋子
		A[row][i] = row + 1;

		// 放下OK 继续
		if (CheckSafe(A, row, i))
		{
			// 放下了最后1个
			if (row + 1 == CHESS_SIZE)
			{
				// 打印解法
				PrintChess(A);

				FIND_COUNT++;
			}
			else
			{
				// 继续
				PlaceChess(A, row + 1);
			}
		}

		A[row][i] = 0;
	}
}

// 求n个数中取m个的组合
constexpr int NUM_SIZE = 5;
constexpr int GET_SIZE = 2;
int sign[GET_SIZE] = {};
void dfs_combi(int n, int m)
{
	// 先找最大的数
	for (int i = m; i <= n; i++)
	{
		// 选择第i个元素作为组合的最后1个元素
		sign[m - 1] = i;

		if (m > 1)
		{
			// 不断递归找前一个
			dfs_combi(i - 1, m - 1);
		}
		else
		{
			// m为0 取完m个元素了
			printArray(sign, GET_SIZE);
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

	// 排序算法
	if (0)
	{
		rand_array(nArray, size);
		PRINT_ELEMENTS(nArray);

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

		// 求质数
		CountPrime(10);

		// 8皇后
		int nChess[CHESS_SIZE][CHESS_SIZE] = {};
		PrintChess(nChess);
		PlaceChess(nChess, 0);
		cout << "The Eight Queens find solution count = " << FIND_COUNT << endl;

		// 求n个数中取m个的组合
		dfs_combi(NUM_SIZE, GET_SIZE);
	}
}
