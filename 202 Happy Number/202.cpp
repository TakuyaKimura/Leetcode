/*

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: 
    Starting with any positive integer, 
    replace the number by the sum of the squares of its digits, 
    and repeat the process until the number equals 1 (where it will stay), 
    or it loops endlessly in a cycle which does not include 1. 
    Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

    1^2 + 9^2 = 82
    8^2 + 2^2 = 68
    6^2 + 8^2 = 100
    1^2 + 0^2 + 0^2 = 1

*/

// if n is not happy, its sequence ends in a cycle
// 4, 16, 37, 58, 89, 145, 42, 20, 4, ...
// use Floyd's cycle detection algorithm

// if n has m digits, then the sum of the squares of its digits is at most 81m
// for m>=4, n >= 10^(m-1) > 81m
// so any number over 1000 gets smaller under this process and in particular becomes a number with strictly fewer digits
// Once we are under 1000, the number for which the sum of squares of digits is largest is 999, and the result is 243
// In the range 100 to 243, the number 199 produces the largest next value, of 163
// In the range 100 to 163, the number 159 produces the largest next value, of 107
// In the range 100 to 107, the number 107 produces the largest next value, of 50
// Considering more precisely the intervals [244,999], [164,243], [108,163] and [100,107]
// we see that every number above 99 gets strictly smaller under this process

// Thus, no matter what number we start with, we eventually drop below 100
// An exhaustive search then shows that every number in the interval [1,99] either is happy or goes to the above cycle

class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = digitSquareSum(slow);
            fast = digitSquareSum(digitSquareSum(fast));
        } while (slow != fast);

        return slow == 1;
    }
private:
    int digitSquareSum(int n) {
        int sum = 0, digit;
        while (n)
        {
            digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
};