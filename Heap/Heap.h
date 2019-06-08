#pragma once
#include<iostream>
#include<climits>

template<class T>
class HeapNode {
public:
	T* Data;				// ����ָ��ָ�������
	int Size;				// ����Ԫ�ظ���
	int Capacity;			// ���������
	HeapNode(int size = 20);
};

template<class T>
inline HeapNode<T>::HeapNode(int size)
{
	Data = 0;					// Not allocate storage for now
	Capacity = size;
	Size = 0;
}


template<class T>
using Heap = HeapNode<T>*;

template<class T>
using MinHeap = HeapNode<T>*;

template<class T>
using MaxHeap = HeapNode<T>*;

template<class T>
MinHeap<T> createMinHeap(int size, T min) {
	MinHeap<T> H = new HeapNode<T>(size);
	H->Data = new T[size + 1];
	H->Data[0] = min;    // �����ڱ�
	return H;
}

//template<>
//MinHeap<int> createMinHeap<int>(int size) {
//	MinHeap<int> H = new HeapNode<int>(size);
//	H->Data = new int[size + 1];
//	H->Data[0] = INT_MIN;			// ��Сֵint��Ϊ�ڱ�
//	return H;
//}

template<typename T>
bool isFull(Heap<T> H) {
	return H->Size == H->Capacity;
}

template<class T>
bool insertMin(MinHeap<T> H, T Element) {	// ������������false, �����Element������С��H��
	if (isFull(H)) {
		std::cout << "��С������\n";
		return false;
	}

	else {
		int i = ++H->Size;				// Ԫ�ؼ�1
		while (H->Data[i / 2] > Element) {			// ������С�����˳�ѭ������������
			H->Data[i] = H->Data[i / 2];
			i /= 2;
		}

		H->Data[i] = Element;						// Element�������λ��
		return true;
	}
}



template<class T>
bool isEmpty(Heap<T> H) {
	return H->Size == 0;
}

template<class T>
T deleteMin(MinHeap<T> H) {
	if (isEmpty(H)) {
		std::cout << "��С���ѿ�\n";
		return H->Data[0];
	}

	else {
		T ret = H->Data[1];
		T tem = H->Data[H->Size--];
		int parent = 1, child;
		for (; parent <= H->Size / 2; parent = child) {
			child = 2 * parent;
			if (child != H->Size && H->Data[child] > H->Data[child + 1])	// ���˽��ָ���С���ӽ�㣨����������Ļ���
				child += 1;
			if (tem <= H->Data[child]) break;								// ������С��
			else
				H->Data[parent] = H->Data[child];							// ����
		}

		H->Data[parent] = tem;
		return ret;
	}
}



template<class T>
void procDown(Heap<T> H, int parent) {
	int child;
	T cur = H->Data[parent];
	for (; parent <= H->Size / 2; parent = child) {
		child = 2 * parent;
		if (child != H->Size && H->Data[child] > H->Data[child + 1])
			child += 1;
		if (cur <= H->Data[child])break;
		else
			H->Data[parent] = H->Data[child];
	}

	H->Data[parent] = cur;
}



template<class T>
void buildMinHeap(Heap<T> H) {
	for (int i = H->Size / 2; i > 0; i--)
		procDown<T>(H, i);
}

template<class T>
Heap<T> assignHeap(T mess[], int size) {			// ����ͨ���鸳ֵ����(����0λ�ú����ڱ�)
	Heap<T> H = new HeapNode<T>(size - 1);
	H->Data = mess;
	H->Size = size - 1;
	return H;
}
