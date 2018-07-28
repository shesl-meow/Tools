#include "KMP.h"

KMP::KMP(std::string *sour, std::string *pat, std::string *rpl):
    FindSubStr(sour, pat ,rpl)
{
	this->SetPat(pat);
}

void KMP::SetPat(std::string *pat)
{
	this->PatternStr = pat;
	this->PatternLen = pat->length();
	this->GnrIterPatMap();
}

void KMP::SetPat(std::string *pat, bool useIndex)
{
	if (useIndex) this->GnrIndexPatMap();
	this->SetPat(pat);
}

std::vector<std::string::iterator> KMP::FindIter()const
{
	std::vector<std::string::iterator> result;
	if (this->PatIterMap.empty()) return result;

	std::string::iterator it = OriginStr->begin(), jt = PatternStr->begin();
	while (it != OriginStr->end())
	{
		if (*jt != *it++) jt = this->PatIterMap.at(it);
		else if (++jt == PatternStr->end())
		{
			result.push_back(it - PatternLen);
			jt = PatternStr->begin();
		}
	}
	return result;
}

std::vector<std::string::size_type> KMP::FindIndex()const
{
	std::vector<std::string::size_type> result;
	if (this->PatIndexMap.empty()) return result;

	std::string::size_type i = 0, j = 0;
	while (i < this->OriginStr->length())
	{
		if (this->PatternStr->at(j) != this->OriginStr->at(i++)) j = this->PatIndexMap.at(j);
		else if (++j >= this->PatternLen)
		{
			result.push_back(i - PatternLen);
			j = 0;
		}
	}
	return result;
}

void KMP::ReplaceAll()
{
	if (this->PatIterMap.empty()) this->GnrIterPatMap();
	
	std::string::iterator it = OriginStr->begin(), jt = PatternStr->begin();
	while (it != OriginStr->end())
	{
		if (*jt++ != *it++) jt = this->PatIterMap[jt];
		if (jt == PatternStr->end())
		{
			auto rplBegin = it - PatternLen;
			OriginStr->replace(rplBegin, it, *ReplaceStr);
			it = rplBegin + ReplaceLen;
			jt = PatternStr->begin();
		}
	}
}

void KMP::GnrIterPatMap()
{
	std::string::iterator it = PatternStr->begin(), jt = it++;
	PatIterMap[jt] = jt; // 一个都没匹配到时
	PatIterMap[it] = jt; // 只匹配到一个时
    while(it != PatternStr->end())
    {
        if( jt==PatternStr->begin() || *jt==*it)
        {
            it++; jt++;
            PatIterMap[it] = jt;
		}
		else jt = PatIterMap[jt];
    }
}

void KMP::GnrIndexPatMap()
{
	std::string::size_type i = 0, j = i++;
	PatIndexMap[j] = j; // 一个都没匹配到时
	PatIndexMap[i] = j; // 只匹配到一个时
	while (i < this->PatternLen)
	{
		if (j == 0 || OriginStr->at(i) == OriginStr->at(j))
		{
			i++; j++;
			PatIndexMap[i] = j;
		}
		else j = PatIndexMap[j];
	}
}
