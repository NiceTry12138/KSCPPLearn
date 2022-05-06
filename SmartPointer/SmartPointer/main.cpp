#include <iostream>
#include "SharedPtr.h"
#include "UniquePtr.h"
using namespace std;

int main() {

	int* temp = new int(100);
	SharedPtr<int> ptr1 = SharedPtr<int>(temp);
	std::cout << "shared ptr val = " << *ptr1 << " count = " << ptr1.use_count() << std::endl;
	SharedPtr<int> ptr2(ptr1);
	std::cout << "shared ptr val = " << *ptr1 << " count = " << ptr2.use_count() << std::endl;

	int* temp1 = new int(5);
	UniquePtr<int> ptr3 = UniquePtr<int>(temp1);
	std::cout << "unique ptr val = " << *ptr3 << std::endl;
	UniquePtr<int> ptr4 = std::move(ptr3);
	std::cout << "unique ptr val = " << *ptr4 << std::endl;
	UniquePtr<int> ptr5(std::move(ptr4));
	std::cout << "unique ptr val = " << *ptr5 << std::endl;

	return 0;
}