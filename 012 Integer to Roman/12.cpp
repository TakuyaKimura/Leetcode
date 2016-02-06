/*

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

*/

#include <string>
using namespace std;

// 60ms
class Solution {
public:
    string intToRoman(int num) {
        int values[] { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };  // universal initialization
        string symbols[] { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
        string roman;
        int i = 0;
        while (num > 0)
        {
            if (num >= values[i])
            {
                roman += symbols[i];
                num -= values[i];
            }
            else
                ++i;
        }
        return roman;
    }
};

// 48ms
class Solution2 {
public:
    string intToRoman(int num) {
        int values[] { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };  // universal initialization
        string symbols[] { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
        string roman;
        int count, value;
        for (int i = 0; num > 0; ++i)
        {
            value = values[i];
            if (num >= value)
            {
                count = num / value;
                while (count--)
                    roman += symbols[i];
                num %= value;
            }
        }
        return roman;
    }
};

// 28ms
class Solution3 {
public:
    string intToRoman(int num) {
        int values[] { 1000, 500, 100, 50, 10, 5, 1 };  // universal initialization
        char symbols[] {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
        string roman;
        int count, value;
        for (int i = 0; num > 0; i += 2)
        {
            value = values[i];
            if (num >= value)
            {
                count = num / value;
                if (count < 4)
                    roman.append(count, symbols[i]);
                else if (count == 4)
                {
                    roman.append(1, symbols[i]);
                    roman.append(1, symbols[i - 1]);
                }
                else if (count == 9)
                {
                    roman.append(1, symbols[i]);
                    roman.append(1, symbols[i - 2]);
                }
                else
                {
                    roman.append(1, symbols[i - 1]);
                    roman.append(count - 5, symbols[i]);
                }
                num %= value;
            }
        }
        return roman;
    }
};

// 36ms
class Solution4 {
public:
    string intToRoman(int num) {
        string digits[] {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM", "", "M", "MM", "MMM"};
        return digits[num / 1000 + 30] + digits[num / 100 % 10 + 20] + digits[num / 10 % 10 + 10] + digits[num % 10];
    }
};

// 32ms
class Solution5 {
public:
    string intToRoman(int num) {
        if (num >= 1000) return "M" + intToRoman(num - 1000);
        if (num >= 900) return "CM" + intToRoman(num - 900);
        if (num >= 500) return "D" + intToRoman(num - 500);
        if (num >= 400) return "CD" + intToRoman(num - 400);
        if (num >= 100) return "C" + intToRoman(num - 100);
        if (num >= 90) return "XC" + intToRoman(num - 90);
        if (num >= 50) return "L" + intToRoman(num - 50);
        if (num >= 40) return "XL" + intToRoman(num - 40);
        if (num >= 10) return "X" + intToRoman(num - 10);
        if (num >= 9) return "IX" + intToRoman(num - 9);
        if (num >= 5) return "V" + intToRoman(num - 5);
        if (num >= 4) return "IV" + intToRoman(num - 4);
        if (num >= 1) return "I" + intToRoman(num - 1);
        return "";
    }
};

// 44ms
class Solution6 {
public:
    string intToRoman(int num) {
        string M[] = { "", "M", "MM", "MMM" };
        string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
        string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
        string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
        return M[num / 1000] + C[num % 1000 / 100] + X[num % 100 / 10] + I[num % 10];
    }
};