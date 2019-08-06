#ifndef BINARY_SERIAL_SIZE_H
#define BINARY_SERIAL_SIZE_H

#include "Serializer.h"
#include "serial_util.h"

//this class is meant to count the amount of memory
//needed for buffer allocation
class BinarySerialSize : public Serializer
{
private:
	int m_length;
public:
	BinarySerialSize();
	virtual ~BinarySerialSize();
	
	void BeginAttribute(std::string& name){}
	void EndAttribute(){}
	
	void WriteNumberOfElements(int elements);

	void WriteParameter(std::string& name,  std::string& value);
	void WriteParameter(std::string& name,  D3DXVECTOR3& value);
	void WriteParameter(std::string& name, D3DXVECTOR2& value);
	void WriteParameter(std::string& name, D3DXMATRIX& value);
	void WriteParameter(std::string& name,  unsigned int& value);
	void WriteParameter(std::string& name,  int& value, std::string& readable);
	void WriteParameter(std::string& name, int& value);
	void WriteParameter(std::string& name, float& value);
	void WriteParameter(std::string& name,  bool& value);

	int GetSize();
};

#endif