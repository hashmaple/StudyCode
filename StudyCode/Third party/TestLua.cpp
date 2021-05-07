//--------------------------------------------------------------------
// �ļ���:		TestLua
// ��  ��:		
// ˵  ��:		
// ��������:	2020��9��14��
// ��������:	2020��9��14��
// ������:		Maple(������)
//--------------------------------------------------------------------
#include "TestLua.h"

#include <stdio.h>  
#include <iostream>
#include <windows.h>

#include "lua.hpp"

#include "MD5/md5.h"

#include <string>
using namespace std;

// �ṩ��LUA���ʵĺ�������ð汾
int se_get_version(lua_State* L)
{
	int version = 9527;
	lua_pushnumber(L, version);
	return 1;
}

int luaAdd(lua_State *lua_state, int x, int y)
{
	int sum;
	//��ȡlua�����add�����������ŵ�lua��ջ��
	lua_getglobal(lua_state, "LuaAdd");

	//��luaջ����ѹ����������
	lua_pushnumber(lua_state, x);
	lua_pushnumber(lua_state, y);

	// ����lua����,2�ǲ����ĸ�����1�Ƿ���ֵ�ĸ���
	lua_call(lua_state, 2, 1);

	// ��ջ����ȡ����ֵ,ע������Ĳ�����-1
	sum = lua_tointeger(lua_state, -1);

	// ����ֵ��ջ���õ�
	lua_pop(lua_state, 1);

	return sum;
}

// ��ȡLUA���� keyΪ������table
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

// д��LUA���� keyΪ������table
int writeLuaArray(lua_State *L)
{
	lua_settop(L, 0);
	lua_getglobal(L, "LuaArray");

	//ȷ��table
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

// ����ӿ�
void TestLua::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// ����MD5
	if (0)
	{
		cout << "==TestLua::����MD5===" << endl;

		// ʹ���ַ�����������MD5ֵ
		char buff[64] = { 0 };
		MD5String("mike is a boy!", buff, 64);
		cout << "mike is a boy! md5: " << buff << endl;

		// ʹ���ļ���������MD5ֵ  �ļ�ʱ�������
		char buff_file1[64] = { 0 };
		MD5File("test.lua", buff_file1, 64);

		// ʹ���ļ���������MD5ֵ  �ļ�ʱ�������
		char buff_file2[64] = { 0 };
		MD5File("test.lua", buff_file2, 64);

		// �ļ��� ʱ��� ��ͬ��������ͬMD5��ͬ��
		cout << buff_file1 << endl;
		cout << buff_file2 << endl;
	}

	// ����
	if (0)
	{
		cout << "==TestLua::BeginTest===" << endl;

		// ��ʼ��Lua�����
		lua_State *lua_state;
		lua_state = luaL_newstate();

		// ���ô�ע���Lua��׼�⣬������Ǹ����Lua�ű��õ�
		// ��Ϊ����������ֻ����Lua�ű��������hello world��
		// ����ֻ���������Ϳ�����
		static const luaL_Reg lualibs[] =
		{
			{ "base", luaopen_base },
			{ NULL, NULL }
		};

		// ע��Lua��׼�Ⲣ���ջ
		const luaL_Reg *lib = lualibs;
		for (; lib->func != NULL; lib++)
		{
			luaL_requiref(lua_state, lib->name, lib->func, 1);
			lua_pop(lua_state, 1);
		}

		// ��LUA����C++����
		lua_pushcfunction(lua_state, se_get_version);
		lua_setglobal(lua_state, "se_get_version");

		// ��LUA����C++����
		lua_pushstring(lua_state, "Mike");
		lua_setglobal(lua_state, "cppname");

		// ��LUA����TABLE
		lua_createtable(lua_state, 2, 0);

		lua_pushnumber(lua_state, 1);
		lua_pushstring(lua_state, "Wife is Father Christmas");
		lua_rawset(lua_state, -3);

		lua_pushnumber(lua_state, 2);
		lua_pushstring(lua_state, "Life is gift");
		lua_rawset(lua_state, -3);

		lua_setglobal(lua_state, "arg");

		// ����hello.lua�ű�
		auto b = luaL_dofile(lua_state, "test.lua");
		if (b == false)
		{
			cout << "����luaL_dofile����: failed!"<< endl;
		}

		// ����LUA�ĺ��� (��������Ҫ��lua_pcall����֮��)
		cout << "����LUA����: LuaAdd() = " << luaAdd(lua_state, 1, 2) << endl;

		// ��ȡLUA�ı���ֵ
		lua_getglobal(lua_state, "myname");
		string myname = lua_tostring(lua_state, -1);
		lua_pop(lua_state, 1);
		cout << "LUA���� myname: " << myname << endl;

		// ���Ķ�ȡ��д��
		cout << "LUA���Ķ�ȡ��д��" << endl;
		readLuaArray(lua_state);
		writeLuaArray(lua_state);
		cout << "LUA����޸ĺ�" << endl;
		readLuaArray(lua_state);

		// �ر�Lua�����
		lua_close(lua_state);
	}
}
