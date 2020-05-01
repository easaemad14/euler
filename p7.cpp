#include <iostream>
#include <cmath>

using namespace std;

// Print out the nth prime number
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters!" << endl;
		cerr << "Please provide index for a prime number" << endl;
		return 1;
	}

	auto index{0u};
	try {
		index = stoi(argv[1]);
	} catch (...) {
		cerr << "Invalid index: " << argv[1] << endl;
		return 1;
	}

	// Lambda for checking primality (see p3.cpp)
	auto isPrime = [] (unsigned val) -> unsigned {
		auto retVal{true};
		for (auto i = static_cast<unsigned>(sqrt(val)); i > 1; --i) {
			if (val % i == 0) {
				retVal = false;
				break;
			}
		}

		return retVal;
	};

	auto count{0u};
	for (auto i{2}; ; ++i) {
		if (isPrime(i)) {
			++count;
		}

		// If we have reached the index, print and exit
		if (count == index) {
			clog << "Value: " << to_string(i) << endl;
			break;
		}
	}
	return 0;
}
