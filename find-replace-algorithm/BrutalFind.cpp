#include "BrutalFind.h"

std::vector<std::string::iterator> BrutalFind::FindIter()const
{
	std::vector<std::string::iterator> result;
	for (auto iter=OriginStr->begin(); iter != OriginStr->end(); iter++)
	{
		auto it = iter, jt = PatternStr->begin();
		while (jt != PatternStr->end())
			if (*jt++ != *it++) break;
		if (jt == PatternStr->end()) result.push_back(iter);
	}
	return result;
}

std::vector<std::string::size_type> BrutalFind::FindIndex()const
{
	std::vector<std::string::size_type> result;
	for (std::string::size_type iter = 0; iter < OriginStr->length(); ++iter)
	{
		std::string::size_type i = iter, j = 0;
		while (j < PatternLen)
			if (OriginStr->at(i++) != PatternStr->at(j++)) break;
		if (j >= PatternLen) result.push_back(iter);
	}
	return result;
}

void BrutalFind::ReplaceAll()
{
	for (auto iter = OriginStr->begin(); iter != OriginStr->end(); iter++)
	{
		auto it = iter, jt = PatternStr->begin();
		while (jt != PatternStr->end())
			if (*jt++ != *it++) break;
		if (jt == PatternStr->end())
		{
			OriginStr->replace(iter, iter + PatternLen, *this->ReplaceStr);
			iter = iter + ReplaceLen;
		}
	}
}