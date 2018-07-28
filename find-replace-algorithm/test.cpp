#include <iostream>
#include <ctime>
#include "KMP.h"
#include "BrutalFind.h"

const std::string str = "hello World! World! abcabcdabcjklabc? ";

int main(){
	std::string strcp1 = str, strcp2 = str;
    std::string pattern = "abcabcdabcjklabc";
    std::string rpl = "World!";

	std::clock_t kmpbegin = std::clock();
    KMP kmp(&strcp1, &pattern, &rpl);
	kmp.ReplaceAll();
	std::clock_t kmpend = std::clock();

	std::clock_t brutalbegin = std::clock();
	BrutalFind bru(&strcp2, &pattern, &rpl);
	bru.ReplaceAll();
	std::clock_t brutalend = std::clock();

	std::cout << "kmp: " << strcp1 << "; time: " << (kmpend - kmpbegin) << std::endl;
	std::cout << "brutal: " << strcp2 << "; time: " << (brutalend - brutalbegin) << std::endl;
	while (1);
    return 0;
}