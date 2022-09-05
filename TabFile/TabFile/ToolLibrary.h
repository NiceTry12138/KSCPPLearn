#pragma once
#include <string>
#include <sstream>

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