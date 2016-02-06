/*

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

For example:

Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?

Hint:
A naive implementation of the above process is trivial. Could you come up with other methods?
What are all the possible results?
How do they occur, periodically or randomly?
You may find this Wikipedia article useful. https://en.wikipedia.org/wiki/Digital_root

*/

// digital root (dr)
// casting out nines

// ABC
// = 100A + 10B + 1C
// = (99 + 1)A + (9 + 1)B + 1C
// = 99A + 9B + (A + B + C)
// = 9M + (A + B + C)

// if the sum of A + B + C still has more than one digits, we can do the same thing
// finally, the one digit left is the remainder of mod 9
// note: if the remainder is 0, we should return 9 instead

class Solution {
public:
    int addDigits(int num) {
        int remainder = num % 9;
        if (num == 0 || remainder != 0)
            return remainder;
        return 9;
    }
};

class Solution2 {
public:
    int addDigits(int num) {
        return num - (num - 1) / 9 * 9;
    }
};

class Solution3 {
public:
    int addDigits(int num) {
        return 1 + (num - 1) % 9;
    }
};

// naive method
class Solution4 {
public:
    int addDigits(int num) {
        int sum, digit;
        while (num > 9)
        {
            sum = 0;
            while (num)
            {
                digit = num % 10;
                sum += digit;
                num /= 10;
            }
            num = sum;
        }
        return num;
    }
};