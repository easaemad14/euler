#include <iostream>

#include "../math.hpp"

using namespace std;


// Just a simple test file for testing new math operations in math.hpp
int
main(int, char**)
{
	clog << "Creating matrix of size 2, 3" << endl;
	Matrix<int> m1(2, 3);
	auto value{0};
	for (auto i{0}; i < 2; ++i) {
		for (auto j{0}; j < 3; ++j) {
			m1.set(i, j, ++value);
		}
	}
	clog << "Num rows: " << to_string(m1.numRows()) << endl;
	clog << "Num cols: " << to_string(m1.numCols()) << endl;
	clog << m1 << endl;

	auto frow = m1.row(0);
	clog << "The first row of the matrix: " << endl;
	for (auto i : frow) {
		clog << to_string(i) << " ";
	}
	clog << endl;

	auto fcol = m1.col(2);
	clog << "The third column of the matrix: " << endl;
	for (auto i : fcol) {
		clog << to_string(i) << " ";
	}
	clog << endl;

	clog << "Multiplying the matrix by three" << endl;
	auto m2 = m1 * 3;
	clog << m2 << endl;

	clog << "Adding the two matricies" << endl;
	clog << m1 + m2 << endl;

	clog << "Subtracting m2 from m1" << endl;
	clog << m1 - m2 << endl;

	clog << "Transposing the first matrix into 3x2" << endl;
	auto m3 = m1.transpose();
	clog << m3 << endl;

	clog << "Creating square matrix" << endl;
	Matrix<int> smat({ {1, 2}, {3, 4} });
	clog << smat << endl;

	clog << "square matrix cubed" << endl;
	clog << smat.pow(3) << endl;

	clog << "3x2 matrix transposed" << endl;
	auto trans = m3.transpose();
	clog << trans << endl;

	clog << "3x2 * 2x3" << endl;
	clog << m3 * trans << endl;

	return 0;
}
