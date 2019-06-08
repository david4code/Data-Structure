#pragma once
#include<iostream>
#include<cmath>
using EntryType = enum { Empty, Legitimate, Deleted };
constexpr auto MAXTABLESIZE = 100000;
using Pos = int;				// 散列索引


static int nextPrime(int init) {	// 返回大于init且不超过MAXTABLESIZE的素数
	int i, p = (init % 2) ? init + 2 : init + 1;

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p%i))break;
		if (i == 2)break;				// p为素数
		else							// 继续寻找素数
			p += 2;
	}
	return p;
}

template<class T>
class Cell {				// 散列表单元元素
public:
	T Data;					// 键值
	EntryType Info;			// 元素状态
};

template<class T>
class TblNode {				// 
public:
	Cell<T>   *Cells;
	int TableSize;
};

template<class T>
using HashTable = TblNode<T>*;

template<class T>
HashTable<T> createTable(int TableSize) {
	HashTable<T> H = new TblNode<T>;
	int size = nextPrime(TableSize);		// 确定散列表长度

	H->TableSize = size;
	H->Cells = new Cell<T>[H->TableSize];

	for (int i = 0; i < H->TableSize; i++)	// 写入散列表初始长度
		H->Cells[i].Info = Empty;

	return H;
}

template<class T>
int Hash(T key, int size) {			// 确定散列值
	return key % size;
}

template<class T>
Pos Find(HashTable<T> H, T Key) {
	Pos curPos, newPos;
	curPos = newPos = Hash(Key, H->TableSize);
	int cNum = 0;				// 冲突计数

	while (H->Cells[newPos].Info != Empty &&	// 当前位置状态不为Empty，且该位置元素不是要找的元素时产生冲突
		H->Cells[newPos].Data != Key) {		// 平方探测法
		if (++cNum % 2) {
			newPos = curPos + (cNum + 1)*(cNum + 1) / 4;
			if (newPos >= H->TableSize)
				newPos %= H->TableSize;
		}
		else {
			newPos = curPos - cNum * cNum / 4;
			while (newPos < 0)
				newPos += H->TableSize;
		}
	}

	return newPos;	// 返回空位置或者元素所在位置
}

template<class T>
bool Insert(HashTable<T> H, T Key) {		// 由于Find函数的deficit，函数不会在Deleted处插入元素
	Pos p = Find(H, Key);

	if (H->Cells[p].Info != Legitimate) {	// 位置p中没有元素时,或者元素Key状态为Deleted
		H->Cells[p].Info = Legitimate;
		H->Cells[p].Data = Key;
		return true;
	}
	else {
		std::cout << "键值已存在" << std::endl;
		return false;			// Key已经存在于散列表中
	}
}


template<class T>
bool Delete(HashTable<T> H, T Key) {		// Deleted the Element in the HashTable with Info value Legitimate
	Pos p = Find(H, Key);

	if (H->Cells[p].Info == Legitimate) {
		H->Cells[p].Info = Deleted;
		return true;
	}
	else {
		std::cout << "键值不在哈希列表中" << std::endl;
		return false;
	}
}