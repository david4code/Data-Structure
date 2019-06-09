#pragma once
#include<iostream>
#include<cmath>
#include<string>
using std::string;
constexpr auto MAXTABLESIZE = 100000;

template<class T>
class LNode;					// ����Ԫ��ģ��������

template<class T>
using PtrToLNode = LNode<T>*;	// ����ָ�����

template<class T>
class LNode {				// ɢ�б�ԪԪ��
public:
	T Data;					// ��ֵ
	PtrToLNode<T> Next;		// ����ָ��
	LNode<T>(T init = "", PtrToLNode<T> ptr = nullptr);		// ���캯��Ĭ��ֵ��ֵΪ���ַ���
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
			if (!(p % i))break;			// p��������
		if (i == 2)break;				// p������
		else p += 2;
	}
	return p;
}

template<class T>
using List = PtrToLNode<T>;

template<class T>
using Position = List<T>;


template<class T>
class TblNode {				// ɢ�б�
public:
	List<T>  Heads;			// ��ͷָ��
	int TableSize;
};

template<class T>
using HashTable = TblNode<T>*;

inline int hash(string Key, int TableSize) {			// �ַ���ɢ�к���
	unsigned int H = 0;				// ɢ�к���ֵ��ʼ��Ϊ0
	int i = 0;
	while (Key[i] != '\0') {
		H = (H << 5) + Key[i++];
	}

	return H % TableSize;
}

template<class T>
HashTable<T> createTable(int size) {
	HashTable<T> H = new TblNode<T>;				// ����ɢ�б�ָ��

	H->TableSize = nextPrime(size);					// ɢ�б��СΪ
	H->Heads = new LNode<T>[H->TableSize];			// ��������ͷ�������
	return H;
}

template<class T>
Position<T> Find(HashTable<T> H, T Key) {
	int pos = hash(Key, H->TableSize);

	Position<T> cur = H->Heads[pos].Next;			// ����ͷ����е�nextָ��

	while (cur != nullptr && cur->Data != Key) {
		cur = cur->Next;
	}

	return cur;										// δ�ҵ����ؿ�ָ�룬���򷵻�����Ԫ��
}

template<class T>
bool Insert(HashTable<T> H, T Key) {
	int pos = hash(Key, H->TableSize);
	Position<T> p = Find(H, Key);

	if ( p == nullptr) {			// δ�ҵ��ؼ��� ���뵽ɢ�б���Ӧ�����һ�����

		Position<T> next = H->Heads[pos].Next;
		H->Heads[pos].Next = new LNode<T>(Key, next);

		return true;
	}
	else {
		std::cout << "�ؼ����Ѵ��ڣ�\n";
		return false;
	}
}

template<class T>
bool Delete(HashTable<T> H, T Key) {
	Position<T> p = Find(H, Key);

	if (p == nullptr) {
		std::cout << "�ؼ��ʲ����б��У�\n";
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

	delete[]H->Heads;					// �ͷ�ͷ�������
	delete H;							// �ͷ�ɢ�б�
}