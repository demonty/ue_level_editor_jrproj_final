#include "BinarySerializer.h"

BinarySerializer::BinarySerializer(_int8 *buffer, int bufferSize)
: m_buffer(buffer), m_bufferSize(bufferSize), m_offset(0), m_overflow(false)
{
}

BinarySerializer::~BinarySerializer()
{
}

void BinarySerializer::WriteNumberOfElements(int elements)
{

	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&elements);
    std::copy(src, src+4, m_buffer+m_offset);
    m_offset += 4;
}

void BinarySerializer::WriteParameter(std::string& name,  std::string& value)
{
	int length;
	length = (int)value.length();

	WriteNumberOfElements(length);

	if(m_overflow || m_offset + length > m_bufferSize)
	{
		m_overflow = true;
		return;
	}


	memcpy((void*)(m_buffer + m_offset), value.c_str(), length);
	
	m_offset += length;
}

void BinarySerializer::WriteParameter(std::string& name,  D3DXVECTOR3& value)
{
	if(m_overflow || m_offset + 12 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+sizeof(value), m_buffer+m_offset);
    m_offset += 12;
}

void BinarySerializer::WriteParameter(std::string& name,  D3DXVECTOR2& value)
{
	if(m_overflow || m_offset + 8 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+sizeof(value), m_buffer+m_offset);
    m_offset += 8;
}

void BinarySerializer::WriteParameter(std::string& name,  D3DXMATRIX& value)
{
	if(m_overflow || m_offset + 64 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+64, m_buffer+m_offset);
    m_offset += 64;
}

void BinarySerializer::WriteParameter(std::string& name,  unsigned int& value)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+4, m_buffer+m_offset);
    m_offset += 4;
}

void BinarySerializer::WriteParameter(std::string& name,  int& value, std::string& readable)
{ //this method is more for xml than binary
	//its purpose is to have a word in the
	//xml-file for the enum, instead of just
	//a worthless unidentified int.. so i'll
	//just pass it to the normal one to not
	//repeat code
	WriteParameter(name, value);
}

void BinarySerializer::WriteParameter(std::string& name, int& value)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+sizeof(value), m_buffer+m_offset);
    m_offset += 4;
}

void BinarySerializer::WriteParameter(std::string& name, float& value)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+4, m_buffer+m_offset);
    m_offset += 4;
}

void BinarySerializer::WriteParameter(std::string& name,  bool& value)
{

	if(m_overflow || m_offset + 1 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(src, src+1, m_buffer+m_offset);
    m_offset += 1;
}