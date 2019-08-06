#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include "serial_util.h"

class Deserializer
{
public:
	virtual ~Deserializer(){}

	//for binary, both of these methods will be empty
	//they are simply there so it exists when xml is implemented..
	virtual void BeginAttribute(std::string& name)=0;
	virtual void EndAttribute()=0;
	
	//returns number of elements to expect
	//assuming WriteNumberOfElements() was used in serialization..
	virtual int ReadNumberOfElements() = 0;

	//methods for parsing serialized data
	virtual void ReadParameter(std::string& name, std::string& value)=0;
	virtual void ReadParameter(std::string& name, D3DXVECTOR3& value)=0;
	virtual void ReadParameter(std::string& name, D3DXVECTOR2& value)=0;
	virtual void ReadParameter(std::string& name, D3DXMATRIX& value)=0;
	virtual void ReadParameter(std::string& name, unsigned int& value)=0;
	virtual void ReadParameter(std::string& name, int& value, std::string& readable)=0;
	virtual void ReadParameter(std::string& name, int& value)=0;
	virtual void ReadParameter(std::string& name, float& value)=0;
	virtual void ReadParameter(std::string& name, bool& value)=0;
};

#endif