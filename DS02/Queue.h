#pragma once
#include "Linearlist.h"

template<class T>
class Queue
{
public:
	Queue() :storage(), start(0) {}
	Queue(const Queue& other) :storage(other.storage), start(other.start) {}
	//~Queue(); Ĭ��

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
	// ���洢�����������ֿ���
	// һ�������������������ʱ����Ҫ���⴦��SqList�ṩ���Զ����ݷ���
	// ��һ���Ƕ�������ƶ�����ͷ���ռ���࣬�����Ǵ�����Ĵ�����
		if (start)
		{// ���Ǵ�ͷ��ʼ
			storage.movForward(start);
			start = 0;
		}// ������ϣ�����Queue�Ĵ洢����SqListǰ��
	}

	storage.insert(storage.size(), input);
}

template<class T>
inline T Queue<T>::pop()
{
	// ��ͬ��storage.erase(storage.size() - 1)
	// storage.erase(0)��ҪO(n)��ʱ��
	// ���ʹ��start�����㣬����ÿ��pop��Ҫ�ƶ�Ԫ��
	if (!storage.empty()) {
		return storage.get(start++);
	}
	else {
		throw("����ʧ�ܣ������ǿյ�");
	}
}

// ����Ψһ����������Ƿ��start
template<class T>
inline T& Queue<T>::getFront() const
{
	if (!storage.empty()) {
		return storage.get(start);
	}
	else {
		throw("����ʧ�ܣ������ǿյ�");
	}
}

template<class T>
inline T& Queue<T>::getBack() const
{
	if (!storage.empty()) {
		return storage.get(storage.size() - 1);
	}
	else {
		throw("����ʧ�ܣ������ǿյ�");
	}
}

template<class T>
inline void Queue<T>::clear()
{
	storage.clear();
	start = 0;
}
