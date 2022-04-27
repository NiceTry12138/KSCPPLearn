#include <iostream>
#include <vector>
#include "FStackArray.h"

using namespace std;
int main() {
	FStackArray<int, 5> arr;
	arr.pushBackElement(1);
	arr.pushBackElement(2);
	arr.pushBackElement(3);
	arr.pushBackElement(4);
	
	for (int i = 0; arr.getLength() > 0; ++i)
	{
		std::cout << arr.popBackElement() << std::endl;
	}

	return 0;
}