#include <vector>
#include <iostream>

using namespace std;


// Sum all of the numbers between 0 and upper limit provided by user
// (exclusively) that are multiples of 3 or 5.
// Put everything into main because this is easy and quicker
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		clog << "Invalid number of arguments!" << endl;
		clog << "Please supply upper limit as argument" << endl;
		return -1;
	}

	// Get the upper limit from the argument list
	int upper;
	try {
		upper = stoi(argv[1]);
	} catch (...) {
		clog << "Invalid integer: " << argv[1] << endl;
		return -1;
	}

	// Sum all numbers that are foo or bar
	auto sum{0u};
	for (auto i{1}; i < upper; ++i) {
		sum += ((i % 3 == 0) or (i % 5 == 0)) ? i : 0;
	}

	// Output the sum and exit success
	clog << sum << endl;
	return 0;
}
