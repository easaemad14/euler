#pragma once
/*******************************************************************************
 * File:        math.hpp
 * Author:      eazy
 *
 * Description: Mathematical functions
 ******************************************************************************/
#include <cmath>
#include <vector>

// Structure for containing Fibonacci sequence
struct Fib {
	std::vector<unsigned> elems;

	unsigned last() {
		return elems[elems.size() - 1];
	}

	void shrink() {
		while (elems.size() > 2) {
			elems.erase(elems.begin());
		}
	}

	// Operator overload to add new elements
	void operator()(void) {
		if (elems.size() < 2) { // Start the list with a couple 1s
			elems.push_back(1);
		} else { // Add the last two elements
			elems.push_back(elems[elems.size() - 1] +
					elems[elems.size() - 2]);
		}
	}
};

// Compute a^b mod n for large numbers
unsigned long long
powMod(
const unsigned long long a,
const unsigned long long b,
unsigned long long n)
{
	auto retVal{1ull};
	for (auto i{0ull}; i < b; ++i) {
		retVal = retVal * a % n;
	}

	return retVal;
}

// Fermat's little theorem to test for primality
// This is quicker, but may result in pseudo-primes
bool
isProbablyPrime(const unsigned long long val)
{
	// a^(p-1) congruent to 1 mod p?
	return (powMod(2, val-1, val) == 1ull ? true : false);
}

// (Currently) the only sure way to know if a number is prime
bool
isDefinitelyPrime(const unsigned long long val)
{
	auto retVal{true};
	for (auto i = static_cast<unsigned long long>(sqrtl(val)); i > 1; --i) {
		if (val % i == 0) {
			retVal = false;
			break;
		}
	}

	return retVal;
}
