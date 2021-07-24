//--------------------------------------------------------------------
// 文件名:		TestXML
// 内  容:		tinyXML rapidxml
// 说  明:		
// 创建日期:	2021年6月30日
// 整理日期:	2021年6月30日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "TestHeader.h"

#include <stdio.h>  
#include <iostream>

#include <string>
using namespace std;

#include "rapidxml-1.13.0\rapidxml.hpp"
#include "rapidxml-1.13.0\rapidxml_utils.hpp"
#include "rapidxml-1.13.0\rapidxml_print.hpp"
using namespace rapidxml;

#include "tinyxml2\tinyxml2.h"
using namespace tinyxml2;


// 对外接口
void TestXML::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// rapidxml写文件
	if (0)
	{
		xml_document<> doc;

		// 写入XML头
		xml_node<>* rot = doc.allocate_node(node_pi, "xml version='1.0' encoding='utf-8'");
		doc.append_node(rot);

		// 新节点1级  doc.append_node
		xml_node<>* config_node = doc.allocate_node(node_element, "config", "1");
		doc.append_node(config_node);

		// 新节点 子节点   config_node.append_node
		xml_node<>* color = doc.allocate_node(node_element, "color", NULL);
		config_node->append_node(color);

		// 直接加节点和值
		color->append_node(doc.allocate_node(node_element, "red", "0.1"));
		color->append_node(doc.allocate_node(node_element, "green", "0.1"));
		color->append_node(doc.allocate_node(node_element, "blue", "0.1"));
		color->append_node(doc.allocate_node(node_element, "alpha", "1.0"));

		// 新节点 子节点   config_node.append_node
		xml_node<>* size = doc.allocate_node(node_element, "size", NULL);
		size->append_node(doc.allocate_node(node_element, "x", "640"));
		size->append_node(doc.allocate_node(node_element, "y", "480"));
		config_node->append_node(size);

		// 新节点 子节点   config_node.append_node
		xml_node<>* mode = doc.allocate_node(node_element, "mode", "screen mode");
		mode->append_attribute(doc.allocate_attribute("fullscreen", "false"));
		config_node->append_node(mode);

		// 获取文本并输出
		string text;
		rapidxml::print(back_inserter(text), doc, 0);
		cout << "config.xml = " << endl << text << endl;

		// 写入文件
		std::ofstream out("config.xml");
		out << doc;
		out.close();
	}

	// rapidxml读文件
	if (0)
	{
		// 读取文件
		file<> fdoc("config.xml");
		
		// 解析文件XML内容
		std::cout << "config.xml = " << endl << fdoc.data() << endl;
		xml_document<>   doc;
		doc.parse<0>(fdoc.data());

		std::cout << doc.name() << std::endl;

		// 获取根节点
		xml_node<>* root = doc.first_node();
		if (root)
		{
			// 输出名称和值
			cout << "root node name = "<< root->name() << " value = " << root->value() << endl;

			// 输出子节点和属性
			std::cout << "root count_children: " << count_children(root) << std::endl;
			std::cout << "root count_attributes: " << count_attributes(root) << std::endl;

			// 获取根的第一个子节点
			auto node = root->first_node();
			while (node)
			{
				// 输出名称和值
				cout << "sub node name = " << node->name() << " value = " << node->value() << endl;
				cout << "count_children: " << count_children(node) << endl;
				cout << "count_attributes: " << count_attributes(node) << endl;

				// 获取下一个兄弟节点
				node = node->next_sibling();
			}

			// 获取根节点的"size"子节点
			xml_node<>* new_node = root->first_node("size");
			if (new_node)
			{
				// 添加新的子节点
				new_node->append_node(doc.allocate_node(node_element, "w", "0"));
				new_node->append_node(doc.allocate_node(node_element, "h", "0"));
			}
		}

		// 写入文件
		std::ofstream out("config.xml");
		out << doc;
		out.close();
	}

	// tinyxml2 写文件
	if (0)
	{
		const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

		XMLDocument doc;
		if (doc.Parse(declaration) != 0) 
		{
			return;
		}

		tinyxml2::XMLComment* comment = doc.NewComment("this is a xml test file");
		doc.InsertEndChild(comment);

		tinyxml2::XMLElement* root = doc.NewElement("Root");
		doc.InsertEndChild(root);

		tinyxml2::XMLElement* user = doc.NewElement("User");
		user->SetAttribute("Name", "fengbingchun");
		root->InsertEndChild(user);

		tinyxml2::XMLElement* blog = doc.NewElement("Blog");
		tinyxml2::XMLText* text1 = doc.NewText("CSDN");
		blog->InsertEndChild(text1);
		user->InsertEndChild(blog);

		tinyxml2::XMLElement* code = doc.NewElement("Code");
		tinyxml2::XMLText* text2 = doc.NewText("GitHub");
		code->InsertEndChild(text2);
		user->InsertEndChild(code);

		// Blog
		tinyxml2::XMLElement* blog2 = doc.NewElement("Blog");
		blog2->SetAttribute("Name", "CSDN");
		root->InsertEndChild(blog2);

		tinyxml2::XMLElement* addr = doc.NewElement("Address");
		tinyxml2::XMLText* text3 = doc.NewText("https://blog.csdn.net/fengbingchun");
		addr->InsertEndChild(text3);
		blog2->InsertEndChild(addr);

		tinyxml2::XMLElement* id = doc.NewElement("ID");
		tinyxml2::XMLText* text4 = doc.NewText("fengbingchun");
		id->InsertEndChild(text4);
		blog2->InsertEndChild(id);

		// Code
		tinyxml2::XMLElement* code2 = doc.NewElement("Code");
		code2->SetAttribute("Name", "GitHub");
		root->InsertEndChild(code2);

		tinyxml2::XMLElement* addr2 = doc.NewElement("Address");
		tinyxml2::XMLText* text5 = doc.NewText("https://github.com//fengbingchun");
		addr2->InsertEndChild(text5);
		code2->InsertEndChild(addr2);

		tinyxml2::XMLElement* repositories = doc.NewElement("Repositories");
		tinyxml2::XMLText* text6 = doc.NewText("27");
		repositories->InsertEndChild(text6);
		code2->InsertEndChild(repositories);

		// 保存文件
		doc.SaveFile("tinyTest.xml");
		doc.Clear();
	}

	// tinyxml2 读文件
	if (0)
	{
		XMLDocument doc;
		doc.LoadFile("config.xml");

		// 解析格式:
		// node:Value() mode
		// element-attr:Value() false
		// element-GetText() screen
		// <mode fullscreen = "false">screen< / mode>

		// 第一行注释
		auto root = doc.FirstChild();
		if (root)
		{
			cout << "FirstChild value = " << root->Value() << endl;

			// 此为根节点
			auto node = root->NextSibling();

			// 再换到根节点下第一个子节点
			node = node->FirstChild();

			// 遍历邻节点
			while (node)
			{
				cout << "node->Value() = " << node->Value() << endl;

				// 输出属性
				if (node->ToElement() && node->ToElement()->FirstAttribute())
				{
					cout << "node Attribute = " << node->ToElement()->FirstAttribute()->Value() << endl;
				}
				
				// 输出一层子节点
				auto child = node->FirstChild();
				while (child)
				{
					cout << "Child value = " << child->Value() << endl;

					// 输出内容
					auto element = child->ToElement();
					if (element)
					{
						cout << "Child ToElement text = " << element->GetText() << endl;
					}

					child = child->NextSibling();
				}

				cout << "============ " << endl;

				node = node->NextSibling();
			}
		}
	}
}
