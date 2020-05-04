#include <iostream>
#include <cmath>

#include "math.hpp"

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

	auto count{0u};
	for (auto i{2}; ; ++i) {
		if (isDefinitelyPrime(i)) {
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
