#pragma once
#include <tuple>
#include <string>

template<typename T>
class Binder
{
	void bindVar(const std::string& Name, void* ValOffset);
	void bindFunc(const std::string& Name, void* FuncOffset);
	void bindStaticFunc(const std::string& Name, void* FuncOffset);
	void callFunc(void* Ptr, const std::string& Name, void* FuncOffset);
	void callStaticFunc(const std::string& Name, void* FuncOffset);
};

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, void* ValOffset)
{
}

template<typename T>
inline void Binder<T>::bindFunc(const std::string& Name, void* FuncOffset)
{
}

template<typename T>
inline void Binder<T>::bindStaticFunc(const std::string& Name, void* FuncOffset)
{
}

template<typename T>
inline void Binder<T>::callFunc(void* Ptr, const std::string& Name, void* FuncOffset)
{
}

template<typename T>
inline void Binder<T>::callStaticFunc(const std::string& Name, void* FuncOffset)
{
}
