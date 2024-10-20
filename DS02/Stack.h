#pragma once
#include "Linearlist.h"

template<class T>
class Stack
{
public:
	Stack() :storage() {}
	Stack(const Stack& other) :storage(other.storage) {}
	// ~Stack(); 默认

	bool empty() const { return storage.size() == 0; }
	int size() const { return storage.size(); }
	void push(const T& input);
	T pop();
	T getFront() const;
	void clear();

protected:
	SqList<T> storage;

};

template<class T>
inline void Stack<T>::push(const T& input)
{
	storage.insert(storage.size(), input);
}

template<class T>
inline T Stack<T>::pop()
{
	if (!storage.empty()) {
		T top = storage.get(storage.size() - 1);
		storage.erase(storage.size() - 1);
		return top;
	}
	else {
		throw("访问失败，栈是空的");
	}
}

template<class T>
inline T Stack<T>::getFront() const
{
	if (!storage.empty()) {
		return storage.get(storage.size() - 1);
	}
	else {
		throw("访问失败，栈是空的");
	}
}

template<class T>
inline void Stack<T>::clear()
{
	storage.clear();
}
