/*

Implement int sqrt(int x).

Compute and return the square root of x.

*/

#include <cmath>  // fabs - absolute value for doubles and floats

class Solution {
public:
    int mySqrt(int x) {
        int low = 1, high = x, mid, target;
        while (low <= high)
        {
            mid = low + (high - low) / 2;  // (low + high) / 2 will overflow
            target = x / mid;              // mid * mid will overflow
            if (mid == target)
                return mid;
            if (mid < target)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return high;
    }
};

class Solution2 {
public:
    int mySqrt(int x) {
        int low = 1, high = x, mid;
        long long square;
        while (low <= high)
        {
            mid = low + (high - low) / 2;
            square = static_cast<long long>(mid)* mid;  // long long is 64-bit, cast before calculation
            if (square == x)
                return mid;
            if (square < x)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return high;
    }
};

// Newton's method
// tangent line to the curve y = f(x) at the point x=xn is  y = f'(xn)(x - xn) + f(xn)
// next guess is the x-intercept of the tangent line        xn+1 = xn - f(xn)/f'(xn)

// x^2 = square
// f(x) = x^2 - square
// f'(x) = 2x
// next guess = current guess - (cur^2 - square) / 2 * cur
//            = (cur + square / cur) / 2

class Solution3 {
public:
    int sqrt(int x) {
        double guess = double(x) / 2, delta = 0.0001;
        while (fabs(guess * guess - x) > delta)
            guess = (guess + x / guess) / 2;
        return guess;
    }
};

/*
    bit manipulation

    Since sqrt(x) is composed of binary bits, 
    calculate sqrt(x) by deciding every bit from the most significant to least significant. 
    Since an integer n can have O(log n) bits with each bit decided within constant time, 
    this algorithm has time limit O(log n), 
    actually, because an Integer can have at most 32 bits, we can also say this algorithm takes O(32) = O(1) time.

    Furthermore, sqrt of 2147483647 is 46340, which has only 16 bits
*/
class Solution4 {
public:
    int sqrt(int x) {
        long long ans = 0;
        int bit = 1 << 16;  // long long bit = 1ll << 16;
        while (bit > 0)
        {
            ans |= bit;      // set the bit
            if (ans * ans > x)
                ans ^= bit;  // unset the bit
            bit >>= 1;
        }
        return ans;
    }
};