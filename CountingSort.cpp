//  
//  algorithm - some algorithms in "Introduction to Algorithms", third edition
//  Copyright (C) 2018  lxylxy123456
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as
//  published by the Free Software Foundation, either version 3 of the
//  License, or (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  

#ifndef MAIN
#define MAIN
#define MAIN_CountingSort
#endif

#ifndef FUNC_CountingSort
#define FUNC_CountingSort

#include "utils.h"

template <typename T>
inline size_t Self(T x) {
	return x; 
}

template <typename T, typename Predicate>
void CountingSort(std::vector<T>& A, std::vector<T>& B, size_t k, Predicate f) {
	// for i in A: i in range(k); T must be int-like
	std::vector<size_t> C(k, 0); 
	for (typename std::vector<T>::iterator i = A.begin(); i != A.end(); i++)
		C[f(*i)]++; 
	for (typename std::vector<size_t>::iterator i = C.begin() + 1; 
		i != C.end(); i++)
		*i += *(i - 1); 
	for (typename std::vector<T>::reverse_iterator i = A.rbegin(); 
		i < A.rend(); i++)
		B[--C[f(*i)]] = *i; 
}
#endif

#ifdef MAIN_CountingSort

#include "InsertSort.cpp"

int main(int argc, char *argv[]) {
	std::vector<int> a; 
	const size_t n = get_argv(argc, argv, 1, 10); 
	const int k = get_argv(argc, argv, 2, n); 
	const size_t compute = get_argv(argc, argv, 3, 3); 
	random_integers(a, 0, k - 1, n); 
	std::vector<int> b(a), c(n, 0); 
	if (compute >> 0 & 1) {
		InsertSort(a); 
		output_integers(a); 
	}
	if (compute >> 1 & 1) {
		CountingSort(b, c, k, Self<int>); 
		output_integers(c); 
		if (compute >> 0 & 1)
			std::cout << std::boolalpha << (a == c) << std::endl; 
	}
	return 0; 
}
#endif

