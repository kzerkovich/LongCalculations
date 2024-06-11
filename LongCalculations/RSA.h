#pragma once

#include <iostream>
#include <vector>
#include "Operations.h"

class RSA : public Operations {
public:
	int calc_s(LongNumber number);
	LongNumber myRand(LongNumber number);

	bool MillerRabin(LongNumber number, int round = 10);

	void generate_key();
	void encrypt_message();
	void decrypt_message();

	LongNumber gcd(LongNumber a, LongNumber b, LongNumber& x, LongNumber& y);
	void extendedEuclidean(LongNumber a, LongNumber b);
	void myToLower(std::string& word);
	void rsa();

};
