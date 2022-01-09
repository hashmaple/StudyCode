#include "TestHeader.h"

#include <io.h>  
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

std::map<size_t, _finddata_t> G_mapfiles;

std::vector<string> G_sameFilePaths;

// �ļ�Ѱ�Һ���
void getFiles(string path, std::map<size_t, _finddata_t>& mapfiles)
{
	_finddata_t fileinfo;
	string p;

	intptr_t hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo);

	if (hFile != -1)
	{
		do 
		{
			// Ŀ¼�͵���
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					getFiles(p.assign(path).append("\\").append(fileinfo.name), mapfiles);
				}
			}
			else // �ļ������
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
		// _findnext �ļ���̫����Ŀ¼һ�𳬹�260 �ͻ����
		// �ж��ļ������ȴ�Լ����100 ��ͨ��Python����
	}
}

// ����ӿ�
void FileCleanUp::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// Ŀ¼+���ֳ��ȳ���260 ͨ��pyhton���� 
	if (0)
	{
#		/* 
		-*- coding:utf-8 -*-
		import os
		from shutil import copyfile

		for root, dirs, files in os.walk(r"F:\05 ѧϰ�̲�\6 KINDLE��") :
			for file in files :
				if len(file) > 100:
					print(file)
					print(os.path.join(root, file))
					# ���Ƶ� copyfile(os.path.join(root, file), os.path.join(r"F:\123", file))
					# ɾ�� os.remove(os.path.join(root, file))
		*/
	}

	// �ļ�����JSON
	if (0)
	{
		// �����ļ���
		getFiles(R"(F:\05 ѧϰ�̲�\6 KINDLE��)", G_mapfiles);

		cout << "S_sameFilePaths cout = " << G_sameFilePaths.size() <<  endl;

		for (auto& name : G_sameFilePaths)
		{
			cout << name << endl;

			// ֱ��ɾ�� ����ʾ ���ɻָ���
			remove(name.c_str());
		}
	}
	
}
