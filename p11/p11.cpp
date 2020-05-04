#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


// Read the map.txt file to build the vector
void
importMap(vector<vector<int>> &vect)
{
	ifstream ifs("map.txt");
	if (not ifs.is_open()) {
		cerr << "Unable to open map!" << endl;
		return;
	}

	// Build a temporary vector for each row
	string tmpStr;
	while (getline(ifs, tmpStr)) {
		vector<int> tmpVect;
		for (;;) {
			try { // Lazy way of catching the end
				auto val = stoi(tmpStr);
				tmpVect.push_back(val);
			} catch (...) {
				break;
			}

			// Remove this element from the space-delimited string
			tmpStr.erase(0, tmpStr.find_first_of(' '));

			// Trim spaces from the front
			while (isspace(tmpStr[0])) {
				tmpStr.erase(0, 1);
			}
		}

		vect.push_back(tmpVect);
	}
}

// Return the product starting at x,y coordinates from left to right
unsigned long
getXProd(unsigned x, unsigned y, vector<vector<int>>& vect, unsigned len) {
	auto retVal{0ul};
	if (y + len < vect[x].size()) {
		retVal = 1;
		for (auto i{0u}; i < len; ++i) {
			retVal *= vect[x][y + i];
		}
	}

	return retVal;
};

// Return the product starting at x,y coordinates from top to bottom
unsigned long
getYProd(unsigned x, unsigned y, vector<vector<int>>& vect, unsigned len) {
	auto retVal{0ul};
	if (x + len < vect.size()) {
		retVal = 1;
		for (auto i{0u}; i < len; ++i) {
			retVal *= vect[x + i][y];
		}
	}

	return retVal;
};

// Return the product diagonally top to bottom, left to right
unsigned long
getLToRDiagProd(unsigned x, unsigned y, vector<vector<int>>& vect, unsigned len) {
	auto retVal{0ul};
	if (x + len < vect.size() and y + len < vect[x].size()) {
		retVal = 1;
		for (auto i{0u}; i < len; ++i) {
			retVal *= vect[x + i][y + i];
		}
	}

	return retVal;
};

// Return the product diagonally top to bottom, right to left
unsigned long
getRToLDiagProd(unsigned x, unsigned y, vector<vector<int>>& vect, unsigned len) {
	auto retVal{0ul};
	if (x + len < vect.size() and y >= len) {
		retVal = 1;
		for (auto i{0u}; i < len; ++i) {
			retVal *= vect[x + i][y - i];
		}
	}

	return retVal;
};


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
	vector<vector<int>> series;
	importMap(series);
	// Starting at top left, iterate through map to find largest product
	auto largest{0ull};
	for (auto i{0u}; i < series.size(); ++i) {
		for (auto j{0u}; j < series[i].size(); ++j) {
			auto xprod = getXProd(i, j, series, len);
			if (xprod > largest) {
				largest = xprod;
			}

			auto yprod = getYProd(i, j, series, len);
			if (yprod > largest) {
				largest = yprod;
			}

			auto lrdiag = getLToRDiagProd(i, j, series, len);
			if (lrdiag > largest) {
				largest = lrdiag;
			}

			auto rldiag = getRToLDiagProd(i, j, series, len);
			if (rldiag > largest) {
				largest = rldiag;
			}
		}
	}

	clog << "Value: " << largest << endl;
	return 0;
}
