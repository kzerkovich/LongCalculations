#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "RSA.h"

std::map<char, unsigned> alphabet {
	{'ú', 166}, {'û', 168}, {'ü', 171}, {'à', 741}, {'á', 743}, {'â', 745},	{'ã', 747}, {'ä', 749}, {'å', 751}, 
	{'¸', 753}, {'æ', 755}, {'ç', 757}, {'è', 759}, {'é', 761}, {'ê', 763},
	{'ë', 765}, {'ì', 767}, {'í', 769}, {'î', 771}, {'ï', 773}, {'ð', 775}, {'ñ', 777}, {'ò', 779}, {'ó', 781},
	{'ô', 783}, {'÷', 785}, {'ö', 787}, {'÷', 789}, {'ø', 791}, {'ù', 793}, {'ý', 795}, {'þ', 797}, {'ÿ', 799},
	{'.', 564}, {',', 563}, {'?', 562}, {'!', 561}, {';', 333}, {':', 559}, {'"', 558}, {'\'', 557}, {'-', 556},
	{'(', 555}, {')', 554}, {'[', 553}, {']', 552}, {'0', 551}, {'1', 222}, {'2', 549}, {'3', 548}, {'4', 547},
	{'5', 546}, {'6', 545}, {'7', 544}, {'8', 543}, {'9', 542}, {' ', 111}
};

std::map<unsigned, char> alphabet_inverse{
	{166, 'ú'}, {168, 'û'}, {171, 'ü'}, {741, 'à'}, {743, 'á'}, {745, 'â'},
	{747, 'ã'}, {749, 'ä'}, {751, 'å'}, {753, '¸'}, {755, 'æ'}, {757, 'ç'}, {759, 'è'}, {761, 'é'}, {763, 'ê'},
	{765, 'ë'}, {767, 'ì'}, {769, 'í'}, {771, 'î'}, {773, 'ï'}, {775, 'ð'}, {777, 'ñ'}, {779, 'ò'}, {781, 'ó'},
	{783, 'ô'}, {785, '÷'}, {787, 'ö'}, {789, '÷'}, {791, 'ø'}, {793, 'ù'}, {795, 'ý'}, {797, 'þ'}, {799, 'ÿ'},
	{564, '.'}, {563, ','}, {562, '?'}, {561, '!'}, {333, ';'}, {559, ':'}, {558, '"'}, {557, '\''}, {556, '-'},
	{555, '('}, {554, ')'}, {553, '['}, {552, ']'}, {551, '0'}, {222, '1'}, {549, '2'}, {548, '3'}, {547, '4'},
	{546, '5'}, {545, '6'}, {544, '7'}, {543, '8'}, {542, '9'}, {111, ' '}
};

void RSA::myToLower(std::string& word) {

	std::vector <std::string> lc = { "à", "á", "â", "ã", "ä", "å", "¸", "æ", "ç", "è", "é", "ê", "ë", "ì", "í", "î", "ï", "ð", "ñ", "ò", "ó", "ô", "õ", "ö", "÷", "ø", "ù", "ý", "þ", "ÿ" };
	std::vector <char> uc = { 'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', '¨', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ý', 'Þ', 'ß' };

	for (int i = 0; i <= word.length() - 1; i++) {
		for (int u = 0; u <= uc.size() - 1; u++) {
			if (word[i] == uc[u]) {
				word.replace(i, 1, lc[u]);
			}
		}
	}
}

int RSA::calc_s(LongNumber number) {
	unsigned int base = 10;
	Operations operation;
	LongNumber two, copy;

	int s = 0;
	copy = number;
	two.number = "2";

	while (operation.div(copy, two, base)[1].number == "0") {
		two.number = "2";
		s++;
		copy = operation.div(copy, two, base)[0];
		two.number = "2";
	}

	return s;
}

LongNumber RSA::myRand(LongNumber number) {
	int size = number.number.size();
	srand(time(0));
	Operations t;
	LongNumber result;
	RSA k;

	for (int i = 0; i < size; i++) {
		int tmp = (rand() % 10);
		if (tmp == 0) {
			tmp++;
		}
		result.number += std::to_string(tmp);
	}

	return result;
}

bool RSA::MillerRabin(LongNumber number, int round) {
	unsigned int base = 10;
	Operations operation;
	
	LongNumber two, one;
	two.number = "2";
	one.number = "1";
	
	if (operation.div(number, two, base)[1].number == "0")
		return false;


	int s = calc_s(operation.sub(number, one, base).number);

	LongNumber new_pow, t;
	new_pow.number = std::to_string(int(std::pow(2, s)));

	reverse(begin(new_pow.number), end(new_pow.number));

	t = operation.div(number, new_pow, base)[0];

	for (int i = 0; i < round; i++) {
		LongNumber r = operation.sub(number, two, base).number;
		LongNumber tmp = myRand(r);
		LongNumber x = operation.pow_mod(tmp, t, number, base);

		if ((x.number == one.number) || (x.number == operation.sub(number, one, base).number.number))
			continue;
		int j;
		for (j = 0; j < s - 1; j++) {
			x = operation.pow_mod(x, two, number, base);
			if (x.number == one.number)
				return false;
			if (x.number == operation.sub(number, one, base).number.number)
				break;
		}

		if (j == s - 1)
			return false;
	}
	return true;
}

LongNumber RSA::gcd(LongNumber a, LongNumber b, LongNumber& x, LongNumber& y) {
	unsigned int base = 10;
	if (b.number == "0") {
		x.number = "1";
		y.number = "0";
		return a;
	}

	Operations operation;
	LongNumber test = operation.div(a, b, base)[1];
	LongNumber gcd = RSA::gcd(b, test, y, x);


	LongNumber tmp = operation.mul(operation.div(a, b, base)[0], x, base);


	y = operation.sub(y, tmp, base).number;


	y.clear();

	return gcd;
}

std::vector<LongNumber> vectorP, tmp_vec;

void RSA::extendedEuclidean(LongNumber a, LongNumber m)
{
	unsigned int base = 10;
	LongNumber qwerty;
	qwerty.number = "1";
	tmp_vec.push_back(qwerty);


	LongNumber temp, da;
	Operations oper;

	while (oper.div(m, a, base)[1].number != "0") {
		vectorP.push_back(oper.div(m, a, base)[0]);
		temp = a;
		a = oper.div(m, a, base)[1];
		m = temp;
	}

	vectorP.push_back(m);
	tmp_vec.push_back(vectorP[0]);

	for (long i = 2; i < vectorP.size(); i++) {
		da = oper.mul(vectorP[i - 1], tmp_vec[i - 1], base);

		tmp_vec.push_back(oper.add(da, tmp_vec[i - 2], base));
	}
}

void RSA::generate_key() {
	unsigned int base = 10;

	RSA miller_rabin, nod, ex_nod;
	LongNumber p, q, n, phi;
	Operations operation;

	std::cout << "Enter p: \n";
	p.initNumber();
	p.checkNumber(base);

	if (!miller_rabin.MillerRabin(p)) {
		std::cout << "p not a prime number";
		exit(1);
	}

	std::cout << "Enter q: \n";
	q.initNumber();
	q.checkNumber(base);

	if (!miller_rabin.MillerRabin(q)) {
		std::cout << "q not a prime number";
		exit(1);
	}

	n = operation.mul(p, q, base);

	LongNumber one, tmp_p, tmp_q;
	one.number = "1";

	tmp_p = operation.sub(p, one, base).number;
	tmp_q = operation.sub(q, one, base).number;
	phi = operation.mul(tmp_p, tmp_q, base);

	LongNumber e, tmp1, tmp2;
	e.number = "2";

	while (nod.gcd(e, phi, tmp1, tmp2).number != "1") {
		e = myRand(phi);
	}

	LongNumber d;

	extendedEuclidean(e, phi);

	int nq = tmp_vec.size() - 1;
	LongNumber gr, lk;

	if (nq % 2 == 0)
		gr.number = "1";
	else
		gr.number = "1-";

	one.number = "1";

	d = operation.mul(gr, tmp_vec[nq], base);

	if (d.number[d.number.size() - 1] == '-') {
		d = operation.add(d, phi, base);
	}

	std::cout << "\n\ne = ";
	e.print_alt();
	std::cout << "\nd = ";
	d.print_alt();
	std::cout << "\nn = ";
	n.print_alt();

	std::ofstream out;
	out.open("public key.txt");
	if (out.is_open()) {
		out << e.number << " " << n.number;
	}
	out.close();
	out.open("private key.txt");
	if (out.is_open()) {
		out << d.number << " " << n.number;
	}
	out.close();
}

void RSA::encrypt_message()
{
	unsigned int base = 10;

	std::ifstream in("public key.txt");
	if (!in.is_open()) {
		std::cout << "The file does not exist!";
		exit(1);
	}
	std::string line;
	std::getline(in, line);
	in.close();
	LongNumber e, n;
	bool probel = true;
	for (int i = 0; i < line.size(); i++) {
		if (probel && line[i] != ' ') {
			e.number += line[i];
		}
		else if (line[i] != ' ') {
			n.number += line[i];
		}
		else {
			probel = false;
			continue;
		}
	}

	reverse(begin(e.number), end(e.number));
	reverse(begin(n.number), end(n.number));

	std::ifstream data("data.txt");
	if (!data.is_open()) {
		std::cout << "The file does not exist!";
		exit(1);
	}
	std::string fdata, clear;

	std::cout << "\nInitial data:\n";
	while (std::getline(data, fdata)) {
		myToLower(fdata);
		for (int i = 0; i < fdata.size(); i++) {
			if (alphabet.find(fdata[i]) != alphabet.end()) {
				clear += fdata[i];
			}
		}
		std::cout << fdata << "\n";
	}

	data.close();

	std::cout << "\nCleared data:\n";
	std::cout << clear;


	std::ofstream encrypted_data;
	encrypted_data.open("encrypted data.txt");
	if (encrypted_data.is_open()) {
		std::string code, enccode;
		for (int i = 0; i < clear.size(); i++) {
			code += std::to_string(alphabet[clear[i]]);
		}
		
		std::cout << "\n\nCode:\n" << code;

		int j = 0;
		while (j < code.size() - 1) {
			LongNumber tmp;
			Operations t;
			do {
				reverse(begin(tmp.number), end(tmp.number));
				tmp.number += code[j++];
				reverse(begin(tmp.number), end(tmp.number));
			} while (t.greater(n, tmp) && (j < code.size()));

			reverse(begin(tmp.number), end(tmp.number));
			if (j != code.size())
				tmp.number.erase(tmp.number.size() - 1, 1);

			reverse(begin(tmp.number), end(tmp.number));
			std::cout << "\n\nBlock: "; tmp.print_alt();

			reverse(begin(tmp.number), end(tmp.number));
			LongNumber er;
			er = t.pow_mod(tmp, e, n, base);
			std::cout << "\nEncrypted block: "; er.print_alt();
			enccode += er.number;
			encrypted_data << er.number << " ";
			tmp.number = "";
			j--;
		}

		std::cout << "\n\nEncrypted code:\n" << enccode;
	}

	encrypted_data.close();
}

void RSA::decrypt_message() {
	unsigned int base = 10;

	std::ifstream in("private key.txt");
	if (!in.is_open()) {
		std::cout << "The file does not exist!";
		exit(1);
	}
	std::string line;
	std::getline(in, line);
	in.close();

	LongNumber d, n;
	bool probel = true;
	for (int i = 0; i < line.size(); i++) {
		if (probel && line[i] != ' ') {
			d.number += line[i];
		}
		else if (line[i] != ' ') {
			n.number += line[i];
		}
		else {
			probel = false;
			continue;
		}
	}

	reverse(begin(d.number), end(d.number));
	reverse(begin(n.number), end(n.number));

	std::ifstream data("encrypted data.txt");
	if (!data.is_open()) {
		std::cout << "The file does not exist!";
		exit(1);
	}

	std::string fdata, clear;

	std::ofstream decrypted_data;
	decrypted_data.open("decrypted data.txt");
	if (decrypted_data.is_open()) {
		std::string decr;
		while (std::getline(data, fdata)) {
			int i = 0;

			LongNumber tmp, test;
			Operations oper;

			while (i < fdata.size()) {
				if (fdata[i] != ' ') {
					tmp.number += fdata[i];
					i++;
				}
				else {
					reverse(begin(tmp.number), end(tmp.number));
					std::cout << "\n\nRead block: "; tmp.print_alt();
					reverse(begin(tmp.number), end(tmp.number));
					test = oper.pow_mod(tmp, d, n, base);
					std::cout << "\nDecrypted read block: "; test.print_alt();
					decr += test.number;
					tmp.number = "";
					i++;
				}
			}
		}

		std::cout << "\n\nDecrypted code: "; std::cout << decr;

		while (decr.size() != 0) {
			std::string tee = decr.substr(0, 3);
			decrypted_data << alphabet_inverse[std::stoi(tee)];
			decr.erase(0, 3);
		}
	}
}

void RSA::rsa() {
	std::cout << "Select a mode:\n1 - Key generation\n2 - Encryption\n3 - Decryption\n\nYour choice: ";

	int choice; std::cin >> choice;

	switch (choice)
	{
	case 1:
		generate_key();
		break;
	case 2:
		encrypt_message();
		break;
	case 3:
		decrypt_message();
		break;
	default:
		break;
	}
}