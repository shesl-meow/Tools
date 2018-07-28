#pragma once
#include <string>
#include <vector>

class FindSubStr
{
public:
	FindSubStr(std::string *sour, std::string *pat, std::string *rpl=NULL):
		OriginStr(sour), PatternStr(pat), ReplaceStr(rpl), 
		PatternLen(pat->length()), ReplaceLen(rpl->length()) {}

	virtual void SetSour(std::string *sour) { this->OriginStr = sour; }
	virtual void SetPat(std::string *pat) { this->PatternStr = pat; }
	virtual void SetRpl(std::string *rpl) { this->ReplaceStr = rpl; }

	virtual std::vector<std::string::iterator> FindIter()const = 0;
	virtual std::vector<std::string::size_type> FindIndex()const = 0;
	
	virtual void ReplaceAll() = 0;
	virtual void ReplaceByIter(std::string::iterator);
	virtual void ReplaceByIndex(std::string::size_type);

	~FindSubStr() {};
protected:
	std::string *OriginStr;
	std::string *PatternStr;
	std::string::size_type PatternLen;
	std::string *ReplaceStr;
	std::string::size_type ReplaceLen;
};
