/*

Given an integer, write a function to determine if it is a power of three.

Follow up:
Could you do it without using any loop / recursion?

*/

#include <cmath>

class Solution {
public:
	bool isPowerOfThree(int n) {
		return n && n == pow(3, int(log(n) / log(3) + 0.5));  // round, not floor
	}
};