#include "OCtreeManager.h"

OCtreeManager::OCtreeManager(Vector3 _CenterPos, Size _Content)
{
	Root = new OCTreeNode(_CenterPos, _Content);
}

OCtreeManager::~OCtreeManager()
{
	delete Root;
}

void OCtreeManager::AddData(std::string _Data, Vector3 _Position)
{
	Root->InsertData(_Data, _Position);
}

void OCtreeManager::PrintAllData()
{
	Root->PrintData();
}
