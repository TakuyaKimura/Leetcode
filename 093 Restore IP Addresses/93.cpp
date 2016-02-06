/*

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

*/

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        string address;
        restore(result, s, address, 0, 0, s.length());
        return result;
    }
private:
    void restore(vector<string>& result, string s, string address, int part, int start, int n) {
        if (start == n && part == 4)
        {
            address.pop_back();
            result.push_back(address);
        }
        if (start == n || part == 4)
            return;
        for (int num = 0, i = start; i < start + 3 && i < n; ++i)
        {
            num = num * 10 + s[i] - '0';
            if (num <= 255)
            {
                address += s[i];
                restore(result, s, address + '.', part + 1, i + 1, n);
            }
            if (num == 0)
                break;
        }
    }
};

class Solution2 {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        string ip; // save temporary result in processing
        dfs(s, 0, 0, ip, result);
        return result;
    }

    /**
    * @brief: split the string
    * @param[in] s string£¬input
    * @param[in] startIndex, start from which index in s
    * @param[in] step current step index£¬start from 0£¬valid values: 0,1,2,3,4, as special, 4 means ending of split
    * @param[out] intermediate, split result in current spliting process
    * @param[out] result, save all possible IP address
    * @return none
    */
    void dfs(string s, size_t start, size_t step, string ip, vector<string>& result) {
        if (start == s.size() && step == 4)  // found a possible result
        {
            ip.resize(ip.size() - 1);  // strip the last '.'
            result.push_back(ip);
            return;
        }

        // since each part of IP address is in 0...255, the length will not be more than 3, and not less than 1 as well.
        if (s.size() - start > (4 - step) * 3)
            return;  // optimize, the length of rest part of s string should not be more than 3 * remaining step count. 
        if (s.size() - start < (4 - step))
            return;  // optimize, the length of rest part of s string should not be less than 1 * remaining step count. 

        int num = 0;
        for (size_t i = start; i < start + 3 && i < s.size(); ++i) 
        {
            num = num * 10 + (s[i] - '0');

            if (num <= 255)
            {
                ip += s[i];
                dfs(s, i + 1, step + 1, ip + '.', result);  // current split is valid, go to next recursion
            }
            if (num == 0)  // single 0 is allowed, but '0X' is not
                break;
        }
    }
};
3 {
public:
    vector<string> restoreIpAddress(string s) {
        vector<string> res;
        size_t len = s.size();
        if (len > 12 || len < 4)
            return res;
        string first, second, third, fourth;
        // i, j, k are the lengths of each substring
        for (size_t i = 1; i < 4 && i < len - 2; ++i)
        {
            first = s.substr(0, i);
            if (!isValid(first))
                continue;
            for (size_t j = 1; j < 4 && i + j < len - 1; ++j)
            {
                second = s.substr(i, j);
                if (!isValid(second))
                    continue;
                for (size_t k = 1; k < 4 && i + j + k < len; ++k)
                {
                    third = s.substr(i + j, k);
                    fourth = s.substr(i + j + k);
                    if (isValid(third) && isValid(fourth))
                        res.push_back(first + "." + second + "." + third + "." + fourth);
                }
            }
        }
        return res;
    }
private:
    bool isValid(string s) {
        if (s[0] == '0' && s.size() > 1)
            return false;
        if (stoi(s) <= 255)
            return true;
        return false;
    }
};

int main()
{
    Solution s;
    s.restoreIpAddresses("1234");
}