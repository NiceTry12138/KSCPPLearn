#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

atomic<int> a{ 0 };
atomic<int> b{ 0 };

void valueSet() {
	int t = 1;
	a = t;
	b = 2;
}

void observer() {
	std::cout << "(" << a << ", " << b << ")" << std::endl;
}

int main() {
	std::thread t1(valueSet);
	std::thread t2(observer);

	t1.join();
	t2.join();

	std::cout << "final (" << a << ", " << b << ")" << std::endl;
	return 0;
}
//int main() {
//
//	return 0;
//}