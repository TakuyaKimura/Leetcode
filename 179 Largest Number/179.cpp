/*

Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

*/

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

/**
    According to requirements to a comparator, this relationship has to be a total order.
    How can we prove that? How to reasonably justify that it will be a transitive relationship as required by Comparator contract?

    Let A, B, C be the integers given.
    To concatenate A and B into AB, we need to know how many digits are there in B,
    then multiply power of 10 with A, add B to the result.
    Example: 12312 = 123 * 100 + 12.
    The number of digits in B is lgB + 1, therefore we need to multiply A with 10^(lgB + 1), then add the result with B to get AB.
    Now we can start our proof.

    Proof:
    Let us define f(X) = 10^(lgX + 1), then XY = f(Y)X + Y

    If AB <= BA, then we have
    f(B)A + B <= f(A)B + A
    (f(B) - 1)A <= (f(A) - 1)B
    that is
    A <= B¡¤(f(A) - 1) / (f(B) - 1)   (1)

    If BC <= CB, then we have
    f(C)B + C <= f(B)C + B
    (f(C) - 1)B <= (f(B) - 1)C
    that is
    B <= C¡¤(f(B) - 1) / (f(C) - 1)   (2)

    Combine (1), (2), we have
    A <= C¡¤(f(A) - 1) / (f(C) - 1)
    (f(C) - 1)A <= (f(A) - 1)C
    f(C)A + C <= f(A)C + A
    AC <= CA
*/

// we are trying to pass a pointer to a member function
// so we need to change the function to be static

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string> strs(n);
        for (int i = 0; i < n; ++i)
            strs[i] = to_string(nums[i]);
        sort(strs.begin(), strs.end(), compareSort);
        if (strs.empty() || strs[0] == "0")
            return "0";
        stringstream ss;
        for (auto& str : strs)
            ss << str;
        return ss.str();
    }
private:
    static bool compareSort(const string& s1, const string& s2) {
        return s1 + s2 > s2 + s1;
    }
};

// same as above, just write as lambda function
class Solution2 {
public:
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string> strs(n);
        for (int i = 0; i < n; ++i)
            strs[i] = to_string(nums[i]);
        sort(begin(strs), end(strs), [](const string &s1, const string &s2){ return s1 + s2 > s2 + s1; });  // only difference
        if (strs.empty() || strs[0] == "0")
            return "0";
        stringstream ss;
        for (auto& str : strs)
            ss << str;
        return ss.str();
    }
};

// 4ms
class Solution3 {
public:
    string largestNumber(vector<int>& nums) {
        int lens = nums.size(), i;
        vector<string> str(lens);
        for (i = 0; i < lens; ++i)
            str[i] = to_string(nums[i]);
        sort(str.begin(), str.end(), cmp);
        string result;
        for (i = 0; i < lens; ++i)
            result += str[i];
        if (result.empty() || result[0] == '0')
            return "0";
        return result;
    }
private:
    static bool cmp(const string& A, const string& B)
    {
        int a = A.size(), b = B.size(), i;
        if (a == b)
            return A > B;
        for (i = 0; i < a && i < b; ++i)
            if (A[i] != B[i])
                return A[i] > B[i];
        if (i == a)
            return cmp(A, B.substr(i));  // we are actually comparing A+B vs B+A, but without copying and concatenating, so faster!
                                         // 123 | 123   123   12   3   12   <- after removing 123 from both fronts, we know what's been left starts with 123, so we use 123 to match
                                         // 123   123   123   12 | 12   3   <- the trailing 12 is the prefix of A
                                         // 123 vs 12312312312 => 123 vs 12 => 3 vs 12
        else
            return cmp(A.substr(i), B);
    }
};