/*

Given an array of citations (each citation is a non-negative integer) of a researcher, 
write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: 
"A scientist has index h if h of his/her N papers have at least h citations each, 
and the other N - h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], 
which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. 
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, 
his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.

Hint:
An easy approach is to sort the array first.
What are the possible values of h-index?
A faster approach is to use extra space.

*/

#include <vector>
#include <algorithm>
using namespace std;

// O(nlogn)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int n = citations.size(), i;
        for (i = 0; i < n; ++i)
            if (citations[i] >= n - i)
                break;
        return n - i;
    }
};

// O(n)
class Solution2 {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> count(n + 1, 0);

        for (int citation : citations)
            if (citation > n)
                ++count[n];
            else
                ++count[citation];

        for (int citation = n, sum = 0; citation >= 0; --citation)
        {
            sum += count[citation];
            if (sum >= citation)
                return citation;
        }
    }
};