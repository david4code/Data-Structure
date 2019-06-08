#include"Heap.h"

int main() {
	MinHeap<int> H = createMinHeap<int>(30);
	int x;
	for (int i = 0; i < 6; i++) {
		std::cin >> x;
		insertMin(H, x);
	}
	deleteMin(H);
	//int mess[] = { INT_MIN,79,66,43,83,30,87,38,55,91,72,49,9 };
	//int size = sizeof(mess) / sizeof(*mess);
	//MinHeap<int> H = assignHeap<int>(mess, size);
	//buildMinHeap(H);
	return 0;
}