#include <iostream>
#include "SkipList.h"

int main() {
	SkipList list;
	for (int i = 0; i < 100; i++) {
		list.insertNode(i, i);
	}

	//list.PrintOneByOne();

	list.findDataByKey(78);
	list.findDataByKey(37);
	list.findDataByKey(52);
	list.findDataByKey(6);
	list.findDataByKey(99);

	return 0;
}