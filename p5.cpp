#include <iostream>
#include <numeric>

using namespace std;


// Find the smallest multiple of integers 1 to 20 inclusive
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of arguments!" << endl;
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

	auto val{1};
	for (auto i{2u}; i < ulimit; ++i) {
		val = lcm(val, i);
	}

	clog << "Value: " + to_string(val) << endl;
	return 0;
}
