#include "BinaryDeserializer.h"

BinaryDeserializer::BinaryDeserializer(_int8 *buffer, int bufferSize)
: m_buffer(buffer), m_bufferSize(bufferSize), m_offset(0), m_overflow(false)
{
}

BinaryDeserializer::~BinaryDeserializer()
{
}

int BinaryDeserializer::ReadNumberOfElements()
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return 0;
	}

	int value;

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+4, src);
    m_offset += 4;

	return value;
}

void BinaryDeserializer::ReadParameter(std::string& name, std::string& value)
{
	int length;
	length = ReadNumberOfElements();

	if(m_overflow || m_offset + length > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	if(length > 0)
	{
		value.resize(length);
		memcpy((void*)value.data(), (void*)(m_buffer + m_offset), length);
	}

	m_offset += length;
}

void BinaryDeserializer::ReadParameter(std::string& name, D3DXVECTOR3& value)
{
	if(m_overflow || m_offset + 12 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+12, src);
    m_offset += 12;
}

void BinaryDeserializer::ReadParameter(std::string& name, D3DXVECTOR2& value)
{
	if(m_overflow || m_offset + 8 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+sizeof(value), src);
    m_offset += 8;
}

void BinaryDeserializer::ReadParameter(std::string& name, D3DXMATRIX& value)
{
	if(m_overflow || m_offset + 64 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+sizeof(value), src);
    m_offset += 64;
}

void BinaryDeserializer::ReadParameter(std::string& name, unsigned int& value)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+sizeof(value), src);
    m_offset += 4;
}

void BinaryDeserializer::ReadParameter(std::string& name, int& value, std::string& readable)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+sizeof(value), src);
    m_offset += 4;
}

void BinaryDeserializer::ReadParameter(std::string& name, int& value)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, m_buffer+m_offset+sizeof(value), src);
    m_offset += 4;
}

void BinaryDeserializer::ReadParameter(std::string& name, float& value)
{
	if(m_overflow || m_offset + 4 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, (m_buffer+m_offset)+sizeof(value), src);
    m_offset += 4;
}

void BinaryDeserializer::ReadParameter(std::string& name, bool& value)
{
	if(m_overflow || m_offset + 1 > m_bufferSize)
	{
		m_overflow = true;
		return;
	}

	////if it's zero -> false, anything else -> true
	//value = m_buffer[m_offset] == 0 ? false : true;
	//
	//m_offset++;

	_int8* src = reinterpret_cast<_int8*>(&value);
    std::copy(m_buffer+m_offset, (m_buffer+m_offset)+sizeof(value), src);
    m_offset += 1;
}