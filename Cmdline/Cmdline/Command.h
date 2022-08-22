#pragma once
#include <map>
#include <set>
#include <iostream>
#include <functional>
#include "Option.h"

class Command
{
public:
	virtual ~Command();

	// 添加无属性值
	void add(const std::string& FullName, const char &ShortName, bool bIsMust = false, const std::string& Desc = "");

	// 添加有属性值
	template<typename T>
	void add(const std::string& FullName, const char& ShortName, const T& Val, bool bIsMust = false, const std::string& Desc = "");

	// 初始化
	void init(const std::string &CurrentVersion);
	
	// 解析输入
	void parse(int argc, char* argv[]);
	
	// 通过全名称获得值
	template<typename T>
	const T& get(const std::string& FullName);

	// 通过缩写获得值
	template<typename T>
	const T& get(const char& ShortName);

	// 用于输入属性判断
	bool isSet(const char& ShortName);
	bool isSet(const std::string& FullName);
protected:
	bool getParam(char* Argv, std::string& FullName, char & ShortName, std::string& Val);

	void insertInputSet(const std::string& FullName);
private:
	std::map<std::string, Option_Base*> Options;
	std::map<char, std::string> ShortToFullMap;

	std::set<char> AllInputShortName;
	std::set<std::string> AllInputFullName;
};

template<typename T>
inline void Command::add(const std::string& FullName, const char& ShortName, const T& Val, bool bIsMust, const std::string& Desc)
{
	if (Options.find(FullName) != Options.end())
	{
		std::cout << FullName << " Was Setted, Check It!" << std::endl;
		return;
	}
	auto opt = new Option_HasVal<T>(ShortName, FullName, Val, bIsMust, Desc);
	Options.insert(std::make_pair(FullName, opt));
	ShortToFullMap.insert(std::make_pair(ShortName, FullName));
}

template<typename T>
inline const T& Command::get(const std::string& FullName)
{
	auto It = Options.find(FullName);
	if (It == Options.end())
	{
		// TODO: 在此处插入 return 语句
		std::cout << "Error FullName For Get Value" << std::endl;
		return T();
	}
	auto Opt = (Option_HasVal<T>*)It->second;
	return  Opt->Get();
}

template<typename T>
inline const T& Command::get(const char& ShortName)
{
	auto It = ShortToFullMap.find(ShortName);
	if (It == ShortToFullMap.end())
	{
		// TODO: 在此处插入 return 语句
		std::cout << "Error FullName For Get Value" << std::endl;
		return T();
	}
	return get<T>(It->second);
}
