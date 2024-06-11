#include <iostream>
#include <string>
#include <vector>
#include "Operations.h"


void Operations::aligment(LongNumber& first, LongNumber& second) {
	int s_first = first.number.size();
	int s_second = second.number.size();

	if (s_first == s_second) return;

	std::string nulls(abs((int)(s_first - s_second)), '0');

	if (s_first < s_second)
		first.number = first.number + nulls;
	else
		second.number = second.number + nulls;
}

LongNumber Operations::add(LongNumber first, LongNumber second, unsigned base) {
	Operations tmp;
	LongNumber result;

	bool fl = false;
	int f = first.number.size() - 1;
	int s = second.number.size() - 1;
	if ((second.number[s] == '-') && (first.number[f] == '-')) {
		first.number = first.number.erase(f, 1);
		second.number = second.number.erase(s, 1);
		fl = true;
	}

	if (first.number[f] == '-') {
		first.number = first.number.erase(f, 1);
		result = tmp.sub(second, first, base).number;
		return result;
	}

	if (second.number[s] == '-') {
		second.number = second.number.erase(s, 1);
		result = tmp.sub(first, second, base).number;
		return result;
	}

	aligment(first, second);

	int size = first.number.size();
	int k = 0, j = 0;

	while (j < size) {
		result.number += int_to_char[(char_to_int[first.number[j]] + char_to_int[second.number[j]] + k) % base];
		k = floor(((double)char_to_int[first.number[j]] + (double)char_to_int[second.number[j]] + (double)k) / (double)base);
		j++;
	}

	if (k)
		result.number += int_to_char[k];

	if (fl)
		result.number += '-';

	first.clear();
	second.clear();

	return result;
}

Operations::modifiedSub Operations::sub(LongNumber first, LongNumber second, unsigned base) {
	bool flag = false;
	LongNumber swap;
	modifiedSub res;
	Operations oper;

	bool f = false, s = false;
	int ff = first.number.size() - 1;
	int ss = second.number.size() - 1;
	if (first.number[ff] == '-') {
		first.number = first.number.erase(ff, 1);
		f = true;
	}
	if (second.number[ss] == '-') {
		second.number = second.number.erase(ss, 1);
		s = true;
	}

	if (f && s) {
		res = oper.sub(second, first, base);
		return res;
	}

	if (f) {
		res.flag = false;
		res.number = oper.add(first, second, base);
		res.number.number = res.number.number + '-';
		return res;
	}

	if (s) {
		res.flag = false;
		res.number = oper.add(first, second, base);
		return res;
	}

	aligment(first, second);

	int i = second.number.size() - 1;
	while (i >= 0) {
		if (char_to_int[first.number[i]] < char_to_int[second.number[i]]) {
			flag = true;
			swap = first;
			first = second;
			second = swap;
			break;
		}
		else if (char_to_int[first.number[i]] != char_to_int[second.number[i]])
			break;
		i--;
	}

	LongNumber result;

	int size = first.number.size();
	int k = 0, j = 0;

	while (j < size) {
		result.number += int_to_char[(char_to_int[first.number[j]] - char_to_int[second.number[j]] + k + base) % base];
		k = floor((double)(char_to_int[first.number[j]] - (double)char_to_int[second.number[j]] + (double)k) / (double)base);
		j++;
	}

	first.clear();
	second.clear();

	result.clear();
	
	if (flag)
		result.number += '-';

	return { flag, result };
}

LongNumber Operations::mul(LongNumber first, LongNumber second, unsigned base) {
	LongNumber result;

	bool f = false, s = false;

	int ff = first.number.size() - 1;
	int ss = second.number.size() - 1;
	if (first.number[ff] == '-') {
		first.number = first.number.erase(ff, 1);
		f = true;
	}
	if (second.number[ss] == '-') {
		second.number = second.number.erase(ss, 1);
		s = true;
	}

	aligment(first, second);

	int n = first.number.size();

	std::string reset(2 * n, '0');

	result.number = reset;

	int k = 0, t, j = 0;

	for (int j = 0; j < n; j++) {
		if (char_to_int[second.number[j]] == 0) {
			result.number[j + n] = '0';
			continue;
		}
		k = 0;
		for (int i = 0; i < n; i++) {
			t = char_to_int[first.number[i]] * char_to_int[second.number[j]] + char_to_int[result.number[i + j]] + k;
			result.number[i + j] = int_to_char[t % base];
			k = floor((double)t / (double)base);
		}
		result.number[j + n] = int_to_char[k];
	}

	first.clear();
	second.clear();

	result.clear();

	if (f ^ s) 
		result.number += "-";

	return result;
}

bool short_div;

std::vector<LongNumber> Operations::div(LongNumber first, LongNumber second, unsigned base) {
	if (second.number == "0") {
		std::cout << "Input error!\n";
		exit(1);
	}

	bool f = false, s = false;
	int ff = first.number.size() - 1;
	int ss = second.number.size() - 1;
	if (first.number[ff] == '-') {
		first.number = first.number.erase(ff, 1);
		f = true;
	}
	if (second.number[ss] == '-') {
		second.number = second.number.erase(ss, 1);
		s = true;
	}

	LongNumber d, u, v, result;
	std::vector<LongNumber> answer, rem;

	u = first;
	v = second;

	int f_size = u.number.size();
	int s_size = v.number.size();

	if (f_size < s_size) {
		LongNumber zero;
		zero.number = "0";

		answer.push_back(zero);
		answer.push_back(first);

		return answer;
	}

	if (f_size == s_size) {
		for (int i = f_size - 1; i >= 0; i--) {
			if (char_to_int[first.number[i]] < char_to_int[second.number[i]]) {
				LongNumber zero;
				zero.number = "0";

				answer.push_back(zero);
				answer.push_back(first);

				return answer;
			}
			else if (char_to_int[first.number[i]] != char_to_int[second.number[i]])
				break;
		}
	}

	if (second.number.size() == 1) {
		short_div = true;
		return mod(first, second, base);
	}

	int n = s_size;
	int m = f_size - s_size;

	std::string nulls(m + 1, '0');

	result.number = nulls;



	d.number = int_to_char[floor(base / (char_to_int[v.number[n - 1]] + 1))];

	Operations oper;

	u = oper.mul(u, d, base);
	v = oper.mul(v, d, base);

	if (d.number == "1")
		u.number = u.number + "0";

	int j = m;

	int q, r;

	while (j >= 0) {

		q = floor((char_to_int[u.number[j + n]] * base + char_to_int[u.number[j + n - 1]]) / char_to_int[v.number[n - 1]]);
		r = (char_to_int[u.number[j + n]] * base + char_to_int[u.number[j + n - 1]]) % char_to_int[v.number[n - 1]];

		if ((q == base) || ((q * char_to_int[v.number[n - 2]]) > (base * r + char_to_int[u.number[j + n - 2]]))) {
			q--;
			r += char_to_int[v.number[n - 1]];
		}

		if (r < base) {
			if ((q == base) || ((q * char_to_int[v.number[n - 2]]) > (base * r + char_to_int[u.number[j + n - 2]]))) {
				q--;
				r += char_to_int[v.number[n - 1]];
			}
		}



		LongNumber u_substr, long_q;
		u_substr.number = u.number.substr(j, n + 1);

		long_q.number = int_to_char[q];

		LongNumber s_part;
				
		s_part = oper.mul(long_q, v, base);

		modifiedSub d4;
		int sss = u_substr.number.size();
		d4 = oper.sub(u_substr, s_part, base);

		bool minus = d4.flag;
		u_substr = d4.number;

		while (u_substr.number.size() != sss) {
			if (minus)
				u_substr.number = u_substr.number.erase((u_substr.number.size() - 1), 1);
			u_substr.number += "0";
			if (minus)
				u_substr.number += "-";
		}

		if (minus) {
			LongNumber b_pow;
			std::string nullsec(n + 1, '0');
			b_pow.number = nullsec + "1";

			u_substr = oper.add(b_pow, u_substr, base);
		}


		result.number[j] = int_to_char[q];


		if (minus) {
			result.number[j] = int_to_char[char_to_int[result.number[j]] - 1];

			u_substr = oper.add(v, u_substr, base);
		}

		u.number = u.number.substr(0, j) + u_substr.number;

		j--;
	}

	LongNumber remaind;
	remaind.number = u.number.substr(0, n);

	result.clear();

	if (f ^ s)
		result.number += "-";

	answer.push_back(result);

	rem = mod(remaind, d, base);

	answer.insert(end(answer), begin(rem), end(rem));

	return answer;
}

std::vector<LongNumber> Operations::mod(LongNumber first, LongNumber second, unsigned base)
{
	LongNumber result;

	std::vector<LongNumber> answer;

	int r = 0;
	int j = first.number.size() - 1;

	std::string nus(j + 1, '0');

	result.number = nus;

	for (j; j >= 0; j--) {
		result.number[j] = int_to_char[floor((r * base + char_to_int[first.number[j]]) / char_to_int[second.number[0]])];
		r = (r * base + char_to_int[first.number[j]]) % char_to_int[second.number[0]];
	}

	if (short_div) {
		result.clear();
		LongNumber rem;
		rem.number = std::to_string(r);

		answer.push_back(result);
		answer.push_back(rem);
	}
	else
	{
		result.clear();

		answer.push_back(result);
	}

	return answer;
}

bool Operations::greater(LongNumber& first, LongNumber& second)
{
	int f = first.number.size();
	int s = second.number.size();

	if (f > s)
		return true;
	if (s > f)
		return false;

	for (int i = s - 1; i >= 0; i--) {
		if (char_to_int[first.number[i]] < char_to_int[second.number[i]]) {
			return false;
		}
		else if (char_to_int[first.number[i]] != char_to_int[second.number[i]])
			return true;
	}

	return false;
}

LongNumber Operations::pow_mod(LongNumber first, LongNumber pow, LongNumber module, unsigned base) {
	if (module.number == "0") {
		std::cout << "Input error!\n";
		exit(1);
	}

	Operations operation;

	LongNumber n = pow;
	LongNumber y;
	y.number = "1";
	LongNumber z = first;

	if (n.number == "0")
		return operation.div(y, module, base)[1];

	LongNumber two;
	two.number = "2";

	int k = 1;
	while (1) {
		std::vector<LongNumber> half_n = operation.div(n, two, base);

		n = half_n[0];

		if (half_n[1].number != "0") {
			y = operation.mul(z, y, base);
			y = operation.div(y, module, base)[1];

			if (n.number == "0") {
				return y;
			}
			z = operation.mul(z, z, base);
			z = operation.div(z, module, base)[1];
		}
		else {
			z = operation.mul(z, z, base);
			z = operation.div(z, module, base)[1];
		}
	}
}