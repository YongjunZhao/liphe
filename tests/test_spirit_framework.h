#ifndef __TEST_FRAMEWORK__
#define __TEST_FRAMEWORK__

#include <iostream>

#include <sys/resource.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#include <cmp.h>

static inline int log(int size) {
	int i = 0;
	while ((1 << i) < size)
		++i;
	return i;
}

int get_mem() {
	struct rusage rus;
	int res;

	res = getrusage(RUSAGE_SELF, &rus);
	if (res == -1) {
		perror("rusage");
		return 0;
	}

	return rus.ru_maxrss / 1024;
}

static inline int find_prime_bigger_than(int p) {
	int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};

	for (int i = 0; i < sizeof(primes); ++i)
		if (primes[i] >= p)
			return primes[i];
	assert(0);
	return -1;
}

template<class X>
class DiracIterator {
private:
	int _size;
	int _location;

	void copy(const DiracIterator &a) { _size = a._size; _location = a._location; }
public:
	DiracIterator(int s, int l = 0) : _size(s), _location(l) {}
	DiracIterator(const DiracIterator &a) { copy(a); }

	DiracIterator &operator=(const DiracIterator &a) { copy(a); return *this; }

	int begin() { _location = 0; }
	int end() { _location = _size; }

	bool is_end() { _location == _size; }
	bool is_begin() { _location == 0; }

	void operator++() { ++_location; }

	bool operator==(const DiracIterator &a) const {
		return _location == a._location;
	}
	bool operator!=(const DiracIterator &a) const { return !operator==(a); }

	X operator*() const { return (_location == 5) ? X::static_from_int(1) : X::static_from_int(0); }
};


template<class CLASS>
inline bool test_find_first_in_array(int size) {
	int log_size = log(size);

	DiracIterator<CLASS> begin(size);
	DiracIterator<CLASS> end(size, size);

	std::vector<CLASS> output(log_size);

	clock_t start_time = clock();
	BinarySearch<CLASS, CompareEuler<CLASS> >::searchFirst(begin, end, output);
	clock_t end_time = clock();
	std::cout << "Took " << (end_time - start_time) << " milli" << std::endl;

	int max_mul_depth;
	int max_add_depth;
	int L = 0;

	int class_place = 0;
	for (int i = 0; i < log_size; ++i) {
		int add_depth = output[i].add_depth();
		int mul_depth = output[i].mul_depth();

		int log_add = 1;
		while ((1 << log_add) < add_depth)
			++log_add;
		if (L < mul_depth + log_add) {
			max_add_depth = add_depth;
			max_mul_depth = mul_depth;
			L = mul_depth + log_add;
		}

		std::cout << "bit[" << i << "] = " <<output[i].to_int() << std::endl;
		class_place += (1 << i) * output[i].to_int();
	}

	int real_place = 5;

	std::cout << "Test " << ((class_place == 5) ? "OK" : "WRONG!") << "   place = " << class_place << std::endl;
	std::cout << "add depth = " << max_add_depth << std::endl;
	std::cout << "mul depth = " << max_mul_depth << std::endl;


	std::cout << "./test_helib --size=" << size << " --L=" << L << " >& output." << size << std::endl;
	std::cout << "Used " << get_mem() << " MBytes" << std::endl;

	return (real_place == class_place);
}


#endif
