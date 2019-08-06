#include "BinarySerialSize.h"

BinarySerialSize::BinarySerialSize()
: m_length(0)
{
}

BinarySerialSize::~BinarySerialSize()
{
}

int BinarySerialSize::GetSize()
{
	return m_length;
}

void BinarySerialSize::WriteNumberOfElements(int elements)
{
	m_length += 4;
}

void BinarySerialSize::WriteParameter(std::string& name,  std::string& value)
{
	//four bytes for (int32)length, plus the string itself
	m_length += 4 + (int)value.length();
}

void BinarySerialSize::WriteParameter(std::string& name,  D3DXVECTOR3& value)
{
	//3 floats..
	m_length += 12;
}

void BinarySerialSize::WriteParameter(std::string& name,  D3DXVECTOR2& value)
{
	//2 floats..
	m_length += 8;
}

void BinarySerialSize::WriteParameter(std::string& name,  D3DXMATRIX& value)
{
	//64 bytes..
	m_length += 64;
}

void BinarySerialSize::WriteParameter(std::string& name,  unsigned int& value)
{
	m_length += 4;
}

void BinarySerialSize::WriteParameter(std::string& name,  int& value, std::string& readable)
{
	m_length += 4;
}

void BinarySerialSize::WriteParameter(std::string& name, int& value)
{
	m_length += 4;
}

void BinarySerialSize::WriteParameter(std::string& name, float& value)
{
	m_length += 4;
}

void BinarySerialSize::WriteParameter(std::string& name,  bool& value)
{
	//bool is one byte..
	m_length++;
}