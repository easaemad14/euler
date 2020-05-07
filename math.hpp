#pragma once
/*******************************************************************************
 * File:        math.hpp
 * Author:      eazy
 *
 * Description: Mathematical functions
 ******************************************************************************/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <ostream>

// Structure for containing Fibonacci sequence
struct Fib {
	std::vector<unsigned> elems;

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

// Return the dot product of two vectors
template<class T>
T dotProduct(const std::vector<T> a, const std::vector<T> b)
{
	if (a.size() not_eq b.size()) {
		throw std::out_of_range("Dimensions do not match!");
	}

	T retVal = 0;
	for (auto i{0u}; i < a.size(); ++i) {
		retVal += a[i] * b[i];
	}
	return retVal;
}

// An N by M matrix of type T
template<class T>
struct Matrix {
	Matrix() = default;

	Matrix(const unsigned m, const unsigned n) {
		for (auto i{0u}; i < m; ++i) {
			m_matrix.push_back(std::vector<T>(n));
		}
	}

	Matrix(std::vector<std::vector<T>> arr) {
		if (arr.empty()) {
			return;
		}

		// Ensure all vectors are of same length
		auto size = arr[0].size();
		for (auto i{0u}; i < arr.size(); ++i) {
			if (arr[i].size() not_eq size) {
				throw std::invalid_argument("Malformed matrix!");
			}
			m_matrix.push_back(arr[i]);
		}
	}

	bool isEmpty() const { return m_matrix.empty(); }
	unsigned numRows() const { return m_matrix.size(); }
	unsigned numCols() const { return m_matrix[0].size(); }

	std::vector<T> row(const unsigned idx) const {
		return m_matrix[idx];
	}

	std::vector<T> col(const unsigned idx) const {
		std::vector<T> retVal(this->numRows());
		for (auto i{0u}; i < this->numRows(); ++i) {
			retVal[i] = m_matrix[i][idx];
		}
		return retVal;
	}

	void set(const unsigned x, const unsigned y, const T val) {
		m_matrix[x][y] = val;
	}

	Matrix transpose() {
		Matrix<T> retVal(this->numCols(), this->numRows());
		for (auto i{0u}; i < this->numRows(); ++i) {
			for (auto j{0u}; j < this->numCols(); ++j) {
				retVal.set(j, i, this->m_matrix[i][j]);
			}
		}

		return retVal;
	}

	// Operators for access/modification of matricies
	std::vector<T> operator[](const unsigned idx) const {
		return m_matrix[idx];
	}

	Matrix operator+(const Matrix& rhs) {
		Matrix<T> retVal(this->numRows(), this->numCols());
		for (auto i{0u}; i < this->numRows(); ++i) {
			for (auto j{0u}; j < this->numCols(); ++j) {
				retVal.set(i, j, m_matrix[i][j] + rhs[i][j]);
			}
		}
		return retVal;
	}

	Matrix operator-(const Matrix& rhs) {
		Matrix<T> retVal(this->numRows(), this->numCols());
		for (auto i{0u}; i < this->numRows(); ++i) {
			for (auto j{0u}; j < this->numCols(); ++j) {
				retVal.set(i, j, m_matrix[i][j] - rhs[i][j]);
			}
		}
		return retVal;
	}

	Matrix operator*(const T val) { // Scalar multiplication
		Matrix<T> retVal(this->numRows(), this->numCols());
		for (auto i{0u}; i < this->numRows(); ++i) {
			for (auto j{0u}; j < this->numCols(); ++j) {
				retVal.set(i, j, m_matrix[i][j] * val);
			}
		}
		return retVal;
	}

	Matrix operator*(const Matrix& rhs) { // Matrix multiplication
		if (this->isEmpty() or rhs.isEmpty()) {
			return Matrix<T>();
		}

		Matrix<T> retVal(this->numRows(), rhs.numCols());
		for (auto i{0u}; i < this->numRows(); ++i) {
			for (auto j{0u}; j < this->numCols(); ++j) {
				retVal.set(i, j, dotProduct(this->row(i),
							rhs.col(j)));
			}
		}
		return retVal;
	}

	Matrix pow(const int val) { // Non-negative powers of matricies
		if (this->numRows() not_eq this->numCols()) {
			throw std::invalid_argument("Invalid dimensions");
		}
		if (val <= 0) {
			throw std::invalid_argument("Invalid exponent");
		}

		// Generate an identity matrix
		Matrix<T> retVal(this->numRows(), this->numCols());
		for (auto i{0u}; i < this->numRows(); ++i) {
			retVal.set(i, i, 1);
		}

		// Compute and return
		for (auto i{0}; i < val; ++i) {
			retVal = retVal * *this;
		}
		return retVal;
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
		for (auto i{0u}; i < mat.numRows(); ++i) {
			for (auto j{0u}; j < mat.numCols(); ++j) {
				os << mat[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}

private:
	std::vector<std::vector<T>> m_matrix;
};

// Compute a^b mod n for large numbers
unsigned long long
powMod(
const unsigned long long a,
const unsigned long long b,
unsigned long long n)
{
	auto retVal{1ull};
	for (auto i{0ull}; i < b; ++i) {
		retVal = retVal * a % n;
	}

	return retVal;
}

// Fermat's little theorem to test for primality
// This is quicker, but may result in pseudo-primes
bool
isProbablyPrime(const unsigned long long val)
{
	// a^(p-1) congruent to 1 mod p?
	return (powMod(2, val-1, val) == 1ull ? true : false);
}

// (Currently) the only sure way to know if a number is prime
bool
isDefinitelyPrime(const unsigned long long val)
{
	auto retVal{true};
	for (auto i = static_cast<unsigned long long>(sqrtl(val)); i > 1; --i) {
		if (val % i == 0) {
			retVal = false;
			break;
		}
	}

	return retVal;
}
