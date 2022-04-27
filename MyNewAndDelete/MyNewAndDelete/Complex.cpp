#include "Complex.h"
#include <iostream>

Complex::Complex()
{
	m_id = 0;
	std::cout << "Complex " << this << " default constructor" << std::endl;
}

Complex::Complex(int _id)
{
	m_id = _id;
	std::cout << "Complex " << this << " constructor " << m_id << std::endl;
}

int Complex::getID()
{
	return m_id;
}

void Complex::setID(int _id)
{
	m_id = _id;
}

Complex::~Complex()
{
	std::cout << "Complex " << this << " D constructor " << m_id << std::endl;
}
