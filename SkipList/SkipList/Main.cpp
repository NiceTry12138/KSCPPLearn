#include <iostream>
#include "SkipList.h"

int main() {
	SkipList list;
	for (int i = 0; i < 100; i++) {
		list.insertNode(i, i);
		std::cout << std::endl;
	}

	std::cout << "---------------------------" << std::endl;
	//list.PrintOneByOne();

	int data = 0;
	list.findDataByKey(78,data);
	list.findDataByKey(37,data);
	list.findDataByKey(52,data);
	list.findDataByKey(6,data);
	list.findDataByKey(99,data);


	for (int i = 0; i < 52; i += 2) {
		list.deleteByKey(i);
	}
	list.findDataByKey(52, data);



	return 0;
}