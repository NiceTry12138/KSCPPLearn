#include <iostream>
#include "Complex.h"

template<typename T>
T* myNew() {
	auto temp = static_cast<T*>(malloc(sizeof(T)));
	new(temp)T();
	return temp;
}

template<typename T>
void myDelete(T* ptr) {
	ptr->~T();
	free(ptr);
	ptr = nullptr;
}

int main() {
	auto temp = myNew<Complex>();
	temp->setID(10);
	std::cout << temp->getID() << std::endl;
	myDelete<Complex>(temp);
	return 0;
}