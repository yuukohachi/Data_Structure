#pragma once
#include "classes.h"
#include <string>

template<class T>
SqList<T> merge(SqList<T> sq1, SqList<T> sq2)
{
	SqList<T> result(sq1.size() + sq2.size());

	int i = 0, j = 0, resIndex = 0;
	while (i < sq1.size() && j < sq2.size())
	{
		if (sq1.get(i) <= sq2.get(j)) {
			result.insert(resIndex, sq1.get(i));
			++i; ++resIndex;
		}
		else {
			result.insert(resIndex, sq2.get(j));
			++j; ++resIndex;
		}
	}

	if (i != sq1.size() && j == sq2.size()) {// sq1有剩余
		while (i < sq1.size())
		{
			result.insert(resIndex, sq1.get(i));
			++i; ++resIndex;
		}
	}

	if (i == sq1.size() && j != sq2.size()) {// sq2有剩余
		while (j < sq2.size())
		{
			result.insert(resIndex, sq2.get(j));
			++j; ++resIndex;
		}
	}

	return result;
}

template<class T>
LinkList<T> merge(LinkList<T> lk1, LinkList<T> lk2)
{
	LinkList<T> result;
	result.insert(0, NULL);// 添加一个空的头节点，以便与后续操作相容
	
	typename LinkList<T>::Iterator it_i = lk1.begin(), it_j = lk2.begin(), it_r = result.begin();
	while (it_i != NULL && it_j != NULL)
	{
		if (*it_i <= *it_j) {
			it_r.iterInsert(*it_i);
			++it_i; ++it_r;
		}
		else {
			it_r.iterInsert(*it_j);
			++it_j; ++it_r;
		}
	}

	if (it_j == NULL && it_i != NULL) {// lk1有剩余
		while (it_i != NULL)
		{
			it_r.iterInsert(*it_i);
			++it_i; ++it_r;
		}
	}

	if (it_i == NULL && it_j != NULL) {// lk2有剩余
		while (it_j != NULL)
		{
			it_r.iterInsert(*it_j);
			++it_j; ++it_r;
		}
	}

	result.recount();// 调用 iterInsert() 后需要更新 numOfElem

	result.erase(0);// 删除空的头节点

	return result;
}

template<class T>
void deduplicate(LinkList<T>& lk)
{
	if (lk.size() < 2) return;

	T a = lk.get(0), b = lk.get(1);
	int index;// b的索引
	typename LinkList<T>::Iterator it = lk.begin(); ++it;

	for (index = 1; index < lk.size(); ++index)
	{
		if (a == b) {
			b = *(++it);
			lk.erase(index);// 这违背了 iterator 的初衷，但是如果不这么做，erase() 就白写了
		}
		else {
			a = b;
			b = *(++it);
		}
	}
}

template<class T>
void reverse(LinkList<T>& lk)
{
	LinkList<T> temp;
	typename LinkList<T>::Iterator it = lk.begin();
	int loopVar = lk.size();

	while (loopVar) {
		temp.insert(0, (*it));
		++it; --loopVar;
	}

	lk = temp;
}



// 选做题的函数
// 选做题目会相对随心所欲一些，对于输入处理等非核心部分，会使用STL以简化代码

SqList<int> polynomialRead();

void polynomialOut(const SqList<int>& sq);

void split(HeadedLinkList<int>& input, HeadedLinkList<int>& La, HeadedLinkList<int>& Lb);