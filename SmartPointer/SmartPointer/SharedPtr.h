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

	SharedPtr& operator =(const SharedPtr& other);	// ��ֵ����ֵʱthis�������ˣ�����this��countҪ-1��other������µ����ã�����Ҫ+1
	T& operator*();									// ������
	T* operator->();								// ��ͷ�����
	operator bool();								// ����bool������ if(shared_ptr)
	T* get() const;									// ���ԭʼָ��
	size_t use_count();								// ������ø���
	bool unique();									// �ж��Ƿ�ֻ��һ����������
	void swap(SharedPtr& p);						// ����������ָ�뽻��
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
	// TODO: �ڴ˴����� return ���
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
