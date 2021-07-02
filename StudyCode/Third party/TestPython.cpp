//--------------------------------------------------------------------
// 文件名:		TestPython
// 内  容:		
// 说  明:		
// 创建日期:	2020年9月16日
// 整理日期:	2020年9月16日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "TestHeader.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>

#include "Python.h" 
#include <string>
using namespace std;

char* UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}

// 对外接口
void TestPython::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 测试运行PYTHON脚本文件
	if (0)
	{
		cout << "==TestPython::BeginTest===" << endl;

		// 初始化，创建一个Python虚拟环境
		Py_Initialize();
		if (!Py_IsInitialized())
		{
			printf("Python环境初始化失败...\n");
		}

		// 需要使用PYTHON的打开文件函数
		FILE *fp = _Py_fopen("httpserver.py", "r");
		if (fp == NULL)
		{
			return;
		}

		PyRun_SimpleFile(fp, "httpserver.py");

		// 调用结束
		Py_Finalize();

		cout << "==TestPython::End===" << endl;
	}

	// 测试
	if (0)
	{
		cout << "==TestPython::BeginTest===" << endl;

		// 初始化，创建一个Python虚拟环境
		Py_Initialize();              
		if (!Py_IsInitialized())
		{
			printf("Python环境初始化失败...\n");
		}

		PyRun_SimpleString("print('hello world! form C++')");

		// 加载PY脚本
		PyObject*  pModule = PyImport_ImportModule("testpython");
		if (!pModule)
		{
			printf("导入Python模块失败...\n");
		}

		// 获取PY函数
		PyObject* pFunc = PyObject_GetAttrString(pModule, "PyHello");
		if (pFunc)
		{
			// 执行函数
			PyEval_CallObject(pFunc, NULL);   
			pFunc = nullptr;
		}

		// 获取PY函数+传递参数
		pFunc = PyObject_GetAttrString(pModule, "PyAdd");
		if (pFunc)
		{
			// 1 构造参数
			auto pArgs = PyTuple_New(2);
			// 0-序号  i-表示 int型变量 
			PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));
			PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));

			// 2 便捷的构造参数
			auto pArgs2 = Py_BuildValue("ii", 1, 2);
			
			// 执行函数+参数
			auto pRet = PyEval_CallObject(pFunc, pArgs2);

			int num;
			PyArg_Parse(pRet, "i", &num);
			cout << "PyAdd ret =  " << num << endl;
		}

		// 获取类名
		PyObject *pClassPerson = PyObject_GetAttrString(pModule, "MyClass");
		if (pClassPerson)
		{
			//构造类的实例
			PyObject* pInstance = PyInstanceMethod_New(pClassPerson);
			if (pInstance == NULL)
			{
				cout << "Can't find Person instance!" << endl;
				return;
			}

			//调用方法    s表示传递的是字符串,值为"Hello Kitty"(GB2312编码，中文需要转UTF8）
			PyObject_CallMethod(pInstance, "greet", "(Os)", pInstance, "Hello Kitty");

			// 宽字符（UNICODE转UTF8编码后，PYTHON显示正确）
			wchar_t* wCharUnicode = L"中国人";
			char* cCharUtf = UnicodeToUtf8(wCharUnicode);
			PyObject_CallMethod(pInstance, "greet", "(Os)", pInstance, cCharUtf);
			free(cCharUtf);
		}
	
		// 调用结束
		Py_Finalize();

		cout << "==TestPython::End===" << endl;
	}
}
