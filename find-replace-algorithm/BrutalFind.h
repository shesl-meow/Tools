#include "FindSubStr.h"

class BrutalFind : public FindSubStr
{
public:
	BrutalFind(std::string *sour, std::string *pat, std::string *rpl = NULL) :
		FindSubStr(sour, pat, rpl) {}

	std::vector<std::string::iterator> FindIter()const override;
	std::vector<std::string::size_type> FindIndex()const override;
	void ReplaceAll() override;
};