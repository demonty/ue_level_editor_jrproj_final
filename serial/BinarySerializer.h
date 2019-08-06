#ifndef BINARY_SERIALIZER_H
#define BINARY_SERIALIZER_H

#include "Serializer.h"
#include "serial_util.h"

//the actual serializer for binary
class BinarySerializer : public Serializer
{
protected:
	_int8* m_buffer;
	int    m_bufferSize;
	int    m_offset;
	bool   m_overflow;
public:
	BinarySerializer(_int8 *buffer, int bufferSize);
	virtual ~BinarySerializer();
	
	void BeginAttribute(std::string& name){}
	void EndAttribute(){}
	
	void WriteNumberOfElements(int elements);

	void WriteParameter(std::string& name, std::string& value);
	void WriteParameter(std::string& name, D3DXVECTOR3& value);
	void WriteParameter(std::string& name, D3DXVECTOR2& value);
	void WriteParameter(std::string& name, D3DXMATRIX& value);
	void WriteParameter(std::string& name, unsigned int& value);
	void WriteParameter(std::string& name, int& value, std::string& readable);
	void WriteParameter(std::string& name, int& value);
	void WriteParameter(std::string& name, float& value);
	void WriteParameter(std::string& name, bool& value);
};

#endif