#pragma once
#include "OCTreeLazeNode.h"

class OCTreeLaze
{
public:
	inline bool isPointInBox(Vec3 Point);

protected:


private:
	Vec3 m_Position;				// 坐标
	Vec3 m_BoxSize;					// 尺寸
	OCTreeLazeNode m_Node;			// 信息节点
	OCTreeLaze* m_ChildNodes[8];	// 子节点
};

