#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>

// 线性表（抽象）
template<class T>
class LinearList
{
public:
	virtual bool empty() const = 0;// 判空
	virtual int size() const = 0;// 返回元素个数
	virtual T& get(int theIndex) const = 0;// 返回标号为theIndex的元素
	virtual int find(const T& theElement) const = 0;// 查找元素theElement首次出现的标号
	virtual void erase(int theIndex) = 0;// 删除标号为theIndex的元素
	virtual void insert(int theIndex, const T& theElement) = 0;// 将元素theElement插入到标号theIndex处
	virtual void output(std::ostream& os) const = 0;// 输出整个表
};





// 顺序表
template<class T>
class SqList :public LinearList<T>
{
public:
	SqList(int initSize = 10);
	SqList(const SqList<T>&);
	~SqList() { delete storage; }

	//ADT
	bool empty() const override { return numOfElem == 0; }
	int size() const override { return numOfElem; }
	T& get(int theIndex) const override;
	int find(const T& theElement) const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T& theElement) override;
	void output(std::ostream& os) const override;

	int capacity() const { return storSize; }

	void change(int theIndex, const T& newElement);

protected:
	T* storage;
	int storSize;
	int numOfElem;

	void index_legal(int theIndex) const;
};

template<class T>
inline SqList<T>::SqList(int initSize)
{
	if (initSize < 1) {
		throw ("表长必须大于0");
	}
	storSize = initSize;
	storage = new T[storSize];
	numOfElem = 0;
}

template<class T>
SqList<T>::SqList(const SqList<T>& other)
{
	storSize = other.storSize;
	numOfElem = other.numOfElem;
	storage = new T[storSize];
	std::copy(other.storage, other.storage + storSize, storage);
}

template<class T>
void SqList<T>::index_legal(int theIndex) const
{
	if (theIndex < 0 || theIndex >= numOfElem) {
		throw ("超范围访问");
	}
}

template<class T>
T& SqList<T>::get(int theIndex) const
{
	index_legal(theIndex);
	return storage[theIndex];
}

template<class T>
int SqList<T>::find(const T& theElement) const
{
	for (int index = 0; index < numOfElem; ++index) {
		if (theElement == storage[index]) {
			return index;
		}
	}
	return -1;// not found
}

template<class T>
void SqList<T>::insert(int theIndex, const T& theElement)
{
	// 此处不使用index_legal()，是因为可以在空表的0位置插入
	if (theIndex < 0 || theIndex > numOfElem) {
		throw ("超范围访问");
	}

	if (theIndex == storSize)// 若插入元素时存储已满，倍增存储空间
	{
		T* temp = new T[storSize * 2];
		std::copy(storage, storage + storSize, temp);
		delete storage;
		storage = temp;
		storSize *= 2;
	}

	// 手动实现copy_backward()
	for (int i = numOfElem; i != theIndex; --i)
	{// 将第i个元素复制到i+1的位置
		storage[i] = storage[i - 1];
	}

	storage[theIndex] = theElement;
	++numOfElem;
}

template<class T>
void SqList<T>::erase(int theIndex)
{// 这里仿照了vector的思路，删除元素时检查删除后的容器利用率，若占用 <= 1/4 则容量减半
	index_legal(theIndex);

	if (numOfElem - 1 <= storSize / 4)
	{
		T* temp = new T[storSize / 2];
		if (theIndex) {// 当删除0位置的元素时，显然没有这一步
			std::copy(storage, storage + theIndex - 1, temp);
		}
		std::copy(storage + theIndex + 1, storage + numOfElem, temp);
		delete[] storage;
		storage = temp;
	}
	else
	{
		for (int i = theIndex; i != numOfElem; ++i)
		{// 将第i个元素复制到i-1的位置
			storage[i] = storage[i - 1];
		}// 其实这里也可以std::copy()...虽然是STL
	}

	--numOfElem;
}

template<class T>
inline void SqList<T>::change(int theIndex, const T& newElement)
{
	storage[theIndex] = newElement;
}


template<class T>
void SqList<T>::output(std::ostream& os) const
{// 以空格隔开的输出流
	std::copy(storage, storage + numOfElem, std::ostream_iterator<T>(os, " "));
}
// 同时，提供 << 的形式
template <class T>
std::ostream& operator<<(std::ostream& os, const SqList<T>& s)
{
	s.output(os);
	return os;
}






// 链表

// 前向声明，以设置友元(这太蠢了)
template <class T>
class HeadedLinkList;

// 节点结构体
template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;

	chainNode(){}
	chainNode(const T& element) {
		this->element = element;
		this->next = NULL;
	}
	chainNode(const T& element, chainNode<T>* next) {
		this->element = element;
		this->next = next;
	}
};

// 链表类
template<class T>
class LinkList:public LinearList<T>
{
public:
	LinkList(int initSize = 1);
	LinkList(const LinkList<T>&);
	~LinkList();

	//ADT
	bool empty() const override { return numOfElem == 0; }
	int size() const override { return numOfElem; }
	T& get(int theIndex) const override;
	int find(const T& theElement) const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T& theElement) override;
	void output(std::ostream& os) const override;

	void recount();
	void clear();
	LinkList<T>& operator=(const LinkList<T>& other);

	// 迭代器 
	class Iterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = chainNode<T>;
		using difference_type = std::ptrdiff_t;
		using pointer = chainNode<T>*;
		using reference = chainNode<T>&;

		Iterator(chainNode<T>* ptr = NULL) : current(ptr) {}
		Iterator& operator=(const Iterator& other) {
			current = other.current;
		}

		T& operator*() const { return current->element; }
		Iterator& operator++() {
			current = current->next;
			return *this;
		}
		bool operator==(const Iterator& other) const {
			return current == other.current;
		}
		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

		void iterInsert(const T& theElement) {
			chainNode<T>* ptrNext = new chainNode<T>(theElement, current->next);
			current->next = ptrNext;
		}

	private:
		chainNode<T>* current;
	};

	Iterator begin() { return Iterator(firstNode); }
	Iterator end() { return Iterator(NULL); }

	friend HeadedLinkList<T>;

protected:
	chainNode<T>* firstNode;
	int numOfElem;

	void index_legal(int theIndex) const;
};

template<class T>
inline LinkList<T>::LinkList(int initSize)
{
	if (initSize < 1) {
		throw ("表长必须大于0");// 这并无实际意义，只是为了与顺序表相容
	}
	firstNode = NULL;
	numOfElem = 0;
}

template<class T>
inline LinkList<T>::LinkList(const LinkList<T>& other)
{
	numOfElem = other.numOfElem;

	if (!numOfElem) {// 空表
		firstNode = NULL;
	}
	else{// 非空情况下
		chainNode<T>* opNode = other.firstNode;
		firstNode = new chainNode<T>(opNode->element);
		opNode = opNode->next;
		chainNode<T>* targNode = firstNode;
		while (opNode != NULL)
		{
			targNode->next = new chainNode<T>(opNode->element);
			targNode = targNode->next;
			opNode = opNode->next;
		}
		targNode->next = NULL;
	}
}

template<class T>
inline LinkList<T>::~LinkList()
{
	while (firstNode!=NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
inline void LinkList<T>::index_legal(int theIndex) const
{
	if (theIndex < 0 || theIndex >= numOfElem) {
		throw ("超范围访问");
	}
}

template<class T>
inline T& LinkList<T>::get(int theIndex) const
{
	index_legal(theIndex);
	chainNode<T>* currNode = firstNode;
	for (int i = 0; i < theIndex; ++i) {
		currNode = currNode->next;
	}
	return currNode->element;
}

template<class T>
inline int LinkList<T>::find(const T& theElement) const
{
	chainNode<T>* currNode = firstNode;
	int index = 0;
	while (currNode!=NULL&&currNode->element!=theElement)
	{
		currNode = currNode->next;
		++index;
	}
	if (currNode == NULL) {
		return -1;// 未找到
	}
	else {
		return index;
	}
}

template<class T>
inline void LinkList<T>::erase(int theIndex)
{
	index_legal(theIndex);
	chainNode<T>* deleteNode;
	if (theIndex == 0) 
	{// 删除头节点
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex-1; ++i) {
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
	}

	delete deleteNode;
	--numOfElem;
}

template<class T>
inline void LinkList<T>::insert(int theIndex, const T& theElement)
{
	// 此处不使用index_legal()，是因为可以在空表的0位置插入
	if (theIndex < 0 || theIndex > numOfElem) {
		throw ("超范围访问");
	}

	if (theIndex == 0) {
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else {
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; ++i) {
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);
	}

	++numOfElem;
}

template<class T>
inline void LinkList<T>::output(std::ostream& os) const
{
	for (chainNode<T>* currNode = firstNode;
		currNode != NULL;
		currNode = currNode->next) {
		os << currNode->element << " ";
	}
}

template<class T>
inline void LinkList<T>::recount()
{// 更新 numOfElem
	numOfElem = 0;
	chainNode<T>* p = firstNode;
	while (p!=NULL)
	{
		++numOfElem;
		p = p->next;
	}
}

template<class T>
void LinkList<T>::clear()
{
	while (firstNode != NULL)
	{
		chainNode<T>* temp = firstNode;
		firstNode = firstNode->next;
		delete temp;
	}
	numOfElem = 0;
}

template<class T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T>& other)
{
	if (this != &other) {// 避免自我赋值
		this->clear();

		// 深拷贝
		numOfElem = other.numOfElem;
		if (numOfElem == 0) {
			firstNode = NULL;
		}
		else {
			chainNode<T>* opNode = other.firstNode;
			firstNode = new chainNode<T>(opNode->element);
			opNode = opNode->next;
			chainNode<T>* targNode = firstNode;

			while (opNode != NULL) {
				targNode->next = new chainNode<T>(opNode->element);
				targNode = targNode->next;
				opNode = opNode->next;
			}
			targNode->next = NULL;
		}
	}

	return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const LinkList<T>& l) {
	l.output(os); return os;
}





// 选做题：带头节点的单链表
template <class T>
class HeadedLinkList
{
public:
	HeadedLinkList() {
		head = new chainNode<T>;// 头节点
		head->next = link_list.firstNode;
	}
	~HeadedLinkList() {
		link_list.clear();
		delete head;
	}

	void insert(int theIndex, const T& theElement) {
		link_list.insert(theIndex, theElement);
		if(!theIndex) {// 在 list 的首节点插入,需要更新 head
			head->next = link_list.firstNode;
		}
	}

	void erase(int theIndex) {
		link_list.erase(theIndex);
		if (!theIndex) {// 在 list 的首节点删除,需要更新 head
			head->next = link_list.firstNode;
		}
	}

	int size() const { return link_list.size(); }

	void clear() { link_list.clear(); }

	void recount() { link_list.recount(); }

	void output(std::ostream& os) const { link_list.output(os); }

	class Iterator {
	public:
		Iterator(chainNode<T>* node) : current(node) {}

		T& operator*() { return current->element; }

		Iterator& operator++() {
			current = current->next;
			return *this;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

		void iterInsert(const T& theElement) {
			chainNode<T>* ptrNext = new chainNode<T>(theElement, current->next);
			current->next = ptrNext;

			if (*this==link_list.begin()) {// 在 list 的首节点插入,需要更新 head
				head->next = link_list.firstNode;
			}
		}

	private:
		chainNode<T>* current;
	};

	// 迭代器将会跳过头节点
	Iterator begin() const { return Iterator(head->next); }
	Iterator end() const { return Iterator(NULL); }

private:
	chainNode<T>* head;// 头节点
	LinkList<T> link_list;// 一个 LinkList 对象，实际数据操作由它提供
};

template<class T>
std::ostream& operator<<(std::ostream& os, const HeadedLinkList<T>& l) {
	l.output(os); return os;
}
