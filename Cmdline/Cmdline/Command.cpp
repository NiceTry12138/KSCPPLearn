#include "Command.h"

Command::~Command()
{
	for (auto _Item : Options)
	{
		delete _Item.second;
	}
}

void Command::add(const std::string& FullName, const char& ShortName, bool bIsMust, const std::string& Desc)
{
	if (Options.find(FullName) != Options.end())
	{
		std::cout << FullName << " Was Setted, Check It!" << std::endl;
		return;
	}
	auto opt = new Option_NonVal(ShortName, FullName, bIsMust, Desc);
	Options.insert(std::make_pair(FullName, opt));
	ShortToFullMap.insert(std::make_pair(ShortName, FullName));
}

void Command::init(const std::string& CurrentVersion)
{
	add("help", '?');
	add<std::string>("version", 'v', CurrentVersion);
}

void Command::parse(int argc, char* argv[])
{
	if (argc <= 1)
	{
		std::cout << "param is not enough" << std::endl;
		return;
	}
	
	for (int i = 1; i < argc; ++i)
	{
		std::string FullName;
		char ShortName;
		std::string Val;
		bool bIsShort = getParam(argv[i], FullName, ShortName, Val);
		if (bIsShort && ShortToFullMap.find(ShortName) != ShortToFullMap.end())
		{
			FullName = ShortToFullMap[ShortName];
		}
		if (Options.find(FullName) == Options.end())
		{
			std::cout << argv[i] << " Error Input !" << std::endl;
			continue;
		}
		auto Opt = Options[FullName];
		if (Val.size() != 0)
		{
			Opt->Set(Val);
		}
		insertInputSet(FullName);
	}
}

bool Command::isSet(const char& ShortName)
{
	return (AllInputShortName.find(ShortName) != AllInputShortName.end());
}

bool Command::isSet(const std::string& FullName)
{
	return (AllInputFullName.find(FullName) != AllInputFullName.end());
}

bool Command::getParam(char* Argv, std::string& FullName, char& ShortName, std::string& Val)
{
	bool bIsShort = true;
	bool bIsError = false;
	bool hasEqual = true;
	int StartIndex = 0;
	int StrLen = strlen(Argv);
	if (strncmp(Argv, "--", 2) == 0)
	{
		bIsShort = false;
		StartIndex = 2;
	}
	else if (strncmp(Argv, "-", 1) == 0)
	{
		bIsShort = true;
		StartIndex = 1;
	}
	else {
		bIsError = true;
		ShortName = Argv[1];
	}

	int EqualCharIndex = StartIndex;
	std::string ParamName;
	while (EqualCharIndex < StrLen && Argv[EqualCharIndex] != '=') {
		ParamName.push_back(Argv[EqualCharIndex]);
		++EqualCharIndex;
	};

	if (ParamName.size() == 0)
	{
		bIsError = true;
	}

	++EqualCharIndex;	// Ìø¹ýµÈºÅ
	std::string SetValue;
	while (EqualCharIndex < StrLen)
	{
		SetValue.push_back(Argv[EqualCharIndex]);
		++EqualCharIndex;
	}

	if (SetValue.size() == 0)
	{
		hasEqual = false;
	}

	ShortName = ParamName[0];
	FullName = ParamName;
	Val = SetValue;

	if (bIsError)
	{
		std::cout << "error input" << std::endl;
	}
	return bIsShort;
}

void Command::insertInputSet(const std::string& FullName)
{
	AllInputFullName.insert(FullName);
	auto Opt = Options[FullName];
	AllInputShortName.insert(Opt->GetShortName());
}
