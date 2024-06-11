#include <iostream>
#include <Windows.h>
#include <string>
#include "RSA.h"
unsigned base = 10;

void initBase() {
	std::cout << "Enter base of number: \n";
	std::cin >> base;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Rus");

	LongNumber first, second, pow, module, result;
	Operations temp;
	RSA t;

	//first.number = "0";
	//second.number = "0";
	std::vector<LongNumber> res;

	// initBase();
	//first.initNumber();
	//first.checkNumber(base);

	//second.initNumber();
	//second.checkNumber(base);

	//temp.aligmentAdd(&first, &second);
	//temp.aligmentSub(first, second);
	//t.extendedEuclidean(first, second, pow, module);

	//res = temp.div(first, second, base);

	//result.printDiv(res);
	//pow.print();
	//module.print();
	t.rsa();
	//std::cout << t.gcd(first, second);
	//res = temp.div(first, second, base);
	//result.printDiv(res);
	
	// Для возведения по модулю
	//pow.initPow();
	//pow.checkNumber(base);

	//module.initMod();
	//module.checkNumber(base);

	//result = temp.pow_mod(first, pow, module, base);
	//result.print();
	// 
	//std::cout << t.MillerRabin(first);
	//result.print();
}