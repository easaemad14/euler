#include <vector>
#include <iostream>

using namespace std;


struct Fib {
	vector<unsigned> elems;

	unsigned last() {
		return elems[elems.size() - 1];
	}

	void shrink() {
		while (elems.size() > 2) {
			elems.erase(elems.begin());
		}
	}

	// Operator overload to add new elements
	void operator()(void) {
		if (elems.size() < 2) { // Start the list with a couple 1s
			elems.push_back(1);
		} else { // Add the last two elements
			elems.push_back(elems[elems.size() - 1] +
					elems[elems.size() - 2]);
		}
	}
};

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
