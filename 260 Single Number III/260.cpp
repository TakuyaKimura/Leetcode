/*

Given an array of numbers nums, in which exactly two elements appear only once 
and all the other elements appear exactly twice. 

Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

*/

#include <vector>
#include <numeric>     // or <algorithm>, for accumulate(first, last, initial value, binary operator)
#include <functional>  // for bit_xor
#include <unordered_set>
using namespace std;

/**
    All the bits that are set in xor will be set in one non-repeating element (x or y) and not in other. 
    So if we take any set bit of xor and divide the elements of the array in two sets ¨C 
    one set of elements with same bit set and other set with same bit not set. 
    By doing so, we will get x in one set and y in another set. 
    Now if we do XOR of all the elements in first set, we will get first non-repeating element, 
    and by doing same in other set we will get the second non-repeating element.

    Let us see an example.
    nums = {2, 4, 7, 9, 2, 4}
    1) Get the XOR of all the elements.
       xor = 2^4^7^9^2^4 = 14 (1110)
    2) Get a number which has only one set bit of the xor.
       Since we can easily get the rightmost set bit, let us use it.
       set_bit_no = xor & -xor = (1110) & (0001 + 1) = 1110 & 0010 = 0010
          - Note: two's complement: bits are inverted (~), then add 1
                  -INT_MIN == INT_MIN
       Now set_bit_no will have only set as rightmost set bit of xor.
    3) Now divide the elements in two sets and do xor of
       elements in each set, and we get the non-repeating
       elements 7 and 9. Please see implementation for this step.
*/

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> result(2, 0);

        //int x = 0;
        //for (auto num : nums)
        //    x ^= num;
        int x = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());

        // get the rightmost set bit
        x &= -x;
        for (auto num : nums)
            //if (num & x)  // that bit is set
            //    result[0] ^= num;
            //else          // that bit is not set
            //    result[1] ^= num;
            result[!(num & x)] ^= num;  // result[(num & x) == 0]

        return result;
    }
};

class Solution2 {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_set<int> hash;
        for (auto num : nums)
            if (hash.find(num) != hash.end())
                hash.erase(num);
            else
                hash.insert(num);
        return vector<int>(hash.begin(), hash.end());
    }
};