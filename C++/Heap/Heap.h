#pragma once
#include<iostream>
#include<climits>

template<class T>
class HeapNode {
public:
	T* Data;				// 数组指针指向堆数据
	int Size;				// 堆中元素个数
	int Capacity;			// 堆最大容量
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
	H->Data[0] = min;    // 设置哨兵
	return H;
}

//template<>
//MinHeap<int> createMinHeap<int>(int size) {
//	MinHeap<int> H = new HeapNode<int>(size);
//	H->Data = new int[size + 1];
//	H->Data[0] = INT_MIN;			// 最小值int最为哨兵
//	return H;
//}

template<typename T>
bool isFull(Heap<T> H) {
	return H->Size == H->Capacity;
}

template<class T>
bool insertMin(MinHeap<T> H, T Element) {	// 若堆已满返回false, 否则把Element插入最小堆H中
	if (isFull(H)) {
		std::cout << "最小堆已满\n";
		return false;
	}

	else {
		int i = ++H->Size;				// 元素加1
		while (H->Data[i / 2] > Element) {			// 符合最小堆则退出循环，否则上滤
			H->Data[i] = H->Data[i / 2];
			i /= 2;
		}

		H->Data[i] = Element;						// Element放入合适位置
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
		std::cout << "最小堆已空\n";
		return H->Data[0];
	}

	else {
		T ret = H->Data[1];
		T tem = H->Data[H->Size--];
		int parent = 1, child;
		for (; parent <= H->Size / 2; parent = child) {
			child = 2 * parent;
			if (child != H->Size && H->Data[child] > H->Data[child + 1])	// 过滤结点指向较小的子结点（如果有两个的话）
				child += 1;
			if (tem <= H->Data[child]) break;								// 符合最小堆
			else
				H->Data[parent] = H->Data[child];							// 下滤
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
Heap<T> assignHeap(T mess[], int size) {			// 把普通数组赋值给堆(需在0位置含有哨兵)
	Heap<T> H = new HeapNode<T>(size - 1);
	H->Data = mess;
	H->Size = size - 1;
	return H;
}
