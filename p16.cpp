#include <iostream>
#include <string>
#include <gmpxx.h>

using namespace std;


/**
 * It is known that there are patters for digital roots (applying the digit sum
 * of a number until you have a single digit), but I don't know if patterns
 * exist for digit sums. My intuition tells me that this is unbounded and I have
 * to solve this heuristically.
 */

// Return the sum of the digits of 2^x
int
main(int argc, char** argv)
{
    if (argc not_eq 2) {
        cerr << "Invalid number of paramters!" << endl;
        cerr << "Please provide exponent" << endl;
        return -1;
    }

    auto exp{0};
    try {
        exp = stoi(argv[1]);
    } catch (...) {
        cerr << "Invalid exponent value: " << argv[1] << endl;
        return -1;
    }

    // Calculate our large number, using GMP
    mpz_class val("1");
    for (auto i{0}; i < exp; ++i) {
        val *= 2;
    }

    // Sum all values
    mpz_class sum("0");
    while (val != 0) {
        sum += val % 10; // LSB in base 10
        val /= 10;
    }

    clog << "Sum of digits: " << sum << endl;
    return 0;
}
