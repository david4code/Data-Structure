#include"HashTable.h"

int main() {
	HashTable<int> H = createTable<int>(10);
	int key;
	for (int i = 0; i < 9; i++) {
		std::cin >> key;
		Insert(H, key);
	}
	Delete(H, 9);
	Delete(H, 9);
	Insert(H, 9);
	return 0;
}