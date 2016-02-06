/*

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

*/

#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// Definition for a point.
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

// In order to avoid using double type (the slope k) as map key
// used pair(int a, int b) as key, where a = pj.x - pi.x, b = pj.y - pi.y, and k = b / a
// Using greatest common divisor ensures that lines with the same slope have the same key

// use map instead of unordered_map
// there is no specialization for std::tr1::hash<Key> with Key = std::pair<int, int>
// one must specialize std::tr1::hash<Key> with Key = std::pair<int, int> before declaring tr1::unordered_map<Pair,int>
// this happens because std don't know how to hash a pair<int, int>

class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int n = points.size(), result = 0, localmax, overlap, a, b, gcd;
        Point pi, pj;

        // for each point, compare it with all the points after it
        for (int i = 0; i < n; ++i)
        {
            pi = points[i];
			map<pair<int, int>, int> lines;
            localmax = overlap = 0;

            for (int j = i + 1; j < n; ++j)
            {
                pj = points[j];
                if (pj.x == pi.x && pj.y == pi.y)
                    ++overlap;
                else
                {
                    a = pj.x - pi.x;  // could also use pi.x - pj.x, because e.g. a,b = 6,-4 and -6,4 are the same -> 3,-2
                    b = pj.y - pi.y;
                    gcd = GCD(a, b);

                    a /= gcd;
                    b /= gcd;

                    ++lines[make_pair(a, b)];
                }
            }

			for (auto& line : lines)
				localmax = max(localmax, line.second);

            result = max(result, localmax + overlap + 1);  // plus point i itself
        }

        return result;
    }

private:
    // Euclidean algorithm, or Euclid's algorithm
    
    int GCD(int a, int b) {
        if (b == 0)
            return a;
        return GCD(b, a % b);
    }

    //int GCD(int a, int b) {
    //    int temp;
    //    while (b)
    //    {
    //        temp = b;
    //        b = a % b;
    //        a = temp;
    //    }
    //    return a;
    //}
};