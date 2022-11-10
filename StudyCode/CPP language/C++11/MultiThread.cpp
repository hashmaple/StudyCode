/*!
 * \file MultiThread.cpp
 * \date 2019/03/12 10:43
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief 多线程和并发,锁等
 *
 * TODO: long description
 *
 * \note
*/
#include "C++11.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <thread>
#include <future>
#include <mutex>
#include <queue>

using namespace std;

// 便于跨平台开发，可利用宏定义支持代码跨平台
#ifndef __linux__
#include "windows.h"
#else
#include "unistd.h"
#endif

// windows
// printf("now pid is %d \n", GetCurrentProcessId());
// printf("now tid is %d \n", GetCurrentThreadId());

// linux
// printf("now pid is %d \n", getpid());
// printf("now tid is %d \n", gettid());

// myallocate
template<typename T>
class MyAlloc
{
public:
	typedef T value_type;
	MyAlloc() noexcept{}

	template<typename U>
	MyAlloc(const MyAlloc<U>&) noexcept{}

	T* allocate(size_t num)
	{
		cout << "allocate num = " << num << "size = " << num * sizeof(T) << endl;
		return static_cast<T*>(::operator new(num * sizeof(T)));
	}

	void deallocate(T* p, size_t num)
	{
		cout << "delete p num = " << num << endl;
		::operator delete(p);
	}

	//template<typename T1, typename T2>
	//bool operator== (const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept
	//{
	//	return true;
	//}

	//template<typename T1, typename T2>
	//bool operator!= (const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept
	//{
	//	return false;
	//}
};


// 输入数值并返回
int queryNumber()
{
	cout << "input number: ";
	int num;
	cin >> num;
	if (!cin)
	{
		throw runtime_error("no number read!");
	}

	return num;
}

// 按随机间隔休眠和打印3个输入的字符 然后返回
int dosomething(char c)
{
	// 随机数 使用c作为种子
	default_random_engine dre(c);
	uniform_int_distribution<int> id(10, 1000);

	// 随机休息后 打印字符
	for (int i = 0; i< 3; i++)
	{
		int t = id(dre); 
		this_thread::sleep_for(chrono::milliseconds(t));
		//cout << t << "/" << c << " ";
		cout.put(c).flush();
	}

	return 1;
}

// 同上,不过f为在函数内获取. 多个线程都可获取f.get()
int dosomething2(char c, shared_future<int> f)
{
	try
	{
		int num = f.get();

		// 随机休息后 打印num个字符
		for (int i = 0; i < num; i++)
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			cout.put(c).flush();
		}
	}
	catch (const exception& e)
	{
		cerr << "exception in thread: " << this_thread::get_id() << " : "
			<< e.what() << endl;
	}

	return c;
}

// 修改传入的字符
void ModificationString(promise<string>& p)
{
	try
	{
		cout << "read x set exception!" << endl;
		char c = cin.get();
		if (c == 'x')
		{
			throw runtime_error("input char is c, throw a exception!");
		}
		else
		{
			cout << "==p.set_value==" << endl;

			//p.set_value(string("input char is ") + c);
			// 确保线程执行结束后设置值,确保别处调用get()后,本线程执行完毕.
			p.set_value_at_thread_exit(string("input char is ") + c);
		}
	}
	catch (...)
	{
		// 把异常设置到p
		cout << "把异常设置给p! " << endl;
		p.set_exception(current_exception());
		//p.set_exception_at_thread_exit(current_exception());
	}
}

int func1()
{
	return dosomething('1');
}

int func2()
{
	return dosomething('2');
}

// 定义互斥体
mutex PrintMutex;
mutex PrintMutex1;
timed_mutex TimedMutex;

// 循环打印字符
void printString(const string& str)
{
	// 锁定 在析构时释放 RAII-Resource Acquisition Is Initialization
	// RAII，也称为“资源获取就是初始化”，是c++等编程语言常用的管理资源、避免内存泄露的方法。
	// 它保证在任何情况下，使用对象时先构造对象，最后析构对象。
	lock_guard<mutex> lockprint(PrintMutex);

	// 单个打印字符
	cout << GetCurrentThreadId();
	for (auto& it : str)
	{
		cout.put(it);
	}
	cout << endl;


	// 判断能否LOCK 失败就返回FLASE 最好少用,用lock_guard
	if (PrintMutex1.try_lock())
	{
		cout << GetCurrentThreadId()  << " PrintMutex1.try_lock() == T" << endl;
		
		// 成功后需要释放 下面2选1
		PrintMutex1.unlock();
		//lock_guard<mutex> lock2(PrintMutex1, adopt_lock);
	}
}

int v = 1;
void critical_section(int change_v) 
{
	static std::mutex mtx;

	// 锁定 在析构时释放 RAII-Resource Acquisition Is Initialization
	std::unique_lock<std::mutex> lock(mtx);
	
	v = change_v;
	cout << GetCurrentThreadId() << " unique_lock v= " << v << std::endl;

	// 解开锁 还可再锁.可在函数内分段LOCK
	lock.unlock();

	// 又可以再加锁,结束会自动析构解锁
	//lock.lock();
	v += 1;
	cout << GetCurrentThreadId() << " lock.lock v= " << v << std::endl;
	cout << GetCurrentThreadId() << " lock.lock v= " << v << std::endl;
}

// 用于once调用 只调用一次
void OnceCallFunc(vector<int>& vct)
{
	// 只会执行一次 用于多线程中的初始化数据
	vct.resize(10, 2);
	cout << "OnceCallFunc only once come!" << endl;
}

vector<int> OnceVector;

// 只调用一次的函数
void OnlyOnceCall()
{
	cout << "call OnlyOnceCall" << endl;
	static once_flag oc;
	call_once(oc, [] {
		OnceCallFunc(OnceVector);
	});

	cout << "OnceVector.size() = " <<  OnceVector.size() << endl;
}

bool readyFlag;
mutex readyMutex;
condition_variable readyCondVar;

// 条件变量线程1
void Thread1()
{
	cout << "Thread1 : " << endl;
	cin.get();

	{
		// 这里锁定 对readyFlag设置为T
		lock_guard<mutex> lg(readyMutex);
		readyFlag = true;
		cout << "set readyFlag true!" << endl;
	}
	// 通知 readyCondVar.wait
	readyCondVar.notify_one();
}

// 条件变量线程2
void Thread2()
{
	{
		unique_lock<mutex> ul(readyMutex);

		// 这里等于循环判断和等待[]{}返回值为T. 为T后再执行下去.
		readyCondVar.wait(ul, [] {
			cout << "wait readyFlag = " << readyFlag << endl; 
			return readyFlag; 
		});

		cout << "readyCondVar.waited" << endl;
	}

	cout << "done" << endl;
}

// Queue 生产者消费者
queue<int> myQueue;
mutex queueMutex;
condition_variable queueCondVar;


// 信号数据 生产者
void provider(int val)
{
	for (int i = 0; i < 6; i++)
	{
		lock_guard<mutex> lg(queueMutex);
		myQueue.push(val + i);
		cout << "provide id = " << val + i << endl;
	}
	queueCondVar.notify_one();

	this_thread::sleep_for(chrono::milliseconds(val));
}

// 信号数据 消费者
void consumer(int num)
{
	std::cout << "call consumer  num = " << num << endl;

	// 死循环等待信号,queue不空就会打印和pop
	int i = 0;
	while (true)
	{
		int val = 0;
		{
			unique_lock<mutex> ul(queueMutex);
			queueCondVar.wait(ul, [] { return !myQueue.empty(); });

			if (!myQueue.empty())
			{
				val = myQueue.front();
				myQueue.pop();
			}
		}

		std::cout << "consumer-" << num << " id = " << val << endl;
		this_thread::sleep_for(chrono::milliseconds(val*2));
	}
}

// 原子的标志,确保原子操作设置.
atomic<bool> atomicFlag(false);

// 信号数据 生产者
void AtomicProvider(int val)
{
	cout << "AtomicProvider input: " << endl;
	int i;
	cin >> i;
	myQueue.push(i);

	atomicFlag.store(true);
}

// 信号数据 消费者
void AtomicConsumer()
{
	cout <<  "\n===AtomicConsumer wait===\n";
	while (!atomicFlag.load())
	{
		cout.put('.').flush();
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	cout << "myQueue.front: " << myQueue.front() << endl;
	myQueue.pop();

}

// thread_local
void tl_func(string name)
{
	thread_local int count = 1;
	for (auto i = 0; i < 5; i++)
	{
		cout << name << " count = " << count << endl;
		count++;
	}

	return;
}

/////////////////////////////对外接口/////////////////////////////////////////////
// MultiThread
void MultiThread::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// 最短的线程
	if (0)
	{
		thread t( [](){cout << "thread short" << endl;} );

		// 	1 waits for the thread to finish its execution
		t.join();

		// 2 将执行线程与线程对象分开，允许独立执行。线程退出后，将释放任何分配的资源
		//t.detach();
	}

	// C++11 THREAD_LOCAL 和 join
	if (0)
	{
		// thread_local int count = 1; 线程安全
		std::thread t1(tl_func, "t1"); // 12345
		std::thread t2(tl_func, "t2"); // 12345
		t1.join();
		t2.join();
	}

	// async and future 方便的使用异步方法
	if (0)
	{
		cout << "func1 in background func2 in foreground : " << endl;

		// 异步启动一个分离线程在后台,不明确调用时间
		future<int> result1 = async(func1);

		// 明确以异步方式启动目标函数,如果无法启动.抛出异常.
		future<int> result2 = async(launch::async, func1);

		// 强制延缓调用,必须等到get启动
		future<int> result3 = async(launch::deferred, func2);

		// wait会强制执行后台异步线程.get也会强制并且拿到返回值
		result1.wait();	// 要求result1执行完毕
		result3.get();

		// 调用get会让func1保证执行完毕.在单线程上也可以保证. get只能调用一次.
		int result = result1.get() + func2(); // 1+1 只可获取一次get
		cout << endl << "result1.get() + func2() = " << result << endl;
		// 检查有效性  get之后就无效了
		cout << "result1.valid() = " << result1.valid() << endl;
	}

	// 2个异步任务测试案例
	if (0)
	{
		char c = '*';
		char d = '#';
		auto f1 = async([=] {dosomething(c); });
		auto f2 = async(dosomething, d);

		// 如果2个异步至少有一个启动
		if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
			f2.wait_for(chrono::seconds(0)) != future_status::deferred)
		{
			// 至少等待一个异步执行结束就跳出
			while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
					f2.wait_for(chrono::seconds(0)) != future_status::ready)
			{
				//cout << "this_thread::yield()" << endl;
				this_thread::yield();
			}
		}

		cout.put('\n').flush();

		cout << "go try: " << endl;

		// 这个时候让2个都强制运行和返回结果,大概率有一个还没有执行完毕
		try
		{
			f1.get();
			f2.get();
		}
		catch (const exception& e)
		{
			cout << "exception: " << e.what() << endl;
		}

		cout << "\ndone"<< endl;
	}

	// 共享shared_future
	if (0)
	{
		// f为共享的异步执行,结果一份给f1 f2 f3使用
		//shared_future<int> f = async(queryNumber);
		auto f = async(queryNumber).share();

		// dosomething2 有f.get(),不过都是一份数据.
		auto f1 = async(launch::async, dosomething2, '.', f);
		auto f2 = async(launch::async, dosomething2, '+', f);
		auto f3 = async(launch::async, dosomething2, '-', f);

		f1.get();
		f2.get();
		f3.get();

		cout << "\ndone" << endl;
	}

	// 底层接口thread
	if (0)
	{
		// 返回可能的线程数量,I7本机器返回8. 在异步线程函数里也是8.
		cout << "hardware_concurrency " << thread::hardware_concurrency() << endl;

		cout << "判断无效请使用id(),不要假设0. = " << thread::id() << endl;

		thread t1(dosomething, '*');
		cout << "start t1-1 :" << t1.get_id() << endl;

		// 循环开的线程在后台执行.不受主线程退出与否影响
		for (auto i = 0; i < 5; i++)
		{
			thread t(dosomething, 'a'+i);
			cout << "detach started background thread: " << t.get_id() << " c = " << 'a' + i << endl;
			t.detach();
		}

		cin.get();

		// 强制等待结束   或者 使用detach分离. 否则会报错
		cout << "强制等待t1结束.  join :" << t1.get_id() << endl;

		// 执行完t1.join 就会退出主线程. 而循环中开启的线程继续在后台执行.
		t1.join();

		cout << "\nt1.join() 执行完毕" << endl;

	}

	// 底层promise 传递引用,设置数值
	if (0)
	{
		try
		{
			// 启动一个线程,传入引用promise变量
			promise<string> p;
			thread t(ModificationString, ref(p));
			t.detach();

			// 只可以调用一次get_future
			future<string> f(p.get_future());

			// get()调用会保证promise被设置值或异常,不保证线程执行完毕!
			cout << "result : " << f.get() << endl;
		}
		catch (exception& e)
		{
			cerr << "===EXCEPTION===\n" << e.what() << endl;
		}
		catch (...)
		{
			cerr << "EXCEPTION" << endl;
		}
	}

	// packaged_task
	if (0)
	{
		// packaged_task同时持有目标函数和结果
		packaged_task<int(char)> task(dosomething);

		cout << "task(dosomething)" << endl;

		// 获取结果
		future<int> f = task.get_future();
		cout << "task get_future" << endl;

		// 执行task内的函数,使其变为ready
		cout << "call task(&)" << endl;
		task('&');

		// 提取结果
		int result = f.get();
		cout << "\nf.get() " << result << endl;
	}

	// MUTEX  lock_guard unique_lock
	if (0)
	{
		// 3个线程,同时循环打印会导致乱! 加上lock_guard<mutex>
		auto f1 = async(launch::deferred, printString, "f1, My name is Mike!");
		auto f2 = async(launch::async, printString, "f2, This is my book!");
		auto f3 = async(launch::deferred, printString, "f3 lock_guard!");

		// 不加锁情况下顺序无法保证,会相互穿插!
		f1.get();
		f2.get();
		f3.get();

		printString("Here is the main thread!");

		// 测试unique_lock 加锁和解锁更灵活 可按需分段加锁
		thread t1(critical_section, 1), t2(critical_section, 2), t3(critical_section, 3);
		t1.detach();
		t2.detach();
		t3.detach();
	}

	// 只调用一次 初始化数据用途
	if (0)
	{
		// 多次调用 只会执行一次.
		//OnlyOnceCall();
		//OnlyOnceCall();
		//OnlyOnceCall();

		// 多线程调用也能保证安全
		auto f1 = async(OnlyOnceCall);
		auto f2 = async(OnlyOnceCall);
		auto f3 = async(OnlyOnceCall);
	}

	// 多线程唤醒
	if (0)
	{
		auto f1 = async(launch::async, Thread1);
		auto f2 = async(launch::async, Thread2);
	}

	// 多线程读取Queue读写. 生产者消费者
	if (0)
	{
		// 三个生产者
		auto p1 = async(provider, 100);
		auto p2 = async(provider, 200);
		auto p3 = async(provider, 300);

		p1.get();

		// 两个消费者 线程安全操作同一个queue
		auto c1 = async(launch::async, consumer, 1);
		auto c2 = async(launch::async, consumer, 2);
	}

	// 使用atomic来读写
	if (0)
	{
		// 两个消费者 线程安全操作同一个queue
		auto f1 = async(launch::async, AtomicProvider,100);
		auto c1 = async(launch::async, AtomicConsumer);
	}

	// 使用自定义的allocate
	if (0)
	{
		vector<int, MyAlloc<int>> myVct(1,1);
		myVct.push_back(1);
		myVct.pop_back();
		myVct.clear();
	}
}
