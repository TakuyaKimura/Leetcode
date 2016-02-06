/*

Given a string of numbers and operators, return all possible results 
from computing all the different possible ways to group numbers and operators. 

The valid operators are +, - and *.

Example 1
    Input: "2-1-1".

    ((2-1)-1) = 0
    (2-(1-1)) = 2

    Output: [0, 2]


Example 2
    Input: "2*3-4*5"

    (2*(3-(4*5))) = -34
    ((2*3)-(4*5)) = -14
    ((2*(3-4))*5) = -10
    (2*((3-4)*5)) = -10
    (((2*3)-4)*5) = 10

    Output: [-34, -14, -10, -10, 10]

*/

#include <vector>
#include <string>
#include <sstream>
using namespace std;

// DP, each operator is a tree node, see problem 95 unique binary search trees
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        istringstream ss(input + "+");
        int num;
        char op;
        vector<int> nums;
        vector<char> ops;
        while (ss >> num && ss >> op)
        {
            nums.push_back(num);
            ops.push_back(op);
        }
        int size = nums.size(), i, j, k;
        vector<vector<vector<int>>> dp(size, vector<vector<int>>(size, vector<int>()));
        for (i = 0; i < size; ++i)
            dp[i][i].push_back(nums[i]);
        for (i = size - 2; i >= 0; --i)
            for (j = i + 1; j < size; ++j)
                for (k = i; k < j; ++k)
                    for (auto left : dp[i][k])
                        for (auto right : dp[k + 1][j])
                            dp[i][j].push_back(ops[k] == '+' ? left + right : ops[k] == '-' ? left - right : left * right);
        return dp[0][size - 1];
    }
};

class Solution2 {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> data;
        vector<char> ops;
        int num;
        char op;
        istringstream ss(input + "+");
        while (ss >> num && ss >> op)
        {
            data.push_back(num);
            ops.push_back(op);
        }
        const int size_i = data.size();  // this is one more than num of operators
        int i, j, k;
        vector<vector<vector<int>>> dp(size_i, vector<vector<int>>(size_i, vector<int>()));  // use data as indices

        for (i = 0; i < size_i; ++i)
            dp[i][i].push_back(data[i]);

        for (i = 1; i < size_i; ++i)      // last data    // or the first data starts from the back
            for (j = i - 1; j >= 0; --j)  // first data
                for (k = j; k < i; ++k)   // operator
                    for (auto left : dp[j][k])
                        for (auto right : dp[k + 1][i])
                            dp[j][i].push_back(ops[k] == '+' ? left + right : ops[k] == '-' ? left - right : left * right);
                            //switch (ops[k])
                            //{
                            //    case '+':
                            //        dp[j][i].push_back(left + right);
                            //        break;
                            //    case '-':
                            //        dp[j][i].push_back(left - right);
                            //        break;
                            //    case '*':
                            //        dp[j][i].push_back(left * right);
                            //        break;
                            //    default:
                            //        break;
                            //}
        return dp[0][size_i - 1];
    }
};

// recursive, divide-and-conquer
class Solution3 {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> output;
        int last = input.size() - 1;
        char op;
        for (int i = 1; i < last; ++i)
            if (ispunct(op = input[i]))
                for (int a : diffWaysToCompute(input.substr(0, i)))
                    for (int b : diffWaysToCompute(input.substr(i + 1)))
                        output.push_back(op == '+' ? a + b : op == '-' ? a - b : a * b);
        return output.empty() ? vector<int>{ stoi(input) } : output;
    }
};