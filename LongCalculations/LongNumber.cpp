#include <iostream>
#include <set>

#include "LongNumbers.h"

std::map<char, unsigned> char_to_int
{
	{'0', 0},	{'1', 1},	{'2', 2},	{'3', 3},
	{'4', 4},	{'5', 5},	{'6', 6},	{'7', 7},
	{'8', 8},	{'9', 9},	{'A', 10},	{'B', 11},
	{'C', 12},	{'D', 13},	{'E', 14},	{'F', 15}
};

std::map<unsigned, char> int_to_char {
	{0, '0'},	{1, '1'},	{2, '2'},	{3, '3'},
	{4, '4'},	{5, '5'},	{6, '6'},	{7, '7'},
	{8, '8'},	{9, '9'},	{10, 'A'},	{11, 'B'},
	{12, 'C'},	{13, 'D'},	{14, 'E'},	{15, 'F'}
};

void LongNumber::initNumber() {
	std::cin	>> number;
	std::reverse(begin(number), end(number));
}

void LongNumber::initPow(){
	std::cout << "Enter degree: \n";
	std::cin >> number;
	std::reverse(begin(number), end(number));
}

void LongNumber::clear()
{
	reverse(begin(number), end(number));
	int t = 0;
	while (char_to_int[number[t]] == 0 && number.size() != 1) {
		number.erase(0, 1);
	}
	reverse(begin(number), end(number));
}

void LongNumber::initMod() {
	std::cout << "Enter module: \n";
	std::cin >> number;
	std::reverse(begin(number), end(number));
}

void LongNumber::printDiv(std::vector<LongNumber> res)
{
	reverse(begin(res[0].number), end(res[0].number));
	reverse(begin(res[1].number), end(res[1].number));

	std::cout << "\nResult: " << res[0].number;
	std::cout << "\nRemainder: " << res[1].number;
}

void LongNumber::checkNumber(unsigned base) {
	reverse(begin(number), end(number));
	std::set<char> curAlphabet;
	for (int i = 0; i < number.size(); i++)
		curAlphabet.insert(number[i]);

	if (number.size() > 1 && char_to_int[number[0]] == 0) {
		std::cout << "Input Error!";
		exit(0);
	}

	bool sizeAlphabet	= curAlphabet.size() > base;
	bool noLetter		= false;
	bool overLetter		= false;

	for (char c : curAlphabet) {
		if (char_to_int.count(c) == 0)
			noLetter = true;

		if (char_to_int[c] >= base)
			overLetter = true;
	}

	if (sizeAlphabet || noLetter || overLetter || number.empty()) {
		std::cout << "Input Error!";
		exit(0);
	}

	reverse(begin(number), end(number));
}

void LongNumber::print() {
	reverse(begin(number), end(number));
	std::cout << "\nResult: " << number;
}

void LongNumber::print_alt() {
	reverse(begin(number), end(number));
	std::cout << number;
}
