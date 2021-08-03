// MyCMemoryManager.cpp : 定义控制台应用程序的入口点。
//
#include "MemoryManager/MyCMemoryManager.h"
#include "MemoryManager/MyVector.h"
#include "MemoryManager/MyString.h"
#include "MemoryManager/MyQueue.h"
#include "MemoryManager/MyMap.h"
#include "MemoryManager/MySet.h"

#if WIN32
#include <Windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x) * 1000)
#endif

int main(int argc, char* argv[])
{
	MyCMemoryManager::getInstance()->setPoolSize(1024 * 1024, 1024 * 1024, 1024 * 1024*10);
	MyCMemoryManager::getInstance()->init();//初始化内存池

	//两种使用方式，一种，所有的类都使用内存管理（暂时有问题，类的函数不能写死循环）

	//第二种，只有部分数据结构使用内存管理模块，其他的操作仍然和c++一致

#if 0
	//auto mc = MyCMemoryManager::alloc(100);
	auto mv = MyCMemoryManager::getInstance()->allocObject<MyVector<int>>();

	auto str = MyCMemoryManager::getInstance()->allocObject<MyString>();
	str += "hello world";
	//str = "hello world";
	str += 1;
	//str.lockPtr();
	
	
	auto mq = MyCMemoryManager::getInstance()->allocObject<MyQueue<int>>();
	auto ms = MyCMemoryManager::getInstance()->allocObject<MySet<int>>();
	auto ms2 = MyCMemoryManager::getInstance()->allocObject<MySet<SP<MyString>>>();

	auto mm = MyCMemoryManager::getInstance()->allocObject<MyMap<SP<MyString>, SP<MyString>>>();

	mm->set(MyCMemoryManager::getInstance()->allocObject<MyString>("h2"), MyCMemoryManager::getInstance()->allocObject<MyString>("hh4"));
	mm->set(MyCMemoryManager::getInstance()->allocObject<MyString>("h1"), MyCMemoryManager::getInstance()->allocObject<MyString>("hh2"));
	auto th1 = MyCMemoryManager::getInstance()->allocObject<MyString>("h1");
	auto p = mm->get(th1);
	printf("mmap find %s\n", p->c_str());

	for (int i = 1000; i > 0; i--){
		auto tt = MyCMemoryManager::getInstance()->allocObject<MyString>("h");
		tt += i;
		ms2->insert(tt);
	}
	for (int i = 0; i < 1000; i++){
		printf("ms2 i = %s\n", ms2->indexof(i)->c_str());
		Sleep(100);
		//printf("test len=%d %s\n", str->length(), str->c_str());
	}

	for (int i = 1000; i > 0; i--){
		ms->insert(i);
	}
	for (int i = 0; i < 1000; i++){
		printf("ms i = %d\n", ms->indexof(i));
		Sleep(100);
		//printf("test len=%d %s\n", str->length(), str->c_str());
	}

	for (int i = 0; i < 1000; i++){
		mq->push_back(i);
	}

	for (int i = 0; i < 1000; i++){
		printf("mq i = %d\n", mq->front());
		mq->pop();
		Sleep(100);
		//printf("test len=%d %s\n", str->length(), str->c_str());
	}//*/

	for (int i = 0; i < 1000; i++){
		//mv->push_back(i);
		mv->insert(0, i);
		printf("i = %d\n", mv->at(0));
		Sleep(100);
		printf("test len=%d %s\n", str->length(), str->c_str());
	}

	mv.release();

	printf("test len=%d %s\n", str->length(), str->c_str());
	//str.unlockPtr();
	str.release();
	getchar();
#else
	{

		MyString ms = "hello world";
		{
			MyString ms2 = ms;
		}
		ms += 1;
		printf("test ms = %s\n", ms.c_str());
#if 1
		
		{
			MyVector<MyString> mv;
			for (int i = 0; i < 1000; i++){
				mv.push_back(ms);
			}
		}

		
		{
			MyQueue<MyString> mq;
			for (int i = 0; i < 1000; i++){
				ms = "h";
				ms += i;
				mq.push_back(ms);
				Sleep(10);
			}

			for (int i = 0; i < 1000; i++){
				printf("test mq i = %d,%s\n", i, mq.front().c_str());
				mq.pop();
				Sleep(100);
			}
		}
		//*/

		
		MySet<MyString> mss;
		for (int i = 0; i < 1000; i++){
			ms = "hello";
			ms += i;
			mss.insert(ms);
		}

		for (int i = 0; i < 1000; i++){
			printf("mss i = %d,%s\n", i, mss.indexof(i).c_str());
			Sleep(100);
			printf("test ms = %s\n", ms.c_str());
		}//*/

		
		MyMap<MyString, MyString> mm;
		mm.set("h1", "h2");
		mm.set("h2", "h3");

		printf("test mm = %s\n", mm.get("h1").c_str());
		//*/
#endif
		
	}
	MyCMemoryManager::getInstance()->dumpMyCObj("dump.txt");
	getchar();

#endif


	

	/*
	int last = -1;
	for (int i = 0; i < mv->size(); i++){
		//if (mv->at(i) != (last + 1)){
			//printf("error\n");
		//}
		last = mv->at(i);
		printf("i = %d\n",mv->at(i));
		Sleep(100);
	}//*/


	//MyCMemoryManager::getInstance()->freeObject(&mv);

	return 0;
}

