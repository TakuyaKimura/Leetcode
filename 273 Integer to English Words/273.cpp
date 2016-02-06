/*

Convert a non-negative integer to its english words representation. 

Given input is guaranteed to be less than 231 - 1.

For example,
    123 -> "One Hundred Twenty Three"
    12345 -> "Twelve Thousand Three Hundred Forty Five"
    1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Hint:
Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.

Group the number by thousands (3 digits). 
You can write a helper function that takes a number less than 1000 and convert just that chunk to words.

There are many edge cases. What are some good test cases? 
Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)

*/

#include <string>
using namespace std;

class Solution {
public:
    string numberToWords(int num) {
        if (num == 0)
            return "Zero";
        string result;
        for (int x = 1000000000, i = 4; num; x /= 1000, --i)
        {
            if (num >= x)
            {
                int threeDigits = num / x;
                result += convertThreeDigits(threeDigits) + thousands[i];
                num %= x;
            }
        }
        result.pop_back();
        return result;
    }

private:
    string thousands[5] {"Hundred ", "", "Thousand ", "Million ", "Billion "};

    string tens[10] {"", "", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety "};

    string ones[20] {"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ", "Ten ",
        "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};

    string convertThreeDigits(int num) {
        string result;
        if (num >= 100)
        {
            result += ones[num / 100] + thousands[0];
            num %= 100;
        }
        if (num >= 20)
        {
            result += tens[num / 10];
            num %= 10;
        }
        result += ones[num];
        return result;
    }
};