/*

Validate if a given string is numeric.

Some examples:
    "0" => true
    " 0.1 " => true
    "abc" => false
    "1 a" => false
    "2e10" => true

Note: It is intended for the problem statement to be ambiguous. 
You should gather all requirements up front before implementing one.

*/

#include <string>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
		int n = s.length(), i = 0, numDigits = 0, numDots = 0;

        // skip whitespaces
		for (; i < n && isspace(s[i]); ++i) {}

        // check the significand
        if (i < n && (s[i] == '+' || s[i] == '-'))
            ++i;  // skip the sign if exist

		for (; i < n && (isdigit(s[i]) || s[i] == '.'); ++i)
			s[i] == '.' ? ++numDots : ++numDigits;

		if (numDots > 1 || numDigits < 1) // no more than one point, at least one digit
            return false;

        // check the exponent if exist
        if (i < n && s[i] == 'e')
        {
            ++i;
            if (i < n && (s[i] == '+' || s[i] == '-'))
                ++i;  // skip the sign

			for (numDigits = 0; i < n && isdigit(s[i]); ++i, ++numDigits) {}

			if (numDigits < 1)
                return false;
        }

        // skip trailing whitespaces
		for (; i < n && isspace(s[i]); ++i) {}

        return i == n;
    }
};

// add an additional character at the end to skip all the bounds checking
class Solution2 {
public:
	bool isNumber(string s) {
		int n = s.length(), i = 0, numDigits = 0, numDots = 0;
		s.push_back('*');

		// skip whitespaces
		for (; isspace(s[i]); ++i) {}

		// check the significand
		if (s[i] == '+' || s[i] == '-')
			++i;  // skip the sign if exist

		for (; isdigit(s[i]) || s[i] == '.'; ++i)
			s[i] == '.' ? ++numDots : ++numDigits;

		if (numDots > 1 || numDigits < 1) // no more than one point, at least one digit
			return false;

		// check the exponent if exist
		if (s[i] == 'e')
		{
			++i;
			if (s[i] == '+' || s[i] == '-')
				++i;  // skip the sign

			for (numDigits = 0; isdigit(s[i]); ++i, ++numDigits) {}

			if (numDigits < 1)
				return false;
		}

		// skip trailing whitespaces
		for (; isspace(s[i]); ++i) {}

		return i == n;
	}
};

// DFA
// see the pic in the folder
class Solution3 {
public:
    bool isNumber(string s) {
        int state = 0, flag = 0;        // flag for special case "."
        while (!s.empty() && isspace(s[0]))
            s.erase(0, 1);              // delete heading whitespace 
        while (!s.empty() && isspace(s[s.length() - 1]))
            s.erase(s.length() - 1, 1); // delete trailing whitespace
        for (char c : s)
        {
            if (isdigit(c))
            {
                flag = 1;
                if (state <= 2)
                    state = 2;
                else
                    state = (state <= 5) ? 5 : 7;
            }
            else if ('+' == c || '-' == c)
                if (state == 0 || state == 3)
                    ++state;
                else
                    return false;
            
            else if ('.' == c)
                if (state <= 2)
                    state = 6;
                else
                    return false;
            
            else if ('e' == c)
                if (flag && (state == 2 || state == 6 || state == 7))
                    state = 3;
                else
                    return false;
            
            else
                return false;
        }
        return (state == 2 || state == 5 || (flag && state == 6) || state == 7);
    }
};