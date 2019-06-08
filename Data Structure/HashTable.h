#pragma once
#include<iostream>
#include<cmath>
using EntryType = enum { Empty, Legitimate, Deleted };
constexpr auto MAXTABLESIZE = 100000;
using Pos = int;				// ɢ������


static int nextPrime(int init) {	// ���ش���init�Ҳ�����MAXTABLESIZE������
	int i, p = (init % 2) ? init + 2 : init + 1;

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p%i))break;
		if (i == 2)break;				// pΪ����
		else							// ����Ѱ������
			p += 2;
	}
	return p;
}

template<class T>
class Cell {				// ɢ�б�ԪԪ��
public:
	T Data;					// ��ֵ
	EntryType Info;			// Ԫ��״̬
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
	int size = nextPrime(TableSize);		// ȷ��ɢ�б���

	H->TableSize = size;
	H->Cells = new Cell<T>[H->TableSize];

	for (int i = 0; i < H->TableSize; i++)	// д��ɢ�б��ʼ����
		H->Cells[i].Info = Empty;

	return H;
}

template<class T>
int Hash(T key, int size) {			// ȷ��ɢ��ֵ
	return key % size;
}

template<class T>
Pos Find(HashTable<T> H, T Key) {
	Pos curPos, newPos;
	curPos = newPos = Hash(Key, H->TableSize);
	int cNum = 0;				// ��ͻ����

	while (H->Cells[newPos].Info != Empty &&	// ��ǰλ��״̬��ΪEmpty���Ҹ�λ��Ԫ�ز���Ҫ�ҵ�Ԫ��ʱ������ͻ
		H->Cells[newPos].Data != Key) {		// ƽ��̽�ⷨ
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

	return newPos;	// ���ؿ�λ�û���Ԫ������λ��
}

template<class T>
bool Insert(HashTable<T> H, T Key) {		// ����Find������deficit������������Deleted������Ԫ��
	Pos p = Find(H, Key);

	if (H->Cells[p].Info != Legitimate) {	// λ��p��û��Ԫ��ʱ,����Ԫ��Key״̬ΪDeleted
		H->Cells[p].Info = Legitimate;
		H->Cells[p].Data = Key;
		return true;
	}
	else {
		std::cout << "��ֵ�Ѵ���" << std::endl;
		return false;			// Key�Ѿ�������ɢ�б���
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
		std::cout << "��ֵ���ڹ�ϣ�б���" << std::endl;
		return false;
	}
}