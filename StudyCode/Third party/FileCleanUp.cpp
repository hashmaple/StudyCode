#include "TestHeader.h"

#include <io.h>  
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

std::map<size_t, _finddata_t> G_mapfiles;

std::vector<string> G_sameFilePaths;

// 文件寻找函数
void getFiles(string path, std::map<size_t, _finddata_t>& mapfiles)
{
	_finddata_t fileinfo;
	string p;

	intptr_t hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo);

	if (hFile != -1)
	{
		do 
		{
			// 目录就迭代
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					getFiles(p.assign(path).append("\\").append(fileinfo.name), mapfiles);
				}
			}
			else // 文件则加入
			{
				if (mapfiles.find(fileinfo.size) != mapfiles.end())
				{
					G_sameFilePaths.push_back(path + "\\" + fileinfo.name);
				}
				else
				{
					mapfiles[fileinfo.size] = fileinfo;
				}
			}
		}
		while (_findnext(hFile, &fileinfo) == 0); 
		// _findnext 文件名太长和目录一起超过260 就会断言
		// 判断文件名长度大约超过100 就通过Python处理
	}
}

// 对外接口
void FileCleanUp::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 目录+文字长度超过260 通过pyhton处理 
	if (0)
	{
#		/* 
		-*- coding:utf-8 -*-
		import os
		from shutil import copyfile

		for root, dirs, files in os.walk(r"F:\05 学习教材\6 KINDLE书") :
			for file in files :
				if len(file) > 100:
					print(file)
					print(os.path.join(root, file))
					# 复制到 copyfile(os.path.join(root, file), os.path.join(r"F:\123", file))
					# 删除 os.remove(os.path.join(root, file))
		*/
	}

	// 文件解析JSON
	if (0)
	{
		// 遍历文件夹
		getFiles(R"(F:\05 学习教材\6 KINDLE书)", G_mapfiles);

		cout << "S_sameFilePaths cout = " << G_sameFilePaths.size() <<  endl;

		for (auto& name : G_sameFilePaths)
		{
			cout << name << endl;

			// 直接删除 无提示 不可恢复！
			remove(name.c_str());
		}
	}
	
}
