#ifndef SERIAL_UTIL_H
#define SERIAL_UTIL_H
#pragma once

//disables a warning concerning the
//binary serializer/deserializer
//use of buffers in std::copy
#pragma warning(disable : 4996)

#include <d3dx9.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>


// for xml read/write

template <typename O, typename I>
inline const O lexical_cast(const I& source)
{
	std::stringstream s;
	s << source;

	O destination;
	s >> destination;

	return destination;
}

template<>
inline const std::string lexical_cast(const bool& source)
{
	return source ? "true" : "false";
}

template<>
inline const bool lexical_cast(const std::string& source)
{
	return source == "true" ? true : false;
}

#endif