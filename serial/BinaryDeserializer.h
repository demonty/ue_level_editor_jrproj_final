#ifndef BINARY_DESERIALIZER_H
#define BINARY_DESERIALIZER_H

#include "Deserializer.h"
#include "serial_util.h"

class BinaryDeserializer : public Deserializer
{
private:
	_int8*		 m_buffer; //current data buffer
	int			 m_bufferSize; //size of the buffer
	int			 m_offset; //points to current reading position
	bool		 m_overflow; //whether a buffer over run has occured

public:
	BinaryDeserializer(_int8* buffer, int bufferSize);
	~BinaryDeserializer();

	//not used with binary
	void BeginAttribute(std::string& name){}
	//not used with binary
	void EndAttribute(){}

	//returns number of elements to expect
	//assuming WriteNumberOfElements() was used in serialization..
	int ReadNumberOfElements();

	void ReadParameter(std::string& name, std::string& value);
	void ReadParameter(std::string& name, D3DXVECTOR3& value);
	void ReadParameter(std::string& name, D3DXVECTOR2& value);
	void ReadParameter(std::string& name, D3DXMATRIX& value);
	void ReadParameter(std::string& name, int& value);
	void ReadParameter(std::string& name, int& value, std::string& readable);
	void ReadParameter(std::string& name, unsigned int& value);
	void ReadParameter(std::string& name, float& value);
	void ReadParameter(std::string& name, bool& value);
};

#endif