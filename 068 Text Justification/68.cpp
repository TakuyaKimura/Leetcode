/*

Given an array of words and a length L, format the text 
such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. 
Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. 
If the number of spaces on a line do not divide evenly between words, 
the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
    [
        "This    is    an",
        "example  of text",
        "justification.  "
    ]

Note: Each word is guaranteed not to exceed L in length.

Corner Cases:
A line other than the last line might contain only one word. What should you do in this case?
In this case, that line should be left-justified.

*/

#include <vector>
#include <string>
using namespace std;

// the question asks for a greedy algorithm
// for each line, words[i] through words[i+k-1] could fit in
// the first (maxWidth-w) % (k-1) gaps require an additional space
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int n = words.size();
        for (int i = 0, k, w; i < n; i += k)
        {
            // k is number of words fit in current line, w is current width
            for (k = w = 0; i + k < n && w + words[i + k].length() <= maxWidth - k; ++k)
                w += words[i + k].length();
            
            string tmp = words[i];
            for (int j = 0; j < k - 1; ++j)  // jth gap
            {
                if (i + k == n)
                    tmp += " ";  // last line, left justified
                else
                    tmp += string((maxWidth - w) / (k - 1) + (j < (maxWidth - w) % (k - 1)), ' ');
                tmp += words[i + j + 1];
            }
            tmp += string(maxWidth - tmp.length(), ' ');  // if only word on this line
            res.push_back(tmp);
        }
        return res;
    }
};

class Solution2 {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		int n = words.size(), start, len, num, space, i, gap;
		vector<string> result;
		for (start = 0; start < n; start += num)
		{
			string str;
			for (i = start, len = -1, num = 0; i < n && len + 1 + words[i].length() <= maxWidth; ++i, ++num)
				len += 1 + words[i].length();

			len = maxWidth - len;  // how many left
			if (i == n || num == 1)
			{
				str = string(len, ' ');
				len = 0;
			}

			str = words[--i] + str;  // put the last word first, then left with same number of words and gaps
			gap = num - 1;
			len += gap;              // total num of spaces left

			while (gap)
			{
				space = len / gap--;
				str = words[--i] + string(space, ' ') + str;
				len -= space;
			}

			result.push_back(str);
		}

		return result;
	}
};