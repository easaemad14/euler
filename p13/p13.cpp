#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


// Get the first 10 digits of the sum of the 50 digit numbers in digits.txt
int
main(int, char**)
{
	auto sum{0ull};

	ifstream ifs("digits.txt");
	if (not ifs.is_open()) {
		cerr << "Unable to open the digits file!" << endl;
		return -1;
	}

	// Read the file and store in a container
	vector<string> numList;
	string tmp;
	while (getline(ifs, tmp)) {
		numList.push_back(tmp);
	}
	ifs.close();

	// Do the following for every significant digit (column) starting at end
	// This can easily be done in groups to speed things up
	auto carry{0ll};
	for (auto i{49}; i >= 10; --i) {
		for (auto j{0u}; j < numList.size(); ++j) {
			auto c = numList[i][j];
			carry += atoll(&c);
		}

		// Remove the LSB before continuing onto next significant bit
		carry /= 10;
	}

	// Now, just grab the 10 MSBs and add them all up, including carry
	for (auto i{0u}; i < numList.size(); ++i) {
		sum += stoull(numList[i].substr(0, 10));
	}
	sum += carry;

	// Resize and output the value as a string
	auto sumStr = to_string(sum);
	sumStr.resize(10); // Ensure there's only 10
	clog << "First ten digits: " << sumStr << endl;
	return 0;
}
