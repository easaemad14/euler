#include <vector>
#include <iostream>

#include "math.hpp"

using namespace std;


// Add even values of the Fibonacci sequence, not exceeding 4 million
int
main(int, char**)
{
	auto sum{0ull};
	Fib my_seq;

	for (;;) {
		my_seq(); // Add a new element to the list
		auto current = my_seq.last();
		if (current > 4000000) {
			break;
		}

		sum += (current % 2 == 0) ? current : 0;
		my_seq.shrink(); // Let's be cautious of space complexity
	}

	// Output the sum and return success
	clog << sum << endl;
	return 0;
}
