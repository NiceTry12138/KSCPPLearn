#pragma once

#include <stack>
#include <string>
#include <assert.h>

struct StackItem
{
	void* valPtr{ nullptr };
	std::string typeStr;
};

class StackInfo
{
	std::stack<StackItem> m_stack;

public:

	template<typename T>
	void push(const T& val) {
		StackItem item;
		item.typeStr = typeid(T).name();
		T* ptr = new T();
		*ptr = val;
		item.valPtr = (void*)ptr;
		m_stack.push(item);
	}

	template<typename T>
	void pop(T& val) {
		StackItem item = m_stack.top();
		if (std::string(typeid(T).name()) != item.typeStr)
		{
			assert(false);
			return;
		}
		T* ptr = (T*)(item.valPtr);
		val = *ptr;
		delete item.valPtr;
		m_stack.pop();
	}
};
