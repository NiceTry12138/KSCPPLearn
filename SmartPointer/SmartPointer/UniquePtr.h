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

	T& operator*();									// ������
	T* operator->();								// ��ͷ�����
	operator bool();								// ����bool������ if(shared_ptr)
	UniquePtr& operator =(UniquePtr&& other);		// ����move
	T* get() const;									// ���ԭʼָ��
	T* release();									// �ͷŵ�ǰָ��
	void reset(T* p);								// �滻Ϊ����ָ��
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