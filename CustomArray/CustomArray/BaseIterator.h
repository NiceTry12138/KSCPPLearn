#pragma once

template<typename T>
class BaseIterator
{
public:
	virtual ~BaseIterator() = default;
	BaseIterator(bool reverse) : m_IsReverse(reverse) {};

	virtual void next() = 0;
	virtual void behind() = 0;
	virtual bool isDone() = 0;
	virtual void SetVal(const T& _val) = 0;

protected:
	bool ISReverse() { return m_IsReverse; }

private:
	bool m_IsReverse{ false };
};
