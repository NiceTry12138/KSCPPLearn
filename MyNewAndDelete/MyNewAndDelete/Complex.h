#pragma once
class Complex
{
public:
	Complex();
	Complex(int _id);

	int getID();
	void setID(int _id);

	~Complex();

private:
	int m_id;
};

