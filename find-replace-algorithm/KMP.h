#pragma once
#include "FindSubStr.h"
#include <map>

namespace KMP{
	class KMP;
}

class KMP: public FindSubStr{
public:
    KMP(std::string *sour, std::string *pat, std::string *rpl=NULL);

	void SetPat(std::string *pat) override;
	void SetPat(std::string *pat, bool useIndex);

	std::vector<std::string::iterator> FindIter()const override;
	std::vector<std::string::size_type> FindIndex()const override;

	void ReplaceAll() override;

private:
	std::string *PatternStr;
	
	void GnrIterPatMap();
    std::map<std::string::iterator, std::string::iterator> PatIterMap;
	void GnrIndexPatMap();
	std::map<std::string::size_type, std::string::size_type> PatIndexMap;
};
