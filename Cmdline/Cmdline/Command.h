#pragma once
#include <map>
#include <functional>
#include "Option.h"

class Command
{
public:
	Command();
	void option(char _ShortName, const std::string& _Name, const std::string& _Desc, std::function<void()> _CallBackFunc);
	void parse(int argc, char** argv);
private:
	std::map<Option_Base, std::function<void()>> m_Options;
};

