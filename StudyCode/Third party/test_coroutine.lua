-- 在任一指定时刻只有一个协同程序在运行，并且这个正在运行的协同程序只有在明确的被要求挂起的时候才会被挂起。
-- 协同程序有点类似同步的多线程，在等待同一个线程锁的几个线程有点类似协同。

-- 单个 Lua 虚拟机只能工作在一个线程下，如果你需要在同一个进程中让 Lua 并行处理一些事务，必须为每个线程部署独立的 Lua 虚拟机。 -云风

-- 创建协程(返回 coroutine， 参数是一个函数，当和 resume 配合使用的时候就唤醒函数调用)

co = coroutine.create(

    -- 函数
    function(i)
        print("create print ", i);
    end

)

-- 重启 coroutine，和 create 配合使用
coroutine.resume(co, 1) 
coroutine.resume(co, 2) -- 无用了，已退出
print("coroutine.status =", coroutine.status(co))  -- dead
 
print("----------")
-- 创建 coroutine，返回一个函数，一旦你调用这个函数，就进入 coroutine，和 create 功能重复
wrapCo = coroutine.wrap(

    function(i)
        print("wrap print ", i)
    end

)
wrapCo(1)
-- wrapCo(2) -- 不能恢复死亡的协程
print("----------")
 

co2 = coroutine.create(

    function()

        for i = 1, 4 do
            print("co2", i)
            print(coroutine.status(co2))  -- 查看 coroutine 的状态
            print(coroutine.running())    -- 返回一个 coroutine 的线程号

            -- 挂起 coroutine，将 coroutine 设置为挂起状态，等待resume唤醒
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
coroutine.resume(co2) --让协程里的代码执行完毕
print("coroutine.status(co2)", coroutine.status(co2))   -- dead 