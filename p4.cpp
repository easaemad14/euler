#include <iostream>

using namespace std;


bool
isPalindrome(int val)
{
	auto retVal{true};

	// Convert the value to a string and check offset from both directions
	// Don't care about middle value if odd length
	auto valStr = to_string(val);
	for (auto i{0u}; i < valStr.length() / 2; ++i) {
		if (valStr[i] not_eq valStr[valStr.length() - i - 1]) {
			retVal = false;
			break;
		}
	}

	return retVal;
}


// Print out the largest palindrome from the product of two 3-digit numbers
// Brute force is quick enough
int
main(int, char**)
{
	auto largest{0};
	for (auto i{100}; i < 1000; ++i) {
		for (auto j{100}; j < 1000; ++j) {
			if (isPalindrome(i*j) && i*j > largest) {
				largest = i*j;
			}
		}
	}

	// Print out the largest and return success
	clog << "Largest palindrome: " << to_string(largest) << endl;
	return 0;
}
