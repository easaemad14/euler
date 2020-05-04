#include <iostream>
#include <cmath>

using namespace std;


int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters" << endl;
		cerr << "Please provide number of divisors" << endl;
		return -1;
	}

	auto numDivisors{0u};
	try {
		numDivisors = stoi(argv[1]);
	} catch (...) {
		cerr << "Not a valid number of divisors: " << argv[1] << endl;
		return -1;
	}

	// Get the Nth triangle number
	auto getNthTriangleNumber = [] (unsigned n) -> unsigned {
		auto retVal{0u};
		for (auto i{1u}; i <= n; ++i) {
			retVal += i;
		}

		return retVal;
	};

	auto getNumDivisors = [] (unsigned long long n) -> unsigned {
		auto retVal{0u};
		for (auto i{1u}; i <= static_cast<unsigned>(sqrt(n)); ++i) {
			if (n % i == 0) {
				if (i*i == n) { // Perfect square?
					++retVal;
				} else {
					retVal += 2;
				}
			}
		}

		return retVal;
	};

	for (auto i{1u}; ; ++i) {
		auto triNum = getNthTriangleNumber(i);
		if (getNumDivisors(triNum) > numDivisors) {
			clog << "Value: " << to_string(triNum) << endl;
			return 0;
		}
	}

	return -1;
}
