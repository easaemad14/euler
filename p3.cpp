#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
using ull = unsigned long long;


// Check if a value is probably prime using Fermat's little theorem
// This will speed up primality tests for (pseudo)prime values
bool
isProbablyPrime(const ull val)
{
	// Compute a^b mod n for very large numbers
	auto powMod = [] (ull a, ull b, ull n) -> ull {
		auto retVal{1ull};
		for (auto i{0ull}; i < b; ++i) {
			retVal = retVal * a % n;
		}

		return retVal;
	};

#if 0
	clog << "Checking if " << to_string(val) << " is probably prime" << endl;
#endif

	// a^(p-1) congruent to 1 mod p?
	return (powMod(2, val-1, val) == 1ull ? true : false);
}

// (Currently) the only sure way to know if a number is prime
bool
isDefinitelyPrime(const ull val)
{
#if 0
	clog << "Checking if " << to_string(val) << " is definitely prime" << endl;
#endif
	auto retVal{true};
	for (auto i = static_cast<ull>(sqrtl(val)); i > 1; --i) {
		if (val % i == 0) {
			retVal = false;
			break;
		}
	}

	return retVal;
}

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
