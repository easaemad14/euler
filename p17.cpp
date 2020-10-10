#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


// We need a couple dictionaries; one based. These are modular, i.e. 120 and 20
// both contain "twenty" in the name.
// Values less than 20 have unique names in English
constexpr auto getLessTwentyCount = [] (unsigned val) -> size_t
{
	auto retVal{0ul};
	switch(val) {
		case 1:  retVal = "one"s.size();       break;
		case 2:  retVal = "two"s.size();       break;
		case 3:  retVal = "three"s.size();     break;
		case 4:  retVal = "four"s.size();      break;
		case 5:  retVal = "five"s.size();      break;
		case 6:  retVal = "six"s.size();       break;
		case 7:  retVal = "seven"s.size();     break;
		case 8:  retVal = "eight"s.size();     break;
		case 9:  retVal = "nine"s.size();      break;
		case 10: retVal = "ten"s.size();       break;
		case 11: retVal = "eleven"s.size();    break;
		case 12: retVal = "twelve"s.size();    break;
		case 13: retVal = "thirteen"s.size();  break;
		case 14: retVal = "fourteen"s.size();  break;
		case 15: retVal = "fifteen"s.size();   break;
		case 16: retVal = "sixteen"s.size();   break;
		case 17: retVal = "seventeen"s.size(); break;
		case 18: retVal = "eighteen"s.size();  break;
		case 19: retVal = "nineteen"s.size();  break;
		default: break;
	}

#if 0
	clog << "getLessTwentyCount of " << to_string(val) << " is " <<
		to_string(retVal) << " ";
#endif
	return retVal;
};

// Multiples of tens (starting with 20)
constexpr auto getTensCount = [] (unsigned val) -> size_t
{
	auto retVal{0ul};
	switch(val) {
		case 2: retVal = "twenty"s.size();  break;
		case 3: retVal = "thirty"s.size();  break;
		case 4: retVal = "forty"s.size();  break;
		case 5: retVal = "fifty"s.size();   break;
		case 6: retVal = "sixty"s.size();   break;
		case 7: retVal = "seventy"s.size(); break;
		case 8: retVal = "eighty"s.size();  break;
		case 9: retVal = "ninety"s.size();  break;
		default: break;
	}

#if 0
	clog << "getTensCount of " << to_string(val) << " is " <<
		to_string(retVal) << " ";
#endif
	return retVal;
};

// Return the number of letters from an integer.
// Conforms to British usage of the word "and".
unsigned
getLetterCount(const int value)
{
	auto retVal{0u};

	// We also need to keep track of British use of "and".
	// I have used the following link for this algorithm:
	// wikipedia.org/wiki/Comparison_of_American_and_British_English#Omission_of_%22and%22_and_%22on%22
	auto hasHundredNumber{false}; 
	auto hasSmallerNumber{false};

	// Count by thousands since this is where our rules reset.
	for (auto i{0}; pow(1000, i) <= value; ++i) {
		auto tmp = value / static_cast<int>(pow(1000, i)) % 1000; 

		// Count the number of hundreds
		if (tmp % 1000 and tmp / 100) {
			retVal += getLessTwentyCount(tmp % 1000 / 100);
			retVal += "hundred"s.length();
			hasHundredNumber = true;
		}

		// Count the tens
		if (tmp % 100) {
			if (tmp % 100 < 20) {
				retVal += getLessTwentyCount(tmp % 100);
			} else {
				retVal += getTensCount(tmp % 100 / 10);
				retVal += getLessTwentyCount(tmp % 10);
			}
			hasSmallerNumber = true;
		}

		// Now we have to count the thousands, millions, etc.
		switch(i) {
			case 0: break;
			case 1: retVal += "thousand"s.length(); break;
			case 2: retVal += "million"s.length(); break;
			case 3: retVal += "trillion"s.length(); break;
			default:
				cerr << "I cannot count that high yet!" << endl;
				return 0;
		}
	}

	// Add the length of "and" if both of these are set (only once)
	if (hasHundredNumber and hasSmallerNumber) {
		retVal += "and"s.size();
	}

#if 0
	clog << "Letter count of " << to_string(value) << " is " <<
		to_string(retVal) << endl;
#endif
	return retVal;
}

// Print out the sum of the letters used in writing numbers in English
// E.g. when 5 is provided, sum of letters is 19 (one, two, three, ...)
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters!"s << endl;
		return -1;
	}

	auto value{0};
	try {
		value = stoi(argv[1]);
	} catch (...) {
		cerr << "Invalid number provided: "s << argv[1] << endl;
		return -1;
	}

	auto sum{0u};
	for (auto i{1}; i <= value; ++i) {
		sum += getLetterCount(i);
	}
	clog << "Sum of letters: "s << to_string(sum) << endl;

	return 0;
}
