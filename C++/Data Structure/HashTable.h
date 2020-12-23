#pragma once
#include<iostream>
#include<cmath>
#include<string>
using std::string;
constexpr auto MAXTABLESIZE = 100000;

template<class T>
class LNode;					// 链表元素模板类声明

template<class T>
using PtrToLNode = LNode<T>*;	// 链表指针别名

template<class T>
class LNode {				// 散列表单元元素
public:
	T Data;					// 键值
	PtrToLNode<T> Next;		// 链表指针
	LNode<T>(T init = "", PtrToLNode<T> ptr = nullptr);		// 构造函数默认值赋值为空字符串
};

template<class T>
inline LNode<T>::LNode(T init, PtrToLNode<T> ptr) {
	Data = init;
	Next = ptr;
}

inline int nextPrime(int N) {
	int i, p = (N % 2) ? N + 2 : N + 1;

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p % i))break;			// p不是素数
		if (i == 2)break;				// p是素数
		else p += 2;
	}
	return p;
}

template<class T>
using List = PtrToLNode<T>;

template<class T>
using Position = List<T>;


template<class T>
class TblNode {				// 散列表
public:
	List<T>  Heads;			// 表头指针
	int TableSize;
};

template<class T>
using HashTable = TblNode<T>*;

inline int hash(string Key, int TableSize) {			// 字符串散列函数
	unsigned int H = 0;				// 散列函数值初始化为0
	int i = 0;
	while (Key[i] != '\0') {
		H = (H << 5) + Key[i++];
	}

	return H % TableSize;
}

template<class T>
HashTable<T> createTable(int size) {
	HashTable<T> H = new TblNode<T>;				// 创建散列表指针

	H->TableSize = nextPrime(size);					// 散列表大小为
	H->Heads = new LNode<T>[H->TableSize];			// 创建链表头结点数组
	return H;
}

template<class T>
Position<T> Find(HashTable<T> H, T Key) {
	int pos = hash(Key, H->TableSize);

	Position<T> cur = H->Heads[pos].Next;			// 链表头结点中的next指针

	while (cur != nullptr && cur->Data != Key) {
		cur = cur->Next;
	}

	return cur;										// 未找到返回空指针，否则返回链表元素
}

template<class T>
bool Insert(HashTable<T> H, T Key) {
	int pos = hash(Key, H->TableSize);
	Position<T> p = Find(H, Key);

	if ( p == nullptr) {			// 未找到关键词 插入到散列表相应链表第一个结点

		Position<T> next = H->Heads[pos].Next;
		H->Heads[pos].Next = new LNode<T>(Key, next);

		return true;
	}
	else {
		std::cout << "关键词已存在！\n";
		return false;
	}
}

template<class T>
bool Delete(HashTable<T> H, T Key) {
	Position<T> p = Find(H, Key);

	if (p == nullptr) {
		std::cout << "关键词不在列表中！\n";
		return false;
	}
	else {
		int pos = hash(Key, H->TableSize);
		Position<T> cur = &H->Heads[pos];
		while (cur->Next->Data != Key)
			cur = cur->Next;
		cur->Next = p->Next;
		delete p;
		return true;
	}
}

template<class T>
void destroyTable(HashTable<T> H) {
	Position<T> cur = nullptr;
	Position<T> np = nullptr;

	for (int i = 0; i < H->TableSize; i++) {
		cur = H->Heads[i].Next;
		while (cur != nullptr) {
			np = cur->Next;
			delete cur;
			cur = np;
		}
	}

	delete[]H->Heads;					// 释放头结点数组
	delete H;							// 释放散列表
}