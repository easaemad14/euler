#include <iostream>
#include <cmath>

#include "math.hpp"

using namespace std;


// Yet another prime problem
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters!" << endl;
		cerr << "Please provide upper limit" << endl;
		return -1;
	}

	auto ulimit{0u};
	try {
		ulimit = stoi(argv[1]);
	} catch (...) {
		cerr << "Invalid upper limit: " << argv[1] << endl;
		return -1;
	}

	// Output the sum of the primes below the limit
	// One is not prime; start with the first known prime
	auto sum{0ul};
	for (auto i{2u}; i < ulimit; ++i) {
		if (isDefinitelyPrime(i)) {
			sum += i;
		}
	}

	clog << "Sum of primes: " << to_string(sum) << endl;
	return 0;
}
