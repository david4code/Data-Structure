#include"HashTable.h"


int main() {
	HashTable<string> H = createTable<string>(9);
	string tem;
	for (int i = 0; i < 9; i++) {
		std::cin >> tem;
		Insert(H, tem);
	}
	return 0;
}