/*

The set [1,2,3,бн,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):
    1. "123"
    2. "132"
    3. "213"
    4. "231"
    5. "312"
    6. "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

*/

#include <string>
#include <vector>
using namespace std;

// O(n^2) time
class Solution {
public:
    string getPermutation(int n, int k) {
        int factorial = 1, idx;
        for (int i = 2; i <= n; ++i)
            factorial *= i;
        if (k < 1 || k > factorial)
            return "";

        string nums(n, '1'), result(n, ' ');
        for (int i = 1; i < n; ++i)
            nums[i] += i;

        --k;  // k starts from 1, so have to substract 1
        for (int i = 0; i < n; ++i)
        {
            factorial /= n - i;
            idx = k / factorial;  // each group has factorial permutations
            result[i] = nums[idx];
            nums.erase(idx, 1);  // O(n)
            k %= factorial;
        }
        return result;
    }
};

// O(n^2) time, by swapping and keeping the result in order
class Solution2 {
public:
    string getPermutation(int n, int k) {
        int factorial = 1;
        for (int i = 2; i <= n; ++i)
            factorial *= i;
        if (k < 1 || k > factorial)
            return "";

        string result(n, '1');
        for (int i = 1; i < n; ++i)
            result[i] += i;

        for (int i = 0; i < n; ++i)  // or i < n - 1
        {
            factorial /= n - i;  // this is the group size
            for (int j = i + 1; k > factorial; ++j)  // if k > group size, means it's in the next group
            {
                k -= factorial;
                swap(result[i], result[j]);
            }
        }
        return result;
    }
};