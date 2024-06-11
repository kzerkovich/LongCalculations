#pragma once

#include <iostream>
#include <vector>
#include "LongNumbers.h"

class Operations : public LongNumber {
public:
	struct modifiedSub {
		bool flag;
		LongNumber number;
	};

	void aligment(LongNumber& first, LongNumber& second);

	bool greater(LongNumber& first, LongNumber& second);

	LongNumber add(LongNumber first, LongNumber second, unsigned base);
	modifiedSub sub(LongNumber first, LongNumber second, unsigned base);
	LongNumber mul(LongNumber first, LongNumber second, unsigned base);
	std::vector<LongNumber> div(LongNumber first, LongNumber second, unsigned base);
	std::vector<LongNumber> mod(LongNumber first, LongNumber second, unsigned base);
	LongNumber pow_mod(LongNumber first, LongNumber pow, LongNumber module, unsigned base);
};