-- ����һָ��ʱ��ֻ��һ��Эͬ���������У���������������е�Эͬ����ֻ������ȷ�ı�Ҫ������ʱ��Żᱻ����
-- Эͬ�����е�����ͬ���Ķ��̣߳��ڵȴ�ͬһ���߳����ļ����߳��е�����Эͬ��

-- ���� Lua �����ֻ�ܹ�����һ���߳��£��������Ҫ��ͬһ���������� Lua ���д���һЩ���񣬱���Ϊÿ���̲߳�������� Lua ������� -�Ʒ�

-- ����Э��(���� coroutine�� ������һ������������ resume ���ʹ�õ�ʱ��ͻ��Ѻ�������)

co = coroutine.create(

    -- ����
    function(i)
        print("create print ", i);
    end

)

-- ���� coroutine���� create ���ʹ��
coroutine.resume(co, 1) 
coroutine.resume(co, 2) -- �����ˣ����˳�
print("coroutine.status =", coroutine.status(co))  -- dead
 
print("----------")
-- ���� coroutine������һ��������һ�����������������ͽ��� coroutine���� create �����ظ�
wrapCo = coroutine.wrap(

    function(i)
        print("wrap print ", i)
    end

)
wrapCo(1)
-- wrapCo(2) -- ���ָܻ�������Э��
print("----------")
 

co2 = coroutine.create(

    function()

        for i = 1, 4 do
            print("co2", i)
            print(coroutine.status(co2))  -- �鿴 coroutine ��״̬
            print(coroutine.running())    -- ����һ�� coroutine ���̺߳�

            -- ���� coroutine���� coroutine ����Ϊ����״̬���ȴ�resume����
            coroutine.yield()
        end

    end

)
 
coroutine.resume(co2) --1
coroutine.resume(co2) --2
coroutine.resume(co2) --3
 
print("coroutine.status(co2)", coroutine.status(co2))   -- suspended 
print(coroutine.running())
 
print("----------")

coroutine.resume(co2) --4
coroutine.resume(co2) --��Э����Ĵ���ִ�����
print("coroutine.status(co2)", coroutine.status(co2))   -- dead 