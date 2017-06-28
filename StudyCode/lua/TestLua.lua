                   
--tab函数输出for in 
function PrintTab(...)
    local myTab = 
	{
	   0,1,2,3,4,5
	}  
	print(table.getn(myTab)) 
	for i,v in ipairs(myTab) do 
		print(i..v)
    end  
  
end     

--字符查找
function strfind()
	s,e = string.find("hello Lua users", "Lua")
	print(s, e)
end

--参数默认TAB构造
function rename (arg)
    print(arg.old..arg.new)
    --rename({old="old", new="new"})
end

--闭包函数
function newCounter()
    local i = 0
    return function()     -- anonymous function
				i = i + 1
			return i
    end
    --c1 = newCounter()
	--print(c1())  --> 1
	--print(c1())  --> 2
end

--递归函数 前向声明
local fact
fact = function (n)

    if n == 0 then
       return 1
    else
       return n*fact(n-1)
    end
	--print(fact(5))
end

--迭代函数
function list_iter (t)

	--这里只会来一次 构造时候
    local i = 0
    local n = table.getn(t)

    return function ()
       i = i + 1 --i会被返回记住
       --每进来一次 返回下一个
       if i <= n then return t[i] end
    end
    
    --t = {10, 20, 30}
	--iter = list_iter(t)      -- creates the iterator
--
--
	--print(iter())
--
	----for in的使用
	--for i in iter do
		--print(i)
	--end
end

--包含其他库 
--require "TestDefine.lua"
--调用库内函数 
--print(addnum(2,5))

--断言 
function ass()
	assert(11>221, "断言！")
	error(121)
end

--捕获所有的异常和错误。
--若一切正常，pcall返回true以及“被执行函数”的返回值；
--否则返回nil和错误信息。
--local status, err = pcall(ass)
--print(err)

--快速合并字符串
--local t = {"asa","12312","swsw","sds","123123","111","222","333","444"}
--s = table.concat(t, ",") .. "  there is all"
--print(s)

--保存数据
--function serialize (o)
--	print(io.write(o))
--end
--serialize(121)

--输出所有全局对象
--for n in pairs(_G) do
--	print(n)
--end

--随即数
math.randomseed(os.time())
--n 0~n a b a<=x<=b
local ran = math.random(1,1.5)
--print(os.time().."  ran : "..ran)
 
 
--设置大小 n为大小size 
--请一直使用getn获取数组大小，使用setn设置数组大小。
if false then 
	 a = {	n=30000  }
	print(table.getn(a))               --> n=?
	--设置表格大小 
	table.setn(a, 10000)
	print(table.getn(a))               --> 10000
end

--尾部插入
if false then
    a = {}
  	for line,value in pairs{n = 10000} do
		table.insert(a, line)
		table.insert(a, value)
	end
	--尾部删除 也可指定索引 
	table.remove(a)    	
	print(table.getn(a)) 
end 

--排序 
if false then
	a = {}
	--把索引插入a中 
	for n in pairs{z=1,v=2,f=3,s=9} do 
		table.insert(a, n) 
	end
	
	--默认小于排序 可带函数参数 
	table.sort(a)
	
	--输出排序后 
	for i,n in ipairs(a) do 
		print(n) 
	end
end 


--字符串
if false then
	--输出格式
	print(string.format("pi = %.4f", 3.1415926))
	d = 5; m = 11; y = 1990
	print(string.format("%02d/%02d/%04d", d, m, y))
	tag, title = "h1", "a title"
	print(string.format("<%s>%s</%s>", tag, title, tag))


	--查找
	s = "hello world"
	i, j = string.find(s, "hello")
	print(i,j)                        --> 1    5
	print(string.sub(s, i, j))         --> hello

	--替换
	s = string.gsub("Lua is cute", "cute", "great")
	print(s)      --> Lua is great
end


--IO文件
if false then
	--简单模式
    io.write("lua eidt")
	--打开 读取
 local filename = "c:\\lua text complite.txt"
    local f = assert(io.open(filename, "wb"))
    --f:write("123")
    local data = f:read("*all")
	print(data)
end


--操作系统支持
if false then
	-- tiem to now
	print(os.time{year=2010, month=12, day=14, hour=20, min = 0, sec = 0})

	print(os.date("today is %A, in %B"))

    --> today is Tuesday, in May

	print(os.date("%x", 906000490))

    --> 09/16/1998

	--获取当前环境
    --print(os.getenv())

	--建立文件
	function createDir (dirname)
    	os.execute("mkdir " .. dirname)
	end
end


--DEBUG库
if false then
	--追踪函数行数
	debug.sethook(print, "l")
	
	print(table.getn(debug))
	print(table.getn(debug))
end


