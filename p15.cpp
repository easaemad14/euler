#include <iostream>

#include "math.hpp"

using namespace std;


// Find the number of paths from top left to bottom right for a NxN dimension
// square that can result from moving right and down only.
int
main(int argc, char** argv)
{
	if (argc not_eq 2) {
		cerr << "Invalid number of parameters!" << endl;
		cerr << "Please provide number of grids in square" << endl;
		return -1;
	}

	auto n{0};
	try {
		n = stoi(argv[1]);
	} catch (...) {
		cerr << "Invalid number of grids: " << argv[1] << endl;
		return -1;
	}

	// Known values from the description that are needed for calculation.
	unsigned verts = (n + 1) * (n + 1);
	auto npath = 2 * n;

	// Create the adjacency matrix for the directional graph.
	// This graph is directional because you can only move down or to the
	// right from each vertex.
	Matrix<unsigned long long> adjMat(verts, verts);
	for (auto i{0u}; i < adjMat.numRows(); ++i) {
		if (i + 1 < verts) { // Set the right vertex adjacent
			adjMat.set(i, i + 1, 1);
		}

		if (i + 1 + n < verts) { // Set the below vertex adjacent
			adjMat.set(i, i + 1 + n, 1);
		}
	}

	// Calculate the number of paths of npath length
	// A^npath[0][verts-1] is the value we care about
	auto pathMat = adjMat.pow(npath);

#if 0
	clog << adjMat << endl;
	clog << pathMat << endl;
#endif

	// Output the number of paths and return success
	clog << "Number of paths: " << to_string(pathMat[0][verts - 1]) << endl;
	return 0;
}
