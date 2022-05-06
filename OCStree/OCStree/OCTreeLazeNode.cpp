#include "OCTreeLazeNode.h"

const Vec3& OCTreeLazeNode::GetPosition()
{
    // TODO: 在此处插入 return 语句
    return m_Position;
}

inline bool OCTreeLazeNode::equal(const OCTreeLazeNode& other)
{
    return m_Position == other.m_Position;
}

OCTreeLazeNode::OCTreeLazeNode(Vec3 Position)
{
    m_Position = Position;
}
