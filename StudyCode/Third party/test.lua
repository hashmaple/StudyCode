
print("=This is test.lua（Encode CODEGB2312）=")
print("print Hello World!")


print("print C++ var cppname = "..cppname)


print("Call C++ function&result is:"..se_get_version())

--print table from c++
for i=1, #arg do
    print("arg ", i, arg[i])
end

for k,v in pairs(arg) do
       print(k,v)
end

-- 全局变量
--本lUA文件采用GB2312 兼容ASCII码
myname = "赵云"

--table的读取
LuaArray={"mike", "zsqkyo"}

-- add two numbers
function LuaAdd ( x, y )
    return x + y
end




