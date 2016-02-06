/*

Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

Spoilers:

Have you thought about this?
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.

Did you notice that the reversed integer might overflow? 
Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

*/

#include <climits>

// the reversed integer might overflow
// Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows

// -123 / 10 = -12, -123 % 10 = -3

class Solution {
public:
    int reverse(int x) {
        long long result = 0;
        while (x)
        {
            result = result * 10 + x % 10;
            x /= 10;
        }
        return result > INT_MAX || result < INT_MIN ? 0 : result;
    }
};

// faster, before multiply by 10 check if result is > INT_MAX / 10 or < INT_MIN / 10
// if result ==  INT_MAX / 10, it's still safe because the next digits could only be 1 (2147483641 < 2147483647)
// because the original number 1463847412 < 2147483647 < 2463847412
//                            -1463847412 > -2147483648 < -2463847412
class Solution2 {
public:
    int reverse(int x) {
        int result = 0;
        while (x)
        {
            if (result > 214748364 || result < -214748364)
                return 0;
            result = result * 10 + x % 10;
            x /= 10;
        }
        return result;
    }
};