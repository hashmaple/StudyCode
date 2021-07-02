//--------------------------------------------------------------------
// 文件名:		Testjson
// 内  容:		使用通用的PTHREAD来写测试案例
// 说  明:		对比 C++thread库来学习
// 创建日期:	2017年5月8日
// 整理日期:	2017年5月8日
// 创建人:		Maple(周树青)
// 版权所有:	苏州蜗牛数字科技股份有限公司
//--------------------------------------------------------------------
#include "TestHeader.h"

#include <stdio.h>  
#include <iostream>
#include <fstream>
#include <iosfwd>
#include "json/json.h"
#include <string>
using namespace std;

// 对外接口
void Testjson::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 文件解析JSON
	if (0)
	{
		// 文件所在位置 发布时跟随exe 调试时设置 工作目录同调试目录（TargetDir）
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

		// 访问 不存在返回默认值
		string code = root.get("code", "no have").asString();

		// 存在项，可类型错误，转值崩溃！
		string age = root.get("age", "error type").asString();

		// 类型错误或无此项
		if (root["age"].isString() || root["age1"].isString())
		{
			cout << "can't get inside!" << endl;
		}
		else
		{
			cout << "no find or error match type !" << endl;
		}
	}

	// 字符串解析
	if (0)
	{
		// 空字符串会解析失败
		string str = "{\"name\": \"JSON NAME\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(str, root, false))
		{
			return;
		}

		// 二维查找值  需要判断isArray 否则会崩溃。
		if (root["name"].isArray() && !root["name"]["ABC"].isNull())
		{
			cout << root["name"]["ABC"].asString() << endl;
		}

		if (root["name"].isString())
		{
			string name = root["name"].asString();
			cout << name.c_str() << endl;
		}

		// 访问 不存在返回默认值
		string name = root.get("name", "no have").asString();
		int code = root.get("code", 0).asInt();
	}

	// 写入json
	if (0)
	{
		Json::Value root;

		// 组装json内容
		root["occupation"] = "paladin";
		root["camp"] = "alliance";
		root["role_id"] = 1;

		cout << root.toStyledString() << " size:" << root.size() << endl; // 3

		Json::Value newNode;
		newNode["newNode"] = 1;

		root["array"].append(newNode);
		root["array"].append("123");

		// 将json内容（缩进格式）输出到文件
		Json::StyledWriter writer;
		ofstream os;
		os.open("test_write.json");
		os << writer.write(root);
		os.close();

		cout << root.toStyledString();
	}
	
}
