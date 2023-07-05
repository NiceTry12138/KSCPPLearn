#pragma once
#include <tuple>
#include <map>
#include <string>

#define offsetof_binder(Field, FieldName) &Field::FieldName

#define FindVale(TheMap, Key, Obj) 		\
if (m_IntInfo.find(FieldName) != m_IntInfo.end())\
{\
	return (*Obj).*(m_IntInfo[FieldName]);\
}

template<typename T>
class Binder
{
public:
	void bindVar(const std::string& Name, int T::* ValOffset);
	void bindVar(const std::string& Name, bool T::* ValOffset);
	void bindVar(const std::string& Name, char T::* ValOffset);
	void bindVar(const std::string& Name, float T::* ValOffset);
	void bindVar(const std::string& Name, double T::* ValOffset);
	void bindVar(const std::string& Name, std::string T::* ValOffset);

	void bindFunc(const std::string& Name, void (T::* foo)(void *)) {
		m_VoidVoidFunc.insert(std::make_pair(Name, foo));
	}

	void callFunc(T* Obj, const std::string& FieldName, void* param) {
		if (m_VoidVoidFunc.find(FieldName) != m_VoidVoidFunc.end())
		{
			auto foo =m_VoidVoidFunc[FieldName];
			((*Obj).*foo)(param);
		}
	}

	void bindStaticFunc(const std::string& Name, void (*funcptr)(void*)) {
		m_StaticVoidVoidFunc.insert(std::make_pair(Name, funcptr));
	}

	void callStaticFunc(const std::string& FieldName, void* param) {
		if (m_StaticVoidVoidFunc.find(FieldName) != m_StaticVoidVoidFunc.end())
		{
			auto funcptr = m_StaticVoidVoidFunc[FieldName];
			funcptr(param);
		}
	}

	template<typename TargetType>
	TargetType findVar(T* Obj, std::string FieldName) {
		FindVale(m_IntInfo, FieldName, Obj);
		FindVale(m_CharInfo, FieldName, Obj);
		FindVale(m_BoolInfo, FieldName, Obj);
		FindVale(m_FloatInfo, FieldName, Obj);
		FindVale(m_DoubelInfo, FieldName, Obj);
		FindVale(m_StringInfo, FieldName, Obj);
		return TargetType();
	}

private:
	std::map<std::string, int T::*>				m_IntInfo;
	std::map<std::string, char T::*>			m_CharInfo;
	std::map<std::string, bool T::*>			m_BoolInfo;
	std::map<std::string, float T::*>			m_FloatInfo;
	std::map<std::string, double T::*>			m_DoubelInfo;
	std::map<std::string, std::string T::*>		m_StringInfo;

	std::map<std::string, void (T::*)(void*)>	m_VoidVoidFunc;
	std::map<std::string, void (*)(void*)>		m_StaticVoidVoidFunc;
};

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, int T::* ValOffset)
{
	m_IntInfo.insert(std::make_pair(Name, ValOffset));
}

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, bool T::* ValOffset)
{
	m_BoolInfo.insert(std::make_pair(Name, ValOffset));
}

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, float T::* ValOffset)
{
	m_FloatInfo.insert(std::make_pair(Name, ValOffset));
}

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, double T::* ValOffset)
{
	m_DoubelInfo.insert(std::make_pair(Name, ValOffset));
}

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, std::string T::* ValOffset)
{
	m_StringInfo.insert(std::make_pair(Name, ValOffset));
}

template<typename T>
inline void Binder<T>::bindVar(const std::string& Name, char T::* ValOffset)
{
	m_CharInfo.insert(std::make_pair(Name, ValOffset));
}
