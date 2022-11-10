/*!
 * \file MultiThread.cpp
 * \date 2019/03/12 10:43
 *
 * \author zhousq
 * Contact: user@company.com
 *
 * \brief ���̺߳Ͳ���,����
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

// ���ڿ�ƽ̨�����������ú궨��֧�ִ����ƽ̨
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


// ������ֵ������
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

// �����������ߺʹ�ӡ3��������ַ� Ȼ�󷵻�
int dosomething(char c)
{
	// ����� ʹ��c��Ϊ����
	default_random_engine dre(c);
	uniform_int_distribution<int> id(10, 1000);

	// �����Ϣ�� ��ӡ�ַ�
	for (int i = 0; i< 3; i++)
	{
		int t = id(dre); 
		this_thread::sleep_for(chrono::milliseconds(t));
		//cout << t << "/" << c << " ";
		cout.put(c).flush();
	}

	return 1;
}

// ͬ��,����fΪ�ں����ڻ�ȡ. ����̶߳��ɻ�ȡf.get()
int dosomething2(char c, shared_future<int> f)
{
	try
	{
		int num = f.get();

		// �����Ϣ�� ��ӡnum���ַ�
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

// �޸Ĵ�����ַ�
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
			// ȷ���߳�ִ�н���������ֵ,ȷ���𴦵���get()��,���߳�ִ�����.
			p.set_value_at_thread_exit(string("input char is ") + c);
		}
	}
	catch (...)
	{
		// ���쳣���õ�p
		cout << "���쳣���ø�p! " << endl;
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

// ���廥����
mutex PrintMutex;
mutex PrintMutex1;
timed_mutex TimedMutex;

// ѭ����ӡ�ַ�
void printString(const string& str)
{
	// ���� ������ʱ�ͷ� RAII-Resource Acquisition Is Initialization
	// RAII��Ҳ��Ϊ����Դ��ȡ���ǳ�ʼ��������c++�ȱ�����Գ��õĹ�����Դ�������ڴ�й¶�ķ�����
	// ����֤���κ�����£�ʹ�ö���ʱ�ȹ�����������������
	lock_guard<mutex> lockprint(PrintMutex);

	// ������ӡ�ַ�
	cout << GetCurrentThreadId();
	for (auto& it : str)
	{
		cout.put(it);
	}
	cout << endl;


	// �ж��ܷ�LOCK ʧ�ܾͷ���FLASE �������,��lock_guard
	if (PrintMutex1.try_lock())
	{
		cout << GetCurrentThreadId()  << " PrintMutex1.try_lock() == T" << endl;
		
		// �ɹ�����Ҫ�ͷ� ����2ѡ1
		PrintMutex1.unlock();
		//lock_guard<mutex> lock2(PrintMutex1, adopt_lock);
	}
}

int v = 1;
void critical_section(int change_v) 
{
	static std::mutex mtx;

	// ���� ������ʱ�ͷ� RAII-Resource Acquisition Is Initialization
	std::unique_lock<std::mutex> lock(mtx);
	
	v = change_v;
	cout << GetCurrentThreadId() << " unique_lock v= " << v << std::endl;

	// �⿪�� ��������.���ں����ڷֶ�LOCK
	lock.unlock();

	// �ֿ����ټ���,�������Զ���������
	//lock.lock();
	v += 1;
	cout << GetCurrentThreadId() << " lock.lock v= " << v << std::endl;
	cout << GetCurrentThreadId() << " lock.lock v= " << v << std::endl;
}

// ����once���� ֻ����һ��
void OnceCallFunc(vector<int>& vct)
{
	// ֻ��ִ��һ�� ���ڶ��߳��еĳ�ʼ������
	vct.resize(10, 2);
	cout << "OnceCallFunc only once come!" << endl;
}

vector<int> OnceVector;

// ֻ����һ�εĺ���
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

// ���������߳�1
void Thread1()
{
	cout << "Thread1 : " << endl;
	cin.get();

	{
		// �������� ��readyFlag����ΪT
		lock_guard<mutex> lg(readyMutex);
		readyFlag = true;
		cout << "set readyFlag true!" << endl;
	}
	// ֪ͨ readyCondVar.wait
	readyCondVar.notify_one();
}

// ���������߳�2
void Thread2()
{
	{
		unique_lock<mutex> ul(readyMutex);

		// �������ѭ���жϺ͵ȴ�[]{}����ֵΪT. ΪT����ִ����ȥ.
		readyCondVar.wait(ul, [] {
			cout << "wait readyFlag = " << readyFlag << endl; 
			return readyFlag; 
		});

		cout << "readyCondVar.waited" << endl;
	}

	cout << "done" << endl;
}

// Queue ������������
queue<int> myQueue;
mutex queueMutex;
condition_variable queueCondVar;


// �ź����� ������
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

// �ź����� ������
void consumer(int num)
{
	std::cout << "call consumer  num = " << num << endl;

	// ��ѭ���ȴ��ź�,queue���վͻ��ӡ��pop
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

// ԭ�ӵı�־,ȷ��ԭ�Ӳ�������.
atomic<bool> atomicFlag(false);

// �ź����� ������
void AtomicProvider(int val)
{
	cout << "AtomicProvider input: " << endl;
	int i;
	cin >> i;
	myQueue.push(i);

	atomicFlag.store(true);
}

// �ź����� ������
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

/////////////////////////////����ӿ�/////////////////////////////////////////////
// MultiThread
void MultiThread::BeginTest()
{
	cout << __FILE__ << "  " << __FUNCTION__ << endl;

	// ��̵��߳�
	if (0)
	{
		thread t( [](){cout << "thread short" << endl;} );

		// 	1 waits for the thread to finish its execution
		t.join();

		// 2 ��ִ���߳����̶߳���ֿ����������ִ�С��߳��˳��󣬽��ͷ��κη������Դ
		//t.detach();
	}

	// C++11 THREAD_LOCAL �� join
	if (0)
	{
		// thread_local int count = 1; �̰߳�ȫ
		std::thread t1(tl_func, "t1"); // 12345
		std::thread t2(tl_func, "t2"); // 12345
		t1.join();
		t2.join();
	}

	// async and future �����ʹ���첽����
	if (0)
	{
		cout << "func1 in background func2 in foreground : " << endl;

		// �첽����һ�������߳��ں�̨,����ȷ����ʱ��
		future<int> result1 = async(func1);

		// ��ȷ���첽��ʽ����Ŀ�꺯��,����޷�����.�׳��쳣.
		future<int> result2 = async(launch::async, func1);

		// ǿ���ӻ�����,����ȵ�get����
		future<int> result3 = async(launch::deferred, func2);

		// wait��ǿ��ִ�к�̨�첽�߳�.getҲ��ǿ�Ʋ����õ�����ֵ
		result1.wait();	// Ҫ��result1ִ�����
		result3.get();

		// ����get����func1��ִ֤�����.�ڵ��߳���Ҳ���Ա�֤. getֻ�ܵ���һ��.
		int result = result1.get() + func2(); // 1+1 ֻ�ɻ�ȡһ��get
		cout << endl << "result1.get() + func2() = " << result << endl;
		// �����Ч��  get֮�����Ч��
		cout << "result1.valid() = " << result1.valid() << endl;
	}

	// 2���첽������԰���
	if (0)
	{
		char c = '*';
		char d = '#';
		auto f1 = async([=] {dosomething(c); });
		auto f2 = async(dosomething, d);

		// ���2���첽������һ������
		if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
			f2.wait_for(chrono::seconds(0)) != future_status::deferred)
		{
			// ���ٵȴ�һ���첽ִ�н���������
			while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
					f2.wait_for(chrono::seconds(0)) != future_status::ready)
			{
				//cout << "this_thread::yield()" << endl;
				this_thread::yield();
			}
		}

		cout.put('\n').flush();

		cout << "go try: " << endl;

		// ���ʱ����2����ǿ�����кͷ��ؽ��,�������һ����û��ִ�����
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

	// ����shared_future
	if (0)
	{
		// fΪ������첽ִ��,���һ�ݸ�f1 f2 f3ʹ��
		//shared_future<int> f = async(queryNumber);
		auto f = async(queryNumber).share();

		// dosomething2 ��f.get(),��������һ������.
		auto f1 = async(launch::async, dosomething2, '.', f);
		auto f2 = async(launch::async, dosomething2, '+', f);
		auto f3 = async(launch::async, dosomething2, '-', f);

		f1.get();
		f2.get();
		f3.get();

		cout << "\ndone" << endl;
	}

	// �ײ�ӿ�thread
	if (0)
	{
		// ���ؿ��ܵ��߳�����,I7����������8. ���첽�̺߳�����Ҳ��8.
		cout << "hardware_concurrency " << thread::hardware_concurrency() << endl;

		cout << "�ж���Ч��ʹ��id(),��Ҫ����0. = " << thread::id() << endl;

		thread t1(dosomething, '*');
		cout << "start t1-1 :" << t1.get_id() << endl;

		// ѭ�������߳��ں�ִ̨��.�������߳��˳����Ӱ��
		for (auto i = 0; i < 5; i++)
		{
			thread t(dosomething, 'a'+i);
			cout << "detach started background thread: " << t.get_id() << " c = " << 'a' + i << endl;
			t.detach();
		}

		cin.get();

		// ǿ�Ƶȴ�����   ���� ʹ��detach����. ����ᱨ��
		cout << "ǿ�Ƶȴ�t1����.  join :" << t1.get_id() << endl;

		// ִ����t1.join �ͻ��˳����߳�. ��ѭ���п������̼߳����ں�ִ̨��.
		t1.join();

		cout << "\nt1.join() ִ�����" << endl;

	}

	// �ײ�promise ��������,������ֵ
	if (0)
	{
		try
		{
			// ����һ���߳�,��������promise����
			promise<string> p;
			thread t(ModificationString, ref(p));
			t.detach();

			// ֻ���Ե���һ��get_future
			future<string> f(p.get_future());

			// get()���ûᱣ֤promise������ֵ���쳣,����֤�߳�ִ�����!
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
		// packaged_taskͬʱ����Ŀ�꺯���ͽ��
		packaged_task<int(char)> task(dosomething);

		cout << "task(dosomething)" << endl;

		// ��ȡ���
		future<int> f = task.get_future();
		cout << "task get_future" << endl;

		// ִ��task�ڵĺ���,ʹ���Ϊready
		cout << "call task(&)" << endl;
		task('&');

		// ��ȡ���
		int result = f.get();
		cout << "\nf.get() " << result << endl;
	}

	// MUTEX  lock_guard unique_lock
	if (0)
	{
		// 3���߳�,ͬʱѭ����ӡ�ᵼ����! ����lock_guard<mutex>
		auto f1 = async(launch::deferred, printString, "f1, My name is Mike!");
		auto f2 = async(launch::async, printString, "f2, This is my book!");
		auto f3 = async(launch::deferred, printString, "f3 lock_guard!");

		// �����������˳���޷���֤,���໥����!
		f1.get();
		f2.get();
		f3.get();

		printString("Here is the main thread!");

		// ����unique_lock �����ͽ�������� �ɰ���ֶμ���
		thread t1(critical_section, 1), t2(critical_section, 2), t3(critical_section, 3);
		t1.detach();
		t2.detach();
		t3.detach();
	}

	// ֻ����һ�� ��ʼ��������;
	if (0)
	{
		// ��ε��� ֻ��ִ��һ��.
		//OnlyOnceCall();
		//OnlyOnceCall();
		//OnlyOnceCall();

		// ���̵߳���Ҳ�ܱ�֤��ȫ
		auto f1 = async(OnlyOnceCall);
		auto f2 = async(OnlyOnceCall);
		auto f3 = async(OnlyOnceCall);
	}

	// ���̻߳���
	if (0)
	{
		auto f1 = async(launch::async, Thread1);
		auto f2 = async(launch::async, Thread2);
	}

	// ���̶߳�ȡQueue��д. ������������
	if (0)
	{
		// ����������
		auto p1 = async(provider, 100);
		auto p2 = async(provider, 200);
		auto p3 = async(provider, 300);

		p1.get();

		// ���������� �̰߳�ȫ����ͬһ��queue
		auto c1 = async(launch::async, consumer, 1);
		auto c2 = async(launch::async, consumer, 2);
	}

	// ʹ��atomic����д
	if (0)
	{
		// ���������� �̰߳�ȫ����ͬһ��queue
		auto f1 = async(launch::async, AtomicProvider,100);
		auto c1 = async(launch::async, AtomicConsumer);
	}

	// ʹ���Զ����allocate
	if (0)
	{
		vector<int, MyAlloc<int>> myVct(1,1);
		myVct.push_back(1);
		myVct.pop_back();
		myVct.clear();
	}
}
