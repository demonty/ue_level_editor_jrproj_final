#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class Serializer;
class Deserializer;

//all classes that want to be serializable should inherit
//from this class. only two methods need to be implemented
// ReadFrom & WriteTo
// the implementation of these methods will be -almost- identical
// most of the difference is reading rather than writing
// go to the wiki for an example of how to implement

class Serializable
{
public:
	virtual ~Serializable(){}

	virtual void ReadFrom(Deserializer* source) = 0;
	virtual void WriteTo(Serializer* destination) = 0;
};

#endif