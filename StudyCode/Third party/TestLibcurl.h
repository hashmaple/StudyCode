//--------------------------------------------------------------------
// �ļ���:		TestLibcurl
// ��  ��:		
// ˵  ��:		
// ��������:	2020��9��23��
// ��������:	2020��9��23��
// ������:		Maple(������)
//--------------------------------------------------------------------
#pragma once

/* ʹ�ò���
1. ����curl_global_init()��ʼ��libcurl
2. ����curl_easy_init()�����õ� easy interface��ָ��
3. ����curl_easy_setopt()���ô���ѡ��
4. ����curl_easy_setopt()���õĴ���ѡ�ʵ�ֻص�����������û��ض�����
5. ����curl_easy_perform()������ɴ�������
6. ����curl_easy_cleanup()�ͷ��ڴ�
7.����curl_global_cleanup()����libcurl
����������������curl_easy_setopt()��������ؼ��ģ��������е�libcurl����Ҫʹ������

�ڻ���LibCurl�ĳ������Ҫ����callback function ���ص�����������ʽ��ɴ�������
�û�����������ǰ���úø�������ͻص�����������������ʱlibcurl�������û��Ļص�����ʵ���ض����ܡ�
*/

class TestLibcurl
{
public:
	TestLibcurl(void);
	~TestLibcurl(void);

	// ����ӿ�
	void BeginTest();
};
