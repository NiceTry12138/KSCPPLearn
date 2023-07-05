#pragma once
#include <tuple>
#include <map>
#include <string>

class Binder1
{
public:
	inline void bindVar(const std::string& Name, int ValOffset) {
		m_OffsetInfo.insert(std::make_pair(Name, ValOffset));
	}

	template<typename T, typename TargetType>
	TargetType findVar(T* Obj, std::string FieldName) {
		auto it = m_OffsetInfo.find(FieldName);

		if (it == m_OffsetInfo.end())
		{
			return TargetType();
		}

		int offset = it->second;
		TargetType* valPtr = (TargetType*)((char*)Obj + offset);	// 注意指针+的跨度是一个元素的长度，所以这里先将this转char*，+offset即是 + offset个字节
		return *valPtr;
	}

private:
	std::map<std::string, int> m_OffsetInfo;
};
