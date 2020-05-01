#include <iostream>

using namespace std;
using ull = unsigned long long;


int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters!" << endl;
		cerr << "Please provide upper limit" << endl;
		return 1;
	}

	auto ulimit{0u};
	try {
		ulimit = stoi(argv[1]);
	} catch (...) {
		cerr << "Invalid upper limit: " << argv[1] << endl;
		return 1;
	}

	// Find the sum of squares for upper limit, inclusive
	auto sumOfSquares = [] (int limit) -> ull {
		auto retVal{0ull};
		for (auto i{1}; i <= limit; ++i) {
			retVal += i * i;
		}

		return retVal;
	};

	// Find the square of the sum for the upper limit, inclusive
	auto squareOfSum = [] (int limit) -> ull {
		auto retVal{0ull};
		for (auto i{1}; i <= limit; ++i) {
			retVal += i;
		}

		return retVal * retVal;
	};

	clog << "Sum square difference: " << to_string(squareOfSum(ulimit) -
			sumOfSquares(ulimit)) << endl;
	return 0;
}
