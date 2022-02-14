#include <iostream>
#include "CustomArray.h"
#include "CustomList.h"

template<typename T>
void printCustomArray(CustomArray<T>& arr) {
	for (int i = 0; i < arr.size(); ++i) {
		std::cout << i << " ";
	}
	std::cout << endl;
}

template<typename Iteartor, typename T>
Iteartor my_find_if(Iteartor _begin, Iteartor _end, T _val)
{
	for (auto _it = _begin; _it != _end; ++_it)
	{
		if ((*_it) == _val)
		{
			return _it;
		}
	}
}

template<typename T>
void printCustomList(CustomList<T> &_list)
{
	for (auto val : _list) {
		std::cout << val << " ";
	}
	std::cout << std::endl;
}

int main() {
	//CustomArray<int> arr = {1, 2, 3, 4, 5};

	auto arr = CustomArray<int>({1, 2, 3, 4});
	arr.reserve(4);
	printCustomArray(arr);
	arr.push(1);
	printCustomArray(arr);
	arr.push(2);
	printCustomArray(arr);
	arr.insert(1, 3);
	printCustomArray(arr);
	std::cout << arr.remove(1) << std::endl;
	printCustomArray(arr);
	int index = arr.findIndex(1);
	std::cout << index << std::endl;
	std::cout << arr.pop() << std::endl;
	arr.clear();

	std::cout << "---------------------------------" << std::endl;

	auto list1 = new CustomList<int>();
	auto node1 = list1->push(1);
	printCustomList(*list1);
	auto node2 = list1->push(2);
	printCustomList(*list1);
	auto node3 = list1->insert(node2, 3);
	printCustomList(*list1);
	auto ret = list1->find(2);
	std::cout << ret << std::endl;
	list1->remove(node2); 
	printCustomList(*list1);
	list1->popAll();

	system("pause");
	return 0;
}