#include "C++11.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

// NewFeatures
void NewFeatures::BeginTest()
{
	cout << __FILE__ << "  " <<  __FUNCTION__ << endl;

	// nullptr auto range-based for move
	if (0)
	{
		// nullptr �������� ����תΪ����,��תΪ����ָ������.
		// ���������ܿ�NULLΪ0ʱ�򣬵���int���͵����غ���
		int* p = nullptr;

		// �ж��Ƿ�ͬ����
		if (is_same<decltype(p), int*>::value)
		{
			cout << "decltype(p) ==  int*" << endl;
		}

		// constexpr �������ʽ ���������ʼ����
		constexpr int len = 1 + 1;
		char arr[len];

		// auto �����Զ��Ƶ�. ԭ������Ϊĳ�����Ǿֲ���.
		auto i = 20;

		// һ���Եĳ�ʼ�� ������ʹ�ô�����
		int j{}; // j = 0 ���ʼ��
				 // int k; δ��ʼ�����벻ͨ��
		int values[]{ 1,2,3 };
		vector<int> v = { 2,3,4,5,6 };
		vector<string> vstr = { "zsq", "kyo" };

		// range-based forѭ��
		for (auto element : v) {}			   // �ḳֵ��element,����һ�ݸ���
		for (auto& element : v) { ++element; } // element������,�����޸�
		for (const auto& element : v) {}	   // element�ǳ�������,�����޸�

		// std::move() ��Ǩ���� �����ڱ�����Ǩ����ʹ�õ�����.
		vector<int> v_int1{ 1,2,3,4 };
		vector<int> v_int2(2);

		v_int2 = move(v_int1); // ֱ���ƶ����ݹ���,������һ�θ�������. 

		v_int2.size(); // 4
		v_int1.size(); // 0 ����δָ��,����Ч��״̬ move���ô�����,�÷���ȷ!
	}
	
	// lambda
	if (0)
	{
		int lambda_i = 8;
		int lambda_j = 8;

		// l=�������� []=��ȡ�����ı���     ()�������        ->����ֵ
		auto l = [lambda_i, &lambda_j](int i, const string& s) -> int
		{
			cout << "lambda functon call! input args i-s = " << i << s << endl;
			cout << "lambda_i = " << lambda_i << endl;
			cout << "lambda_j = " << lambda_j << endl;

			lambda_j++;

			return 9527;
		};

		// �ȵ���l����,���������ֵ
		cout << "lambda call return = " << l(1, "maple") << endl;
		cout << "lambda_j = " << lambda_j << endl;	// �ں����������ú��Ѿ����޸�
	}

	// ����ָ�� shared,unique,weak
	if (0)
	{
		// shared_ptr:��¼������һ������ָ�룬 ���ܹ���¼���ٸ� shared_ptr ��ָͬ��һ������ 
		// �Ӷ�������ʾ�ĵ��� delete �� �����ü�����Ϊ���ʱ��ͻὫ�����Զ�ɾ��
		auto shared_pointer = make_shared<int>(10);
		cout << "shared_pointer = " << *shared_pointer << endl;

		// ��ȡԭʼ��ָ��
		auto original_pointer = shared_pointer.get();
		cout << "shared_pointer = " << shared_pointer.get() << endl;
		cout << "original_pointer = " << original_pointer << endl;

		// �鿴��������ü���
		auto shared_pointer2 = shared_pointer;
		cout << "use_count = " << shared_pointer.use_count() << endl;

		// �ͷ� ����һ������
		shared_pointer2.reset();
		cout << "use_count = " << shared_pointer.use_count() << endl;

		// ȫ�ͷź� �ٲ鿴ԭʼָ������������
		cout << "original_pointer = " << *original_pointer << endl;
		shared_pointer.reset();
		cout << "original_pointer = " << *original_pointer << endl;


		// unique_ptr ��ռ������ָ�룬 ����ֹ��������ָ�����乲��ͬһ�����󣬴Ӷ���֤����İ�ȫ
		auto unique_pointer = make_unique<int>(20);
		cout << "unique_pointer = " << *unique_pointer << endl;

		// �Ƿ��Ļ�ȡ
		//auto unique_pointer2 = unique_pointer;

		// ��ʹ��moveת�� ת�ƺ��ָ��ʧЧ
		auto unique_pointer2 = move(unique_pointer);
		cout << "unique_pointer = " << *original_pointer << endl;
		cout << "unique_pointer2 = " << *unique_pointer2 << endl;

		// �ͷſ���Ȩ�����ͷ��ڴ�
		auto p = unique_pointer2.release();
		cout << "p = release() = " << *p << endl;

		// �ͷ��ڴ�
		unique_pointer2.reset();
		// �ͷ��ڴ�
		unique_pointer2 == nullptr;

		// weak_ptr ���shared_ptr�����룬���shared_ptr���໥����
		// ��ӵ����Դ������Ȩ������ֱ��ʹ�á��� * �� ->
		// ͨ��lock��ȡ����expired����Ƿ���ڡ�
		auto shared_p = make_shared<string>("This is shared_ptr!");

		// �����Ӽ���
		weak_ptr<string> weak_p = shared_p;

		// û�й��ڣ��������
		if (!weak_p.expired())
		{
			weak_p.lock();
			cout << "*weak_p.lock() = " << *weak_p.lock() << endl;
		}

		// ���
		weak_p.reset();
	}

	// dynamic_cast static_cast const_cast
	if (false)
	{
		// static_cast ������ֵ����ת�� �������������ת��
		int i = static_cast<int>(1.1f);
		
		// �����������ת��
		auto pSon = make_shared<SonNewFeatures>();
		auto pFaClass = static_cast<NewFeatures*>(pSon.get());	// ��ת�� ����
		auto pSonClass = static_cast<SonNewFeatures*>(pFaClass);// ��ת�� ���Ƽ�
		cout << "pFaClass virFunc = " << pFaClass->virFunc() << endl;
		cout << "pSonClass virFunc = " << pSonClass->virFunc() << endl;
		
		// dynamic_cast ��֮���ת�� ���ٰ���1���麯��
		pFaClass = dynamic_cast<NewFeatures*>(pSonClass);
		pSonClass = dynamic_cast<SonNewFeatures*>(pFaClass);

		// const_cast ��const
		string s1 = "abcdefg";
		char* str1 = const_cast<char*>(s1.c_str());
		str1[1] = 0;	// �ǳ�Σ�գ���������

		// ���� ���ֻ��a�� ������ȻΪ7
		cout << "s1 = " << s1.c_str() << endl;
		cout << "s1.size = " << s1.size() << endl;
		cout << "str1 = " << str1 << endl;
	}

	// �������� ������R
	if (0)
	{
		// ���������ַ����ַ���
		std::string str = R"(C:\File\To\Path)";
		std::cout << str << std::endl;
	}

	return;
}
