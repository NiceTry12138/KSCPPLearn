#include <iostream>
#include <string>
#include <vector>
#include "CustomString.h"
using namespace std;

void printBool(bool val) {
	if (val) {
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}
}

template<typename T>
void printArray(const T arr[], int len) {
	for (int i = 0; i < len; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
}

template<typename T>
void printVector(const std::vector<T> arr) {
	for (auto item : arr) {
		std::cout << item << " ";
	}
	std::cout << endl;
}

int main() {
	auto str1 = CustomString("qwertest1");
	auto str2 = CustomString("test2, test3");
	str1 = "qwertest3";
	int len = str1.len();
	CustomString sub1 = str1.sub(1, 2);
	str1.append("append");
	bool equal = str1 == str2;
	int index = str1.find("es");
	printBool(equal);
	std::cout << "str1 = " << str1 << std::endl;
	std::cout << "str2 = " << str2 << std::endl;
	std::cout << "sub1 = " << sub1 << std::endl;
	std::cout << "find es in str1 index : " << index << std::endl;
	printVector(str1.split("e"));

	system("pause");
	return 0;
}