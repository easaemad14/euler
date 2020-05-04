#include <iostream>

using namespace std;

// Find the product of a Pythagorean triplet such that a + b + c = 1000
int
main(int, char**)
{
	/**
	 * With the knowledge that a < b < c, we can assume the following:
	 *   -- 1 <= a < 333 (333 = floor(1000/3))
	 *   -- 2 <= b < 500 (500 = floor(1000/2))
	 *   -- We can cull c from the difference
	 */
	for (auto a{1}; a < 333; ++a) {
		for (auto b{1}; b < 500; ++b) {
			auto c = 1000 - a - b;
			if (a*a + b*b == c*c) {
				clog << "Product: " << to_string(a*b*c) << endl;
				return 0;
			}
		}
	}

	return 1;
}
