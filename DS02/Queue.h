#pragma once
#include "Linearlist.h"

template<class T>
class Queue
{
public:
	Queue() :storage(), start(0) {}
	Queue(const Queue& other) :storage(other.storage), start(other.start) {}
	//~Queue(); 默认

	bool empty() const { return storage.size() == start; }
	int size() const { return storage.size() - start; }
	void push(const T& input);
	T pop();
	T& getFront() const;
	T& getBack() const;
	void clear();


private:
	SqList<T> storage;
	int start;

};

template<class T>
inline void Queue<T>::push(const T& input)
{
	if (storage.capacity() == storage.size())
	{
	// 若存储已满，有两种可能
	// 一种是数组真的已满，此时不需要额外处理，SqList提供了自动扩容方法
	// 另一种是队列向后移动导致头部空间空余，以下是此情况的处理方法
		if (start)
		{// 并非从头开始
			storage.movForward(start);
			start = 0;
		}// 处理完毕，现在Queue的存储紧贴SqList前部
	}

	storage.insert(storage.size(), input);
}

template<class T>
inline T Queue<T>::pop()
{
	// 不同于storage.erase(storage.size() - 1)
	// storage.erase(0)需要O(n)的时间
	// 因此使用start标记起点，避免每次pop都要移动元素
	if (!storage.empty()) {
		return storage.get(start++);
	}
	else {
		throw("访问失败，队列是空的");
	}
}

// 它们唯一的区别就是是否改start
template<class T>
inline T& Queue<T>::getFront() const
{
	if (!storage.empty()) {
		return storage.get(start);
	}
	else {
		throw("访问失败，队列是空的");
	}
}

template<class T>
inline T& Queue<T>::getBack() const
{
	if (!storage.empty()) {
		return storage.get(storage.size() - 1);
	}
	else {
		throw("访问失败，队列是空的");
	}
}

template<class T>
inline void Queue<T>::clear()
{
	storage.clear();
	start = 0;
}
