#pragma once
#include <vector>
#include <string>
#include "Vector3.h"

#define IS_1(v) (v == 1 ? 1 : -1)

struct NodeData {
	Vector3 _Position;
	std::string _Data;

	NodeData(Vector3 _Pos, std::string _D) {
		_Data = _D;
		_Position = _Pos;
	}
};

class OCTreeNode
{
public:
	OCTreeNode();
	~OCTreeNode();

	OCTreeNode(OCTreeNode* _Parent, Vector3 _Pos, Size _Size);

	OCTreeNode(Vector3 _Pos, Size _Size);

	void SetParent(OCTreeNode* _Parent);
	OCTreeNode* GetParent();

	OCTreeNode* GetRoot();
	bool IsPointInSection(Vector3 _Pos);

	int GetDepth();

	bool DeleteNode(OCTreeNode* _Node);

	void InsertData(std::string _NodeName, Vector3 _Position);

	void PrintData();
protected:
	void AddData(std::string _NodeName, Vector3 _Position);
	void SplitSelf();

private:
	int Depth;								// ���

	Vector3 CenterPos;						// ���ĵ�����
	Size Extend;							// �����С

	OCTreeNode* Root{ nullptr };			// ���ڵ�
	OCTreeNode* Parent{ nullptr };			// ���ڵ�
	std::vector<NodeData> DataList;			// �����б�
	std::vector<OCTreeNode*> Children;		// �ӽڵ�����
};