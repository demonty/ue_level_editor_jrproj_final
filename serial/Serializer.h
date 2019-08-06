#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serial_util.h"

class Serializer
{
public:
	virtual ~Serializer(){}

	//for binary, both of these methods will be empty
	//they are simply there so it exists when xml is implemented..
	virtual void BeginAttribute(std::string& name)=0;
	virtual void EndAttribute()=0;
	
	//this is to let know how many elements to expect
	//like when you are going to serialize a bunch
	//of the same object-type
	virtual void WriteNumberOfElements(int elements) = 0;

	virtual void WriteParameter(std::string& name, std::string& value)=0;
	virtual void WriteParameter(std::string& name, D3DXVECTOR3& value)=0;
	virtual void WriteParameter(std::string& name, D3DXVECTOR2& value)=0;
	virtual void WriteParameter(std::string& name, D3DXMATRIX& value)=0;
	virtual void WriteParameter(std::string& name, unsigned int& value)=0;
	virtual void WriteParameter(std::string& name, int& value, std::string& readable)=0;
	virtual void WriteParameter(std::string& name, int& value)=0;
	virtual void WriteParameter(std::string& name, float& value)=0;
	virtual void WriteParameter(std::string& name, bool& value)=0;
};

#endif