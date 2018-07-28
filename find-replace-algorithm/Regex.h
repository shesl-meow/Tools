#pragma once
#include "FindSubStr.h"


class Regex : public FindSubStr{
public:
    Regex(std::string *sour, std::string *pat, std::string *rpl = NULL):
		FindSubStr(sour, pat, rpl) {}

};
