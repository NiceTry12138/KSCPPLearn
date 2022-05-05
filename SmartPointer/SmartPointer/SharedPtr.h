#pragma once
#include <set>
#include <iostream>
template<typename T>
class SharedPtr
{
public:
	explicit SharedPtr();
	explicit SharedPtr(T* ptr);
	SharedPtr(const SharedPtr& p);
	~SharedPtr();

	SharedPtr& operator =(const SharedPtr& other);	// 赋值，赋值时this被覆盖了，所以this的count要-1；other添加了新的引用，所以要+1
	T& operator*();									// 解引用
	T* operator->();								// 箭头运算符
	operator bool();								// 重载bool，用于 if(shared_ptr)
	T* get() const;									// 获得原始指针
	size_t use_count();								// 获得引用个数
	bool unique();									// 判断是否只有一个对象引用
	void swap(SharedPtr& p);						// 与其他智能指针交换
protected:
	void addCount();
	void delCount();

private:
	size_t* count{ nullptr };
	T* ptr{ nullptr };
};

template<typename T>
inline SharedPtr<T>::SharedPtr()
{
	count = new size_t(0);
	ptr = nullptr;
}

template<typename T>
inline SharedPtr<T>::SharedPtr(T* ptr)
{
	count = new size_t(1);
	this->ptr = ptr;
}

template<typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& p)
{
	count = p.count;
	addCount();
	this->ptr = p.ptr;
}

template<typename T>
inline SharedPtr<T>::~SharedPtr()
{
	delCount();
	std::cout << "delete ptr" << std::endl;
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
{
	if (other.ptr == this->ptr)
	{
		return;
	}
	if (ptr)
	{
		delCount();
	}

	this->ptr = other.ptr;
	this->count = other.count;
	addCount();
	return *this;
}

template<typename T>
inline T& SharedPtr<T>::operator*()
{
	// TODO: 在此处插入 return 语句
	return *ptr;
}

template<typename T>
inline T* SharedPtr<T>::operator->()
{
	return ptr;
}

template<typename T>
inline SharedPtr<T>::operator bool()
{
	return ptr == nullptr;
}

template<typename T>
inline T* SharedPtr<T>::get() const
{
	return ptr;
}

template<typename T>
inline size_t SharedPtr<T>::use_count()
{
	if (count == nullptr)
	{
		return 0;
	}
	return *count;
}

template<typename T>
inline bool SharedPtr<T>::unique()
{
	if (count == nullptr)
	{
		return false;
	}
	return (*count) == 1;
}

template<typename T>
inline void SharedPtr<T>::swap(SharedPtr& p)
{
	std::swap(*this, p);
}

template<typename T>
inline void SharedPtr<T>::addCount()
{
	++(*count);
}

template<typename T>
inline void SharedPtr<T>::delCount()
{
	--(*count);
	if (*count <= 0)
	{
		delete ptr;
		delete count;
		ptr = nullptr;
		count = nullptr;
	}
}
