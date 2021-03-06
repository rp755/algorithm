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
#define MAIN_SegmentsIntersect
#endif

#ifndef FUNC_SegmentsIntersect
#define FUNC_SegmentsIntersect

#include "utils.h"

template <typename T>
class Vector {
	public:
		Vector(): x(0), y(0) {}
		Vector(T X, T Y): x(X), y(Y) {}
		T Cross(const Vector<T>& rhs) const { return x * rhs.y - y * rhs.x; }
		T Length() const {
			return x * x + y * y; 
		}
		Vector<T> operator+(const Vector<T>& rhs) const {
			return Vector<T>(x + rhs.x, y + rhs.y); 
		}
		Vector<T> operator-(const Vector<T>& rhs) const {
			return Vector<T>(x - rhs.x, y - rhs.y); 
		}
		bool operator==(const Vector<T>& rhs) const {
			return x == rhs.x && y == rhs.y; 
		}
		friend std::ostream& operator<<(std::ostream& os, const Vector<T>& rhs){
			return os << "(" << rhs.x << ", " << rhs.y << ")"; 
		}
		T x, y; 
}; 

template <typename T>
struct VectorHash {
    std::size_t operator()(Vector<T> t) const {
	    size_t a = std::hash<T>()(t.x); 
	    size_t b = std::hash<T>()(t.y); 
	    const size_t shift = sizeof(size_t) * 4; 
	    size_t B = b >> shift | b << shift; 
	    return a ^ B; 
    }
}; 

template <typename T>
void print_seg(Vector<T>& p1, Vector<T>& p2, T n, std::string stroke) {
	std::cout << "\t<line x1=\"" << n + p1.x + 1 << "\" y1=\"" << n + p1.y + 1
			 << "\" x2=\"" << n + p2.x + 1 << "\" y2=\"" << n + p2.y + 1
			 << "\" style=\"stroke:" << stroke << ";\"/>" << std::endl; 
}

template <typename T>
bool OnSegment(const Vector<T>& i, const Vector<T>& j, const Vector<T>& k) {
	return std::min(i.x, j.x) <= k.x && k.x <= std::max(i.x, j.x) && 
			std::min(i.y, j.y) <= k.y && k.y <= std::max(i.y, j.y); 
}

template <typename T>
T Direction(const Vector<T>& i, const Vector<T>& j, const Vector<T>& k) {
	return (k - i).Cross(j - i); 
}

template <typename T>
bool SegmentsIntersect(const Vector<T>& p1, const Vector<T>& p2, 
						const Vector<T>& p3, const Vector<T>& p4) {
	T d1 = Direction(p3, p4, p1); 
	T d2 = Direction(p3, p4, p2); 
	T d3 = Direction(p1, p2, p3); 
	T d4 = Direction(p1, p2, p4); 
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && 
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true; 
	else if (d1 == 0 && OnSegment(p3, p4, p1))
		return true; 
	else if (d2 == 0 && OnSegment(p3, p4, p2))
		return true; 
	else if (d3 == 0 && OnSegment(p1, p2, p3))
		return true; 
	else if (d4 == 0 && OnSegment(p1, p2, p4))
		return true; 
	return false; 
}
#endif

#ifdef MAIN_SegmentsIntersect
int main(int argc, char *argv[]) {
	const size_t n = get_argv(argc, argv, 1, 200); 
	std::vector<int> b; 
	random_integers(b, -n, n, 8); 
	using T = double; 
	Vector<T> p1(b[0], b[1]), p2(b[2], b[3]), p3(b[4], b[5]), p4(b[6], b[7]); 
	std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>"
				 << std::endl; 
	std::cout << "<svg height=\"" << 2 * n << "\" width=\"" << 2 * n << "\">"
				 << std::endl; 
	std::cout << "\t<rect fill=\"#ffffff\" x=\"0\" y=\"0\" width=\"" << 2 * n
				 << "\" height=\"" << 2 * n << "\"/>" << std::endl; 
	print_seg(p1, p2, (T) n, "#ff0000"); 
	print_seg(p3, p4, (T) n, "#00ff00"); 
	std::cout << "\t<text x=\"" << n << "\" y=\"" << n << "\">"
				 << std::boolalpha << SegmentsIntersect(p1, p2, p3, p4)
				 << "</text>" << std::endl; 
	std::cout << "</svg>" << std::endl; 
	return 0; 
}
#endif

