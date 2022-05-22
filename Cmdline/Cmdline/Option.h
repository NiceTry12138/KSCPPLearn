#pragma once
#include <string>
#include <algorithm>
//template<typename T>
class Option_Base
{
public:
	Option_Base(char _ShortName, const std::string& _Name, bool _bIsNeed = true, const std::string& _Desc = "")
		: m_bIsNeed(_bIsNeed), m_ShortName(_ShortName), m_Desc(_Desc), m_Name(_Name) 
	{
		std::transform(m_Name.begin(), m_Name.end(), m_Name.begin(), ::tolower);
		m_ShortName = std::tolower(m_ShortName);
	}

	bool IsNeed() { return m_bIsNeed; }

	bool operator ==(const Option_Base& _other) {
		return _other.m_Name == this->m_Name || _other.m_ShortName == this->m_ShortName;
	}

	bool operator ==(const std::string& _other) {
		return this->m_Name == _other;
	}

	bool operator == (const char _other) {
		return this->m_ShortName == _other;
	}

private:
	bool m_bIsNeed;
	char m_ShortName;
	std::string m_Desc;
	std::string m_Name;
};

