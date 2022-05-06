#include <iostream>
#include "OCTree.h"
using namespace std;

int main() {

	auto tree = OCTree(5, 200, 200, 200);

	auto node = tree.GetOCTreeNode(100, 100, 100);

	std::cout << node->_XMin << " " << node->_XMax;

	return 0;
}