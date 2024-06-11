#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

extern std::map<char, unsigned> char_to_int;
extern std::map<unsigned, char> int_to_char;

class LongNumber
{
public:
	std::string number;
	void clear();
	void initNumber();
	void initPow();
	void initMod();
	void checkNumber(unsigned base);
	void print();
	void print_alt();
	void printDiv(std::vector<LongNumber> res);
};