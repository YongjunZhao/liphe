#include <string.h>
#include <zp.h>
#include <eq.h>
#include <binomial_tournament.h>
#include <first_non_zero.h>
#include <primes.h>

#include "test_spirit_framework.h"

#define SIMD_FACTOR 1
typedef ZP<SIMD_FACTOR> MyZP;

int main(int argc, char**argv) {

	int size = 1024;

	for (int argc_i = 0; argc_i < argc; ++argc_i) {
		if (memcmp(argv[argc_i], "--size=", 7) == 0)
			size = atoi(argv[argc_i] + 7);

		if (strcmp(argv[argc_i], "--help") == 0) {
			std::cout << "   --L=" << std::endl;
		}
	}

	int p = Primes::find_prime_bigger_than(log(size / SIMD_FACTOR));
	MyZP::set_global_p(p);
	std::cout << "using p = " << p << std::endl;

	test_find_first_in_array<MyZP>(size / SIMD_FACTOR);
}

