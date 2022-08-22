#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <cstring>
#include <algorithm>
#include <cstdlib>

template<typename TargetType, typename SourceType, bool IsSame>
class Cast_Target {
public:
	static TargetType cast(const SourceType& Arg) {
		TargetType Res;
		std::stringstream ss;
		ss << Arg && ss >> Res;
		bool iseof = ss.eof();
		return Res;
	}
};

// 偏特化 输入 输出类型相同
template <typename Target, typename Source>
class Cast_Target<Target, Source, true> {
public:
	static Target cast(const Source& arg) {
		return arg;
	}
};

// 偏特化 输出成字符串
template <typename Source>
class Cast_Target<std::string, Source, false> {
public:
	static std::string cast(const Source& arg) {
		std::ostringstream ss;
		ss << arg;
		return ss.str();
	}
};

// 偏特化 输入是字符串
template <typename Target>
class Cast_Target<Target, std::string, false> {
public:
	static Target cast(const std::string& arg) {
		Target ret;
		std::istringstream ss(arg);
		ss >> ret;
		return ret;
	}
};

// SFINAE
template <typename T1, typename T2>
struct Is_same {
	static const bool value = false;
};

template <typename T>
struct Is_same<T, T> {
	static const bool value = true;
};

template<typename Target, typename Source>
Target lexical_cast(const Source& arg)
{
	return Cast_Target<Target, Source, Is_same<Target, Source>::value>::cast(arg);
}

class Option_Base {
public:
	virtual void Set(const std::string& Val) = 0;
	virtual bool HasSet() = 0;
	virtual bool IsNeed() = 0;

	virtual char GetShortName() = 0;
	virtual const std::string& GetFullName() = 0;
	virtual const std::string& GetDescription() = 0;
};

class Option_NonVal : public Option_Base
{
public:
	Option_NonVal(char _ShortName, const std::string& _Name, bool _bIsNeed = false, const std::string& _Desc = "")
		: m_bIsNeed(_bIsNeed), m_ShortName(_ShortName), m_Desc(_Desc), m_Name(_Name) 
	{
		std::transform(m_Name.begin(), m_Name.end(), m_Name.begin(), ::tolower);
		m_ShortName = std::tolower(m_ShortName);
	}
	virtual void Set(const std::string& Val) {}
	virtual bool HasSet() { return false; }
	virtual bool IsNeed() { return m_bIsNeed; }
	virtual char GetShortName() { return m_ShortName; }
	virtual const std::string& GetFullName() { return m_Name; }
	virtual const std::string& GetDescription() { return m_Desc; }

private:
	bool m_bIsNeed;
	char m_ShortName;
	std::string m_Desc;
	std::string m_Name;
};

template<typename T>
class Option_HasVal : public Option_Base {
public:
	Option_HasVal(char _ShortName, const std::string& _Name, const T& _Val, bool _bIsNeed = false, const std::string& _Desc = "")
		: m_bIsNeed(_bIsNeed), m_ShortName(_ShortName), m_Desc(_Desc), m_Name(_Name)
	{
		std::transform(m_Name.begin(), m_Name.end(), m_Name.begin(), ::tolower);
		m_ShortName = std::tolower(m_ShortName);
		m_Value = _Val;
	}

	virtual bool HasSet() { return m_bIsSet; }
	virtual bool IsNeed() { return m_bIsNeed; }
	virtual char GetShortName() { return m_ShortName; }
	virtual const std::string& GetFullName() { return m_Name; }
	virtual const std::string& GetDescription() { return m_Desc; }

	const T& Get() { return m_Value; }

	virtual void Set(const std::string& Val) {
		m_Value = lexical_cast<T>(Val);
	}

protected:


private:
	bool m_bIsNeed;
	char m_ShortName;
	std::string m_Desc;
	std::string m_Name;

	bool m_bIsSet{ false };
	T m_Value;
};