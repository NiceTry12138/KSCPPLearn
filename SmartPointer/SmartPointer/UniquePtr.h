#pragma once
#include <iostream>
template<typename T>
class UniquePtr
{
public:
	UniquePtr();
	UniquePtr(T* p);
	UniquePtr(UniquePtr&& other);
	~UniquePtr();

	UniquePtr(UniquePtr& other) = delete;
	UniquePtr& operator =(UniquePtr& other) = delete;

	T& operator*();									// 解引用
	T* operator->();								// 箭头运算符
	operator bool();								// 重载bool，用于 if(shared_ptr)
	UniquePtr& operator =(UniquePtr&& other);		// 等于move
	T* get() const;									// 获得原始指针
	T* release();									// 释放当前指针
	void reset(T* p);								// 替换为其他指针
protected:

private:
	T* ptr = { nullptr };
};

template<typename T>
inline UniquePtr<T>::UniquePtr()
{
}

template<typename T>
inline UniquePtr<T>::UniquePtr(T* p)
{
	this->ptr = p;
}

template<typename T>
inline UniquePtr<T>::UniquePtr(UniquePtr&& other)
{
	this->ptr = other.ptr;
	other.ptr = nullptr;
}

template<typename T>
inline UniquePtr<T>::~UniquePtr()
{
	delete ptr;
	ptr = nullptr;
	std::cout << "UniquePtr delete" << std::endl;
}

template<typename T>
inline T& UniquePtr<T>::operator*()
{
	return *ptr;
}

template<typename T>
inline T* UniquePtr<T>::operator->()
{
	return ptr;
}

template<typename T>
inline UniquePtr<T>::operator bool()
{
	return ptr == nullptr;
}

template<typename T>
inline UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other)
{
	this->ptr = other.ptr;
	other.ptr = nullptr;
	return *this;
}

template<typename T>
inline T* UniquePtr<T>::get() const
{
	return this->ptr;
}

template<typename T>
inline T* UniquePtr<T>::release()
{
	auto temp = this->ptr;
	this->ptr = nullptr;
	return temp;
}

template<typename T>
inline void UniquePtr<T>::reset(T* p)
{
	this->ptr = p;
}