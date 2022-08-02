#include "OCTreeNode.h"
#include <math.h>
#include <iostream>

const int MaxNodeDataListNumber = 1;
const int MaxNodeDepth = 10;

OCTreeNode::OCTreeNode()
{
	Root = nullptr;
	Parent = nullptr;
	DataList.clear();
}

OCTreeNode::~OCTreeNode()
{
	if (Parent)
	{
		Parent->DeleteNode(this);
	}
	Parent = nullptr;
	Root = nullptr;
	for (int i = 0; i < Children.size(); ++i) {
		delete Children[i];
	}
	Children.clear();
}

OCTreeNode::OCTreeNode(OCTreeNode* _Parent, Vector3 _Pos, Size _Size)
{
	Parent = _Parent;
	CenterPos = _Pos;
	Extend = _Size;
	Parent = _Parent;
	Root = _Parent->GetRoot();
	Depth = _Parent->GetDepth() + 1;
}

OCTreeNode::OCTreeNode(Vector3 _Pos, Size _Size)
{
	CenterPos = _Pos;
	Extend = _Size;
	Depth = 0;
	Root = this;
	Parent = this;
}

void OCTreeNode::SetParent(OCTreeNode* _Parent)
{
	Parent = _Parent;
	Root = _Parent->GetRoot();
}

OCTreeNode* OCTreeNode::GetParent()
{
	return Parent;
}

OCTreeNode* OCTreeNode::GetRoot()
{
	return Root;
}

bool OCTreeNode::IsPointInSection(Vector3 _Pos)
{
	bool val1 = CenterPos.X - Extend.X / 2 < _Pos.X;
	bool val2 = CenterPos.X + Extend.X / 2 > _Pos.X;
	bool val3 = CenterPos.Y - Extend.Y / 2 < _Pos.Y;
	bool val4 = CenterPos.Y + Extend.Y / 2 > _Pos.Y;
	bool val5 = CenterPos.Z - Extend.Z / 2 < _Pos.Z;
	bool val6 = CenterPos.Z + Extend.Z / 2 > _Pos.Z;
	return val1 && val2 && val3 && val4 && val5 && val6;
}

int OCTreeNode::GetDepth()
{
	return Depth;
}

bool OCTreeNode::DeleteNode(OCTreeNode* _Node)
{
	for (int i=0; i<Children.size(); ++i)
	{
		if (Children[i] == _Node)
		{
			Children[i] = nullptr;
			return true;
		}
	}
	return false;
}

void OCTreeNode::InsertData(std::string _NodeName, Vector3 _Position)
{
	for (int i = 0; i < Children.size(); ++i) {
		if (Children[i]->IsPointInSection(_Position))
		{
			Children[i]->InsertData(_NodeName, _Position);
			return;
		}
	}
	AddData(_NodeName, _Position);
}

void OCTreeNode::PrintData()
{
	std::string PrintStr;
	for (int i = 0; i < Depth; ++i) {
		PrintStr += "\t";
	}
	PrintStr += std::to_string(Depth) + "_" + CenterPos.to_string();
	PrintStr += " |";
	for (auto _Data : DataList)
	{
		PrintStr += _Data._Data + " " + _Data._Position.to_string();
		PrintStr += " ";
	}
	std::cout << PrintStr << std::endl;
	for (auto _Child : Children)
	{
		_Child->PrintData();
	}
}

void OCTreeNode::AddData(std::string _NodeName, Vector3 _Position)
{
	DataList.push_back(NodeData(_Position, _NodeName));
	// 深度和数据数量都超过限制 分割
	if (DataList.size() > MaxNodeDataListNumber && Depth < MaxNodeDepth)
	{
		SplitSelf();
	}
}

void OCTreeNode::SplitSelf()
{
	for (int i = 0; i < Children.size(); ++i) {
		delete Children[i];
		Children[i] = nullptr;
	}
	Children.clear();
	for (int x = 0; x < 2; ++x) 
	{
		for (int y = 0; y < 2; ++y)
		{
			for (int z = 0; z < 2; ++z)
			{
				Vector3 NewNodeCenterPos;
				NewNodeCenterPos.X = CenterPos.X + Extend.X / 4 * IS_1(x);
				NewNodeCenterPos.Y = CenterPos.Y + Extend.Y / 4 * IS_1(y);
				NewNodeCenterPos.Z = CenterPos.Z + Extend.Z / 4 * IS_1(z);
				Children.push_back(new OCTreeNode(this, NewNodeCenterPos, Extend / 2));
			}
		}
	}
	for (int i = 0; i < DataList.size(); ++i) {
		for (int j = 0; j < Children.size(); ++j) {
			if (Children[j]->IsPointInSection(DataList[i]._Position))
			{
				Children[j]->AddData(DataList[i]._Data, DataList[i]._Position);
			}
		}
	}
	DataList.clear();
}
