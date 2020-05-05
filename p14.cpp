#include <iostream>
#include <vector>
#include <utility>

using namespace std;


// Find number under one million that produces longest Collatz sequence:
// n -> n/2 when n is even
// n -> 3n + 1 when n is odd
int
main(int, char**)
{
	// Keep track of starting value and length, respectively
	// Starting case of 1 has length 1?
	auto longest = make_pair(1ull, 1ull);

	for (auto i{2ull}; i < 1000000; ++i) {
		vector<unsigned long long> cSeq(1, i);
		for (;;) {
			if (cSeq.back() == 1) { // Done
				if (cSeq.size() > longest.second) {
					longest.first = i;
					longest.second = cSeq.size();
				}
				break;
			}

			cSeq.push_back(cSeq.back() % 2 == 0 ?
					cSeq.back() / 2 : 3 * cSeq.back() + 1);
		}

#if 0
		clog << "Starting value: " << to_string(i) << endl;
		clog << "Chain: ";
		for (auto val : cSeq) {
			clog << to_string(val) << "->";
		}
		clog << endl;
#endif
	}

	clog << "Value: " << to_string(longest.first) << endl;
	return 0;
}
