#include <iostream>

using namespace std;


// Find the smallest multiple of integers 1 to 20 inclusive
int
main(int, char**)
{
	// Lambda to check for LCM of all values between 1 and 20 inclusive
	auto isLcm = [] (int val) -> bool {
		auto retVal{true}; // Innocent until proven guilty
		for (auto i{1}; i <= 20; ++i) {
			if (val % i != 0) {
				retVal = false;
				break;
			}
		}

		return retVal;
	};

	// Just another brute-force implementation; nothing fancy here
	for (auto i{1}; ; ++i) {
		if (isLcm(i)) {
			clog << "Value: " + to_string(i) << endl;
			break;
		}
	}

	return 0;
}
