//--------------------------------------------------------------------
// �ļ���:		Testjson
// ��  ��:		ʹ��ͨ�õ�PTHREAD��д���԰���
// ˵  ��:		�Ա� C++thread����ѧϰ
// ��������:	2017��5��8��
// ��������:	2017��5��8��
// ������:		Maple(������)
// ��Ȩ����:	������ţ���ֿƼ��ɷ����޹�˾
//--------------------------------------------------------------------
#include "TestHeader.h"

#include <stdio.h>  
#include <iostream>
#include <fstream>
#include <iosfwd>
#include "json/json.h"
#include <string>
using namespace std;

// ����ӿ�
void Testjson::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// �ļ�����JSON
	if (0)
	{
		// �ļ�����λ�� ����ʱ����exe ����ʱ���� ����Ŀ¼ͬ����Ŀ¼��TargetDir��
		ifstream ifs("package.json");
		if (!ifs)
		{
			std::cout << "open file failed!" << std::endl;
		}

		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(ifs, root, false))
		{
			return;
		}
			
		if (root["name"].isString())
		{
			string name = root["name"].asString();
			cout << name.c_str() << endl;
		}

		if (root["age"].asInt())
		{
			int age = root["age"].asInt();
			cout << age << endl;
		}

		// ���� �����ڷ���Ĭ��ֵ
		string code = root.get("code", "no have").asString();

		// ����������ʹ���תֵ������
		string age = root.get("age", "error type").asString();

		// ���ʹ�����޴���
		if (root["age"].isString() || root["age1"].isString())
		{
			cout << "can't get inside!" << endl;
		}
		else
		{
			cout << "no find or error match type !" << endl;
		}
	}

	// �ַ�������
	if (0)
	{
		// ���ַ��������ʧ��
		string str = "{\"name\": \"JSON NAME\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(str, root, false))
		{
			return;
		}

		// ��ά����ֵ  ��Ҫ�ж�isArray ����������
		if (root["name"].isArray() && !root["name"]["ABC"].isNull())
		{
			cout << root["name"]["ABC"].asString() << endl;
		}

		if (root["name"].isString())
		{
			string name = root["name"].asString();
			cout << name.c_str() << endl;
		}

		// ���� �����ڷ���Ĭ��ֵ
		string name = root.get("name", "no have").asString();
		int code = root.get("code", 0).asInt();
	}

	// д��json
	if (0)
	{
		Json::Value root;

		// ��װjson����
		root["occupation"] = "paladin";
		root["camp"] = "alliance";
		root["role_id"] = 1;

		cout << root.toStyledString() << " size:" << root.size() << endl; // 3

		Json::Value newNode;
		newNode["newNode"] = 1;

		root["array"].append(newNode);
		root["array"].append("123");

		// ��json���ݣ�������ʽ��������ļ�
		Json::StyledWriter writer;
		ofstream os;
		os.open("test_write.json");
		os << writer.write(root);
		os.close();

		cout << root.toStyledString();
	}
	
}
