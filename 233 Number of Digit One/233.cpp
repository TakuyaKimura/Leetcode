/*

Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

Hint:
Beware of overflow.

*/

/**
    Go through the digit positions one at a time, find out how often a "1" appears at each position, and sum those up
    for example n=3141592 
    when we're at m=100 for analyzing the hundreds-digit
    we know that the hundreds-digit of n is 1 for prefixes "" to "3141", i.e., 3142 times
    each of those times is a streak
    each streak is 100 long, so 3142 * 100 times, the hundreds-digit is 1

    Consider the thousands-digit, i.e., when m=1000
    The thousands-digit is 1 for prefixes "" to "314", so 315 times
    each time is a streak of 1000 numbers 
    However, since the thousands-digit is a 1, the very last streak isn't 1000 numbers
    but only 593 numbers, for the suffixes "000" to "592". So (314 * 1000) + (592 + 1) times

    The case distincton between the current digit/position being 0, 1 and >=2 can easily be done in one expression
    With (a + 8) / 10 you get the number of full streaks, and a % 10 == 1 tells you whether to add a partial streak
*/

class Solution {
public:
    int countDigitOne(int n) {
        int digit, suffix, k = 1, ones = 0;
        for (int prefix = n; prefix > 0; k *= 10)
        {
            digit = prefix % 10;
            prefix /= 10;
            suffix = n % k;
            if (digit == 0)
                ones += prefix * k;
            else if (digit == 1)
                ones += prefix * k + suffix + 1;
            else
                ones += (prefix + 1) * k;
        }
        return ones;
    }
};

class Solution2 {
public:
    int countDigitOne(int n) {
        int ones = 0;
        for (long long m = 1; m <= n; m *= 10)
            ones += (n / m + 8) / 10 * m + (n / m % 10 == 1) * (n % m + 1);
        return ones;
    }
};

class Solution3 {
public:
    int countDigitOne(int n) {
        int ones = 0, prefix;
        for (int m = 1; m <= n; m *= 10)
        {
            prefix = n / m;
            ones += (prefix + 8) / 10 * m + (prefix % 10 == 1) * (n % m + 1);
            if (m == 1000000000)
                break;
        }
        return ones;
    }
};