                   
--tab�������for in 
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

--�ַ�����
function strfind()
	s,e = string.find("hello Lua users", "Lua")
	print(s, e)
end

--����Ĭ��TAB����
function rename (arg)
    print(arg.old..arg.new)
    --rename({old="old", new="new"})
end

--�հ�����
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

--�ݹ麯�� ǰ������
local fact
fact = function (n)

    if n == 0 then
       return 1
    else
       return n*fact(n-1)
    end
	--print(fact(5))
end

--��������
function list_iter (t)

	--����ֻ����һ�� ����ʱ��
    local i = 0
    local n = table.getn(t)

    return function ()
       i = i + 1 --i�ᱻ���ؼ�ס
       --ÿ����һ�� ������һ��
       if i <= n then return t[i] end
    end
    
    --t = {10, 20, 30}
	--iter = list_iter(t)      -- creates the iterator
--
--
	--print(iter())
--
	----for in��ʹ��
	--for i in iter do
		--print(i)
	--end
end

--���������� 
--require "TestDefine.lua"
--���ÿ��ں��� 
--print(addnum(2,5))

--���� 
function ass()
	assert(11>221, "���ԣ�")
	error(121)
end

--�������е��쳣�ʹ���
--��һ��������pcall����true�Լ�����ִ�к������ķ���ֵ��
--���򷵻�nil�ʹ�����Ϣ��
--local status, err = pcall(ass)
--print(err)

--���ٺϲ��ַ���
--local t = {"asa","12312","swsw","sds","123123","111","222","333","444"}
--s = table.concat(t, ",") .. "  there is all"
--print(s)

--��������
--function serialize (o)
--	print(io.write(o))
--end
--serialize(121)

--�������ȫ�ֶ���
--for n in pairs(_G) do
--	print(n)
--end

--�漴��
math.randomseed(os.time())
--n 0~n a b a<=x<=b
local ran = math.random(1,1.5)
--print(os.time().."  ran : "..ran)
 
 
--���ô�С nΪ��Сsize 
--��һֱʹ��getn��ȡ�����С��ʹ��setn���������С��
if false then 
	 a = {	n=30000  }
	print(table.getn(a))               --> n=?
	--���ñ���С 
	table.setn(a, 10000)
	print(table.getn(a))               --> 10000
end

--β������
if false then
    a = {}
  	for line,value in pairs{n = 10000} do
		table.insert(a, line)
		table.insert(a, value)
	end
	--β��ɾ�� Ҳ��ָ������ 
	table.remove(a)    	
	print(table.getn(a)) 
end 

--���� 
if false then
	a = {}
	--����������a�� 
	for n in pairs{z=1,v=2,f=3,s=9} do 
		table.insert(a, n) 
	end
	
	--Ĭ��С������ �ɴ��������� 
	table.sort(a)
	
	--�������� 
	for i,n in ipairs(a) do 
		print(n) 
	end
end 


--�ַ���
if false then
	--�����ʽ
	print(string.format("pi = %.4f", 3.1415926))
	d = 5; m = 11; y = 1990
	print(string.format("%02d/%02d/%04d", d, m, y))
	tag, title = "h1", "a title"
	print(string.format("<%s>%s</%s>", tag, title, tag))


	--����
	s = "hello world"
	i, j = string.find(s, "hello")
	print(i,j)                        --> 1    5
	print(string.sub(s, i, j))         --> hello

	--�滻
	s = string.gsub("Lua is cute", "cute", "great")
	print(s)      --> Lua is great
end


--IO�ļ�
if false then
	--��ģʽ
    io.write("lua eidt")
	--�� ��ȡ
 local filename = "c:\\lua text complite.txt"
    local f = assert(io.open(filename, "wb"))
    --f:write("123")
    local data = f:read("*all")
	print(data)
end


--����ϵͳ֧��
if false then
	-- tiem to now
	print(os.time{year=2010, month=12, day=14, hour=20, min = 0, sec = 0})

	print(os.date("today is %A, in %B"))

    --> today is Tuesday, in May

	print(os.date("%x", 906000490))

    --> 09/16/1998

	--��ȡ��ǰ����
    --print(os.getenv())

	--�����ļ�
	function createDir (dirname)
    	os.execute("mkdir " .. dirname)
	end
end


--DEBUG��
if false then
	--׷�ٺ�������
	debug.sethook(print, "l")
	
	print(table.getn(debug))
	print(table.getn(debug))
end


