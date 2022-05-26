#pragma once
#include <tuple>
#include <map>
#include <string>

#define offsetof(Field, FieldName) &Field::FieldName

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
	std::map<std::string, int T::*>			m_IntInfo;
	std::map<std::string, char T::*>		m_CharInfo;
	std::map<std::string, bool T::*>		m_BoolInfo;
	std::map<std::string, float T::*>		m_FloatInfo;
	std::map<std::string, double T::*>		m_DoubelInfo;
	std::map<std::string, std::string T::*>	m_StringInfo;
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
