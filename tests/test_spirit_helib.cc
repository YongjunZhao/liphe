#include <iostream>
#include <string.h>

#include <helib_number.h>
#include <eq.h>
#include <binomial_tournament.h>
#include <first_non_zero.h>

#include "test_spirit_framework.h"

int main(int argc, char**argv) {
	HelibKeys keys;

	int size = 0;
//	int L = 20;
	int L = 500;

	for (int argc_i = 0; argc_i < argc; ++argc_i) {
		if (memcmp(argv[argc_i], "--L=", 4) == 0)
			L = atoi(argv[argc_i] + 4);
		if (memcmp(argv[argc_i], "--size=", 7) == 0)
			size = atoi(argv[argc_i] + 7);

		if (strcmp(argv[argc_i], "--help") == 0) {
			std::cout << "   --L=" << std::endl;
			std::cout << "   --size=" << std::endl;
		}
	}

	if (size <= 0)
		size = 64;

	int SIMD_factor = 1;

	long R = 1;
	long p = find_prime_bigger_than(log(size / SIMD_factor));

	std::cout << "Going over an array with " << size << " entries" << std::endl;
	std::cout << "with SIMD factor we need " << (size / SIMD_factor) << " ciphertexts" << std::endl;
	std::cout << "using p =  " << p << std::endl;

	long r = 1;
	long d = 1;
	long c = 2;
	long k = 80;
	long s = 0;
	long chosen_m = 0;
	std::vector<long> gens;
	std::vector<long> ords;

	keys.initKeys(s, R, p, r, d, c, k, 64, L, chosen_m, gens, ords);
	HelibNumber::set_global_keys(&keys);

	test_find_first_in_array<HelibNumber>(size / SIMD_factor);
}

