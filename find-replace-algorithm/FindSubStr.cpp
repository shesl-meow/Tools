#include "FindSubStr.h"

void FindSubStr::ReplaceByIter(std::string::iterator pos)
{
	this->OriginStr->replace(pos, pos + PatternLen, *this->ReplaceStr);
}

void FindSubStr::ReplaceByIndex(std::string::size_type pos)
{
	this->OriginStr->replace(pos, pos + PatternLen, *this->ReplaceStr);
}