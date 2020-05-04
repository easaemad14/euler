#include <vector>
#include <iostream>
#include <cmath>

#include "math.hpp"

using namespace std;
using ull = unsigned long long;


// Put all factors of value into the list
void
factor_primes(ull value, vector<ull> &flist)
{
	// Ensure the list is empty when we start
	flist.clear();

	for (auto i{2ull}; i < value; ++i) {
		// Only check primality if it is a factor to save time
		if (value % i == 0 and isProbablyPrime(i) and
				isDefinitelyPrime(i)) {
			flist.push_back(i);
		}
	}
}

// Output the largest prime factor of a number
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of arguments" << endl;
		cerr << "Please provide value to factor" << endl;
		return -1;
	}

	ull value;
	try {
		value = stoul(argv[1]);
	} catch (...) {
		cerr << "Invalid parameter: " << argv[1] << endl;
		return -1;
	}

	// Factor the value by primes
	vector<ull> flist;
	factor_primes(value, flist);

	// Sorting will take too much time, just iterate to find the largest
	auto largest{0u};
	for (auto i : flist) {
		if (i > largest) {
			largest = i;
		}
	}

	// Print the largest value and return success
	clog << largest << endl;
	return 0;
}
