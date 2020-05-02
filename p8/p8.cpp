#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Read the map.txt file to build the vector
void
importMap(vector<int> &vect)
{
	ifstream ifs("map.txt");
	if (not ifs.is_open()) {
		cerr << "Unable to open map!" << endl;
		return;
	}

	for (;;) {
		char val = ifs.get();

		// Prematurely exited the file?
		if (ifs.eof()) {
			break;
		}

		// Hack to check for EOL because I'm lazy
		if (not isdigit(val)) {
			val = ifs.get();
		}

		vect.push_back(atoi(&val));
	}
}

// Find the largest product in a series
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters!" << endl;
		cerr << "Please provide number of digits" << endl;
		return 1;
	}

	auto len{0u};
	try {
		len = stoi(argv[1]);
	} catch (...) {
		cerr << "Invalid length: " << argv[1] << endl;
		return 1;
	}

	// Get the map into a single digit vector
	vector<int> series;
	importMap(series);

	// Find largest product
	auto largest{0ull};
	for (auto i{0u}; i < series.size(); ++i) {
		if (i + len >= series.size()) {
			break;
		}

		auto prod{1ull};
		for (auto j{0u}; j < len; ++j) {
			prod *= series[i + j];
		}

		if (prod > largest) {
			largest = prod;
		}
	}

	clog << "Value: " << largest << endl;
	return 0;
}
