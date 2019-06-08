#include"Heap.h"
#include"HuffmanTree.h"

template<>
bool insertMin(MinHeap<HuffmanTree> H, HuffmanTree Element) {
	if (isFull(H)) {
		std::cout << "最小堆已满\n";
		return false;
	}

	else {
		int i = ++H->Size;				// 元素加1
		while (*H->Data[i / 2] > *Element) {			// 符合最小堆则退出循环，否则上滤
			H->Data[i] = H->Data[i / 2];
			i /= 2;
		}

		H->Data[i] = Element;						// Element放入合适位置
		return true;
	}
}

template<>
HuffmanTree deleteMin(MinHeap<HuffmanTree> H) {
	if (isEmpty(H)) {
		std::cout << "最小堆已空\n";
		return H->Data[0];
	}

	else {
		HuffmanTree ret = H->Data[1];
		HuffmanTree tem = H->Data[H->Size--];
		int parent = 1, child;
		for (; parent <= H->Size / 2; parent = child) {
			child = 2 * parent;
			if (child != H->Size && *H->Data[child] > *H->Data[child + 1])	// 过滤结点指向较小的子结点（如果有两个的话）
				child += 1;
			if (*tem <= *H->Data[child]) break;								// 符合最小堆
			else
				H->Data[parent] = H->Data[child];							// 下滤
		}

		H->Data[parent] = tem;
		return ret;
	}
}

template<>
void procDown(Heap<HuffmanTree> H, int parent) {
	int child;
	HuffmanTree cur = H->Data[parent];
	for (; parent <= H->Size / 2; parent = child) {
		child = 2 * parent;
		if (child != H->Size && *H->Data[child] > *H->Data[child + 1])
			child += 1;
		if (*cur <= *H->Data[child])break;
		else
			H->Data[parent] = H->Data[child];
	}

	H->Data[parent] = cur;
}

HuffmanTree huffman(Heap<HuffmanTree> H) {
	if (isEmpty(H))
		return 0;
	else {
		HuffmanTree left, right;
		int size = H->Size;
		for (int i = 0; i < size - 1; i++) {			// 作size - 1次合并，H->Size是个变量不能作为循环条件
			left = deleteMin(H);
			right = deleteMin(H);
			insertMin(H, new HuffmanNode(left->Weight + right->Weight, left, right));
		}
		return deleteMin(H);
	}
}

int main() {
	//MinHeap<int> H = createMinHeap<int>(30, INT_MIN);
	//int x;
	//for (int i = 0; i < 6; i++) {
	//	std::cin >> x;
	//	insertMin(H, x);
	//}
	//deleteMin(H);


	//int mess[] = { INT_MIN,79,66,43,83,30,87,38,55,91,72,49,9 };
	//int size = sizeof(mess) / sizeof(*mess);
	//MinHeap<int> H = assignHeap<int>(mess, size);
	//buildMinHeap(H);

	HuffmanNode* ha[6];
	ha[0] = new HuffmanNode(INT_MIN);
	for (int i = 1; i < 6; i++) {
		ha[i] = new HuffmanNode(6 - i);
	}
	MinHeap<HuffmanNode*> H = assignHeap<HuffmanNode*>(ha, 6);
	buildMinHeap(H);
	HuffmanTree HT = huffman(H);
	return 0;
}