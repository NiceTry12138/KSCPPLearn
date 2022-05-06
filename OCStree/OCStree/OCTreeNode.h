#pragma once

#include <map>
#include <tuple>
#include <vector>
#include <iostream>
using namespace std;

#define __SG(n, m) std::get<n>(m)

enum class OCTreeNodeDirection {
	FRONT_LEFT_BOTTOM,				// 前、左、下
	FRONT_LEFT_TOP,					// 前、左、上
	FRONT_RIGHT_BOTTOM,				// 前、右、下
	FRONT_RIGHT_TOP,				// 前、右、上
	REAR_LEFT_BOTTOM,				// 后、左、下
	REAR_LEFT_TOP,					// 后、左、上
	REAR_RIGHT_BOTTOM,				// 后、右、下
	REAR_RIGHT_TOP					// 后、右、上
};

struct OCTreeNode {
	int _Data{ 0 };

	int _XMax, _XMin;
	int _YMax, _YMin;
	int _ZMax, _ZMin;

	std::map<OCTreeNodeDirection, OCTreeNode*> _Nodes;

	static const std::vector<OCTreeNodeDirection> Directions() {
		return
		{
			OCTreeNodeDirection::FRONT_LEFT_BOTTOM,
			OCTreeNodeDirection::FRONT_LEFT_TOP,
			OCTreeNodeDirection::FRONT_RIGHT_BOTTOM,
			OCTreeNodeDirection::FRONT_RIGHT_TOP,
			OCTreeNodeDirection::REAR_LEFT_BOTTOM,
			OCTreeNodeDirection::REAR_LEFT_TOP,
			OCTreeNodeDirection::REAR_RIGHT_BOTTOM,
			OCTreeNodeDirection::REAR_RIGHT_TOP
		};
	}

	static std::tuple<int, int, int, int, int, int> GetBox(OCTreeNodeDirection Direction, OCTreeNode* Node) {
		return GetBox(Direction, Node->_XMin, Node->_XMax, Node->_YMin, Node->_YMax, Node->_ZMin, Node->_ZMax);
	}

	static std::tuple<int, int, int, int, int, int> GetBox(OCTreeNodeDirection Direction, int XMin, int XMax, int YMin, int YMax, int ZMin, int ZMax) {
		std::tuple<int, int, int, int, int, int> result{ 0, 0, 0, 0, 0, 0 };
		switch (Direction)
		{
		case OCTreeNodeDirection::FRONT_LEFT_BOTTOM:
			result = std::make_tuple(XMax, (XMax + XMin) / 2, (YMax + YMin) / 2, YMin, (ZMin + ZMax) / 2, ZMin);
			break;
		case OCTreeNodeDirection::FRONT_LEFT_TOP:
			result = std::make_tuple(XMax, (XMax + XMin) / 2, (YMax + YMin) / 2, YMin, ZMax, (ZMin + ZMax) / 2);
			break;
		case OCTreeNodeDirection::FRONT_RIGHT_BOTTOM:
			result = std::make_tuple(XMax, (XMax + XMin) / 2, YMax, (YMax + YMin) / 2, (ZMin + ZMax) / 2, ZMin);
			break;
		case OCTreeNodeDirection::FRONT_RIGHT_TOP:
			result = std::make_tuple(XMax, (XMax + XMin) / 2, YMax, (YMax + YMin) / 2, ZMax, (ZMin + ZMax) / 2);
			break;
		case OCTreeNodeDirection::REAR_LEFT_BOTTOM:
			result = std::make_tuple((XMax + XMin) / 2, XMin, (YMax + YMin) / 2, YMin, (ZMin + ZMax) / 2, ZMin);
			break;
		case OCTreeNodeDirection::REAR_LEFT_TOP:
			result = std::make_tuple((XMax + XMin) / 2, XMin, (YMax + YMin) / 2, YMin, ZMax, (ZMin + ZMax) / 2);
			break;
		case OCTreeNodeDirection::REAR_RIGHT_BOTTOM:
			result = std::make_tuple((XMax + XMin) / 2, XMin, YMax, (YMax + YMin) / 2, (ZMin + ZMax) / 2, ZMin);
			break;
		case OCTreeNodeDirection::REAR_RIGHT_TOP:
			result = std::make_tuple((XMax + XMin) / 2, XMin, YMax, (YMax + YMin) / 2, ZMax, (ZMin + ZMax) / 2);
			break;
		}
		return result;
	}

	static OCTreeNodeDirection GetDirection(int XMin, int XMax, int YMin, int YMax, int ZMin, int ZMax, int PosX, int PosY, int PosZ) {
		bool isFront = true, isRight = true, isTop = true;

		if (PosX >= XMin && PosX < (XMin + XMax) / 2)
		{
			isFront = false;
		}

		if (PosY >= YMin && PosY < (YMin + YMax) / 2)
		{
			isRight = false;
		}

		if (PosZ >= ZMin && PosZ < (ZMin + ZMax) / 2)
		{
			isTop = false;
		}


	}

	OCTreeNode(int XMax, int Xmin, int YMax, int YMin, int ZMax, int ZMin) {
		_Nodes[OCTreeNodeDirection::FRONT_LEFT_BOTTOM] = nullptr;
		_Nodes[OCTreeNodeDirection::FRONT_LEFT_TOP] = nullptr;
		_Nodes[OCTreeNodeDirection::FRONT_RIGHT_BOTTOM] = nullptr;
		_Nodes[OCTreeNodeDirection::FRONT_RIGHT_TOP] = nullptr;
		_Nodes[OCTreeNodeDirection::REAR_LEFT_BOTTOM] = nullptr;
		_Nodes[OCTreeNodeDirection::REAR_LEFT_TOP] = nullptr;
		_Nodes[OCTreeNodeDirection::REAR_RIGHT_BOTTOM] = nullptr;
		_Nodes[OCTreeNodeDirection::REAR_RIGHT_TOP] = nullptr;

		_XMax = XMax; _XMin = Xmin; _YMax = YMax; _YMin = YMin;  _ZMax = ZMax; _ZMin = ZMin;
	}

	OCTreeNode(std::tuple<int, int, int, int, int, int> InitData) :
		OCTreeNode(__SG(0, InitData), __SG(1, InitData), __SG(2, InitData), __SG(3, InitData), __SG(4, InitData), __SG(5, InitData))
	{
	}

	void SetOCTreeNodeDirection(OCTreeNode* _node, OCTreeNodeDirection _direction) {
		_Nodes[_direction] = _node;
	}

	OCTreeNode* GetOCTreeNodeByDirection(OCTreeNodeDirection _direction) {
		return _Nodes[_direction];
	}

	bool IsPointInBox(int _posX, int _posY, int _posZ) {
		return _posX >= _XMin && _posX <= _XMax &&
			_posY >= _YMin && _posY <= _YMax &&
			_posZ >= _YMin && _posZ <= _ZMax;
	}

	bool HasChild() {
		for (auto it = _Nodes.begin(); it != _Nodes.end(); ++it)
		{
			if (it->second != nullptr) {
				return true;
			}
		}
		return false;
	}
};