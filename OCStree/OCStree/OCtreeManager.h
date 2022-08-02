#pragma once
#include "OCTreeNode.h"

class OCtreeManager
{
public:
	OCtreeManager(Vector3 _CenterPos, Size _Content);
	~OCtreeManager();

	void AddData(std::string _Data, Vector3 _Position);
	void PrintAllData();

private:
	OCTreeNode* Root{ nullptr };
};

