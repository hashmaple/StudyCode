//--------------------------------------------------------------------
// 文件名:		TestLua
// 内  容:		
// 说  明:		
// 创建日期:	2020年9月14日
// 整理日期:	2020年9月14日
// 创建人:		Maple(周树青)
//--------------------------------------------------------------------
#include "TestLua.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>

#include "lua.hpp"

#include "MD5/md5.h"

#include <string>
using namespace std;

// 提供给LUA访问的函数：获得版本
int se_get_version(lua_State* L)
{
	int version = 9527;
	lua_pushnumber(L, version);
	return 1;
}

int luaAdd(lua_State *lua_state, int x, int y)
{
	int sum;
	//获取lua里面的add函数并把它放到lua的栈顶
	lua_getglobal(lua_state, "LuaAdd");

	//往lua栈里面压入两个参数
	lua_pushnumber(lua_state, x);
	lua_pushnumber(lua_state, y);

	// 调用lua函数,2是参数的个数，1是返回值的个数
	lua_call(lua_state, 2, 1);

	// 从栈顶读取返回值,注意这里的参数是-1
	sum = lua_tointeger(lua_state, -1);

	// 返回值从栈顶拿掉
	lua_pop(lua_state, 1);

	return sum;
}

// 读取LUA数组 key为整数的table
void readLuaArray(lua_State *L)
{
	lua_getglobal(L, "LuaArray");

	int n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) 
	{
		lua_rawgeti(L, 1, i);
		cout << "read LuaArray: " << lua_tostring(L, -1) << endl;
		lua_pop(L, 1);
	}
}

// 写入LUA数组 key为整数的table
int writeLuaArray(lua_State *L)
{
	lua_settop(L, 0);
	lua_getglobal(L, "LuaArray");

	//确保table
	luaL_checktype(L, 1, LUA_TTABLE);

	int n = luaL_len(L, 1);
	for (int i = 1; i <= n; ++i) 
	{
		lua_pushnumber(L, i);

		char buf[256];
		sprintf_s(buf, "element_%d", i);
		lua_pushstring(L, buf);

		lua_rawset(L, -3);
	}

	return 0;
}

TestLua::TestLua()
{
}

TestLua::~TestLua()
{
}

// 对外接口
void TestLua::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 测试MD5
	if (0)
	{
		cout << "==TestLua::测试MD5===" << endl;

		// 使用字符串的内容做MD5值
		char buff[64] = { 0 };
		MD5String("mike is a boy!", buff, 64);
		cout << "mike is a boy! md5: " << buff << endl;

		// 使用文件的内容做MD5值  文件时间戳无用
		char buff_file1[64] = { 0 };
		MD5File("test.lua", buff_file1, 64);

		// 使用文件的内容做MD5值  文件时间戳无用
		char buff_file2[64] = { 0 };
		MD5File("test.lua", buff_file2, 64);

		// 文件名 时间催 不同，内容相同MD5相同。
		cout << buff_file1 << endl;
		cout << buff_file2 << endl;
	}

	// 测试
	if (0)
	{
		cout << "==TestLua::BeginTest===" << endl;

		// 初始化Lua虚拟机
		lua_State *lua_state;
		lua_state = luaL_newstate();

		// 设置待注册的Lua标准库，这个库是给你的Lua脚本用的
		// 因为接下来我们只想在Lua脚本里面输出hello world，
		// 所以只引入基本库就可以了
		static const luaL_Reg lualibs[] =
		{
			{ "base", luaopen_base },
			{ NULL, NULL }
		};

		// 注册Lua标准库并清空栈
		const luaL_Reg *lib = lualibs;
		for (; lib->func != NULL; lib++)
		{
			luaL_requiref(lua_state, lib->name, lib->func, 1);
			lua_pop(lua_state, 1);
		}

		// 向LUA声明C++函数
		lua_pushcfunction(lua_state, se_get_version);
		lua_setglobal(lua_state, "se_get_version");

		// 向LUA声明C++变量
		lua_pushstring(lua_state, "Mike");
		lua_setglobal(lua_state, "cppname");

		// 向LUA传递TABLE
		lua_createtable(lua_state, 2, 0);

		lua_pushnumber(lua_state, 1);
		lua_pushstring(lua_state, "Wife is Father Christmas");
		lua_rawset(lua_state, -3);

		lua_pushnumber(lua_state, 2);
		lua_pushstring(lua_state, "Life is gift");
		lua_rawset(lua_state, -3);

		lua_setglobal(lua_state, "arg");

		// 运行hello.lua脚本
		auto b = luaL_dofile(lua_state, "test.lua");
		if (b == false)
		{
			cout << "调用luaL_dofile函数: failed!"<< endl;
		}

		// 调用LUA的函数 (方法调用要在lua_pcall调用之后)
		cout << "调用LUA函数: LuaAdd() = " << luaAdd(lua_state, 1, 2) << endl;

		// 获取LUA的变量值
		lua_getglobal(lua_state, "myname");
		string myname = lua_tostring(lua_state, -1);
		lua_pop(lua_state, 1);
		cout << "LUA变量 myname: " << myname << endl;

		// 表格的读取和写入
		cout << "LUA表格的读取和写入" << endl;
		readLuaArray(lua_state);
		writeLuaArray(lua_state);
		cout << "LUA表格修改后" << endl;
		readLuaArray(lua_state);

		// 关闭Lua虚拟机
		lua_close(lua_state);
	}
}
