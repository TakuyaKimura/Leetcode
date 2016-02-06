/*

Determine whether an integer is a palindrome. Do this without extra space.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", 
you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.

*/

// reverse the right half, while truncating the left half, then compare
class Solution {
public:
    bool isPalindrome(int x) {
        if (x && x % 10 == 0)  // numbers ending with 0 (except 0) are not palindromic
            return false;
        int rhr = 0;
        // negative numbers are not palindromic
        for (; rhr < x; x /= 10)
            rhr = rhr * 10 + x % 10;
        return rhr == x || rhr / 10 == x;
    }
};