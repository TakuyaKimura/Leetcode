/*

You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s 
that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

*/

#include <vector>
#include <string>
#include <unordered_map>
#include <random>  // uniform_real_distribution<double> and default_random_engine
#include <unordered_set>
#include <algorithm>  // for_each
using namespace std;

// O(kn), where k = word length, n = s.length(), 48ms
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> result;
		unordered_map<string, int> need;
		for (string& word : words)
			++need[word];

		int numWords = words.size(), len = numWords ? words[0].length() : 0, totalLen = s.length();

		// if each word is 3 characters long, we only need 3 iterations
		// 0, 3, 6, ...
		// 1, 4, 7, ...
		// 2, 5, 8, ...
		for (int i = 0; i < len; ++i)
		{
			unordered_map<string, int> used;
			int numMatch = 0, start = i;
			for (int j = i; j < totalLen; j += len)
			{
				string word = s.substr(j, len);
				if (need.find(word) != need.end())
				{
					++used[word];
					++numMatch;
					while (used[word] > need[word])  // matched one more word
					{
						// if word w is matched one more
						// remove the first occurence, including the words before it
						--used[s.substr(start, len)];
						--numMatch;
						start += len;
					}

					if (numMatch == numWords)
						result.push_back(start);
				}

				else  // not a match
				{
					start = j + len;  // restart from after j
					used.clear();
					numMatch = 0;
				}
			}
		}

		return result;
	}
};

// 24ms
class Solution2 {
	// The general idea:
	// Construct a hash function f for "words", f: vector<string> -> int, 
	// Then use the return value of f to check whether a substring is a concatenation 
	// of all words in "words".
	// f has two levels, the first level is a hash function f1 for every single word in "words".
	// f1 : string -> double
	// So with f1, "words" is converted into a vector of float numbers
	// Then another hash function f2 is defined to convert a vector of doubles into a single int.
	// Finally f(words) := f2(f1(words))
	// To obtain lower complexity, we require f1 and f2 can be computed through moving window.
	// The following corner case also needs to be considered:
	// f2(f1(["ab", "cd"])) != f2(f1(["ac", "bd"]))
	// There are many possible options for f2 and f1. 
	// The following code only shows one possibility (probably not the best), 
	// f2 is the function "hash" in the class,
	// f1([a1, a2, ... , an]) := int( decimal_part(log(a1) + log(a2) + ... + log(an)) * 1000000000 )
public:
	// The complexity of this function is O(nW).
	double hash(double f, double code[], string& word) {
		double result = 0.;
		for (auto& c : word)
			result = result * f + code[c];
		return result;
	}

	vector<int> findSubstring(string s, vector<string>& words) {
		uniform_real_distribution<double> unif(0., 1.);
		default_random_engine seed;
		double code[128];
		for (auto &d : code)
			d = unif(seed);
		double f = unif(seed) / 5. + 0.8;
		double value = 0;

		// The complexity of the following for loop is O(L.size( ) * nW).
		for (auto& str : words)
			value += log(hash(f, code, str));

		int unit = 1e9;
		int key = (value - floor(value)) * unit;
		int nS = s.size(), nL = words.size(), nW = words[0].size();
		double fn = pow(f, nW - 1.);
		vector<int> result;
		if (nS < nW)
			return result;
		vector<double> values(nS - nW + 1);
		string word(s.begin(), s.begin() + nW);
		values[0] = hash(f, code, word);

		// Use a moving window to hash every word with length nW in S to a float number, 
		// which is stored in vector values[]
		// The complexity of this step is O(nS).
		for (int i = 1; i <= nS - nW; ++i)
			values[i] = (values[i - 1] - code[s[i - 1]] * fn) * f + code[s[i + nW - 1]];

		// This for loop will run nW times, each iteration has a complexity O(nS/nW)
		// So the overall complexity is O(nW * (nS / nW)) = O(nS)
		for (int i = 0; i < nW; ++i)
		{
			int j0 = i, j1 = i, k = 0;
			double sum = 0.;

			// Use a moving window to hash every words.size() continuous words with length nW in S.
			// This while loop will terminate within nS/nW iterations since the increasement of j1 is nW,
			// So the complexity of this while loop is O(nS / nW).
			while (j1 <= nS - nW)
			{
				sum += log(values[j1]);
				++k;
				j1 += nW;
				if (k == nL)
				{
					int key1 = (sum - floor(sum)) * unit;
					if (key1 == key)
						result.push_back(j0);
					sum -= log(values[j0]);
					--k;
					j0 += nW;
				}
			}
		}
		return result;
	}
};

// using Rabin-Karp algorithm to greatly speed up hashcode computation. ( from O(len * N) to O(N) )
// You can add a full check(when hashsums are equal) to handle false positives.

/*
In my understanding, the purpose of setting hashes[i] to 0 if it's not in strSet 
is to eliminate the interference of those hash values when comparing the hash sums. 
For example, suppose that the pattern vector contains "aa" and "bb", 
and the string S has concatenated words like "ab" and "ba"; 
in this case, hashes("aa") + hashes("bb") == hashes("ab") + hashes("ba"), 
but since we have set hashes("ab") and hashes("ba") to 0, 
the equality of the hash sums won't hold any more and the incorrect index is not added to the result vector.

The last "// O(n * L.size())" part can indeed be optimized down to O(n) where n is the length of string S.
*/

// 32ms
class Solution3 {
	size_t stringHash(const string& s) {
		size_t h = 0;
		for (size_t i = 0; i < s.length(); ++i)
			h = (s[i] + 31 * h) % 997;
		return h;
	}

	size_t exponential(unsigned int n) {
		unsigned int p = 1;
		for (unsigned int i = 0; i < n; ++i)
			p = (31 * p) % 997;
		return p;
	}

public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> result;

		size_t cntL = words.size(); // count of strings in L
		size_t lenL = words[0].length(); // Length of L[i]
		size_t lenS = s.length(); // Length of S

		// Special case handling
		if ((cntL == 0) || (lenS == 0) || (lenS < cntL * lenL))
			return result;

		// Compute hash sum for L, and hashset for input string O(cntL * lenL)
		size_t hashSum = 0;
		unordered_set<size_t> strSet;
		for_each(words.begin(), words.end(), [&](const string& str) {
					int hs = stringHash(str);
					strSet.insert(hs);
					hashSum += hs;
				});

		// 31 ^ (len - 1) % 997
		size_t power = exponential(lenL - 1);

		// Compute hash for each position (using Rabin-Karp), O(lenS)
		vector<size_t> hashes;
		hashes.push_back(stringHash(s.substr(0, lenL)));
		for (size_t i = 1; i + lenL <= lenS; ++i)
		{
			size_t newHash = 31 * (hashes.back() + 997 - power * s[i - 1] % 997) + s[i + lenL - 1];
			hashes.push_back(newHash % 997);
		}

		// if substring S[i..i+lenL) is not in L, set hashes[i] to 0, O(lenS)
		for (size_t i = 0; i <= lenS - lenL; ++i)
			if (!strSet.count(hashes[i]))
				hashes[i] = 0;

		vector<size_t> prevHSum(lenL, 0);
		// O(cntL * lenL)
		for (size_t j = 0; j <= min(lenL - 1, lenS - cntL * lenL); ++j)
		{
			size_t currHSum = 0;
			for (size_t k = 0; k <= cntL - 1; ++k)
			{
				currHSum += hashes[j + k * lenL];
				if (currHSum == hashSum)
					result.push_back(j);
			}

			prevHSum[j] = currHSum;
		}

		// O(lenS)
		for (size_t i = 1; i <= (lenS - cntL * lenL) / lenL; ++i)
			for (size_t j = 0; j <= min(lenL - 1, lenS - (i + cntL) * lenL); ++j)
			{
				size_t currHSum = prevHSum[j] - hashes[(i - 1) * lenL + j] + hashes[(i - 1 + cntL) * lenL + j];
				if (currHSum == hashSum)
					result.push_back(i * lenL + j);

				prevHSum[j] = currHSum;
			}

		return result;
	}
};

/*
I think even for these very very rare cases, it doesn't matter and can be easily caught. 
Because there may be two types of possible errors:

1) false negative: there is such a word (concatenated by all the words from the dict) but we fail to detect it. 
2) false positive: there is not such a word but we fire the trigger.

The hashing idea may get false positives but will never miss any true positives. 
Therefore by simply adding a (trivial) double-check for any positives we detected, 
this algorithm can be theoretically correct, and hopefully not too much affected in efficiency.

Based on the idea, I implemented the C++ version, with a sanity checking, as attached below.
*/

// 48ms
class Solution4 {
public:
	unsigned int hash(const string &s) {
		unsigned int ret = 0;
		for (char c : s)
		{
			ret *= 101;
			ret += c;
		}
		return ret;
	}

	bool checkSubstring(const string S, int j, unordered_multiset<string> L) {
		int lsize = L.size(), wsize = L.begin()->size();
		for (int i = 0; i < lsize; ++i)
		{
			auto it = L.find(S.substr(j + i * wsize, wsize));
			if (it == L.end())
				return false;
			L.erase(it);
		}
		return true;
	}

	vector<int> findSubstring(string s, const vector<string>& words) {
		vector<int> ret;
		if (words.empty())
			return ret;
		unsigned int hashsum = 0;
		for (auto s : words)
			hashsum += hash(s);

		int wsize = words[0].size(), lsize = words.size();
		for (int i = 0; i < wsize; ++i)
		{
			vector<unsigned int> hashes;
			int hashsum2 = 0;
			for (int j = i; j < s.size(); j += wsize)
				hashes.push_back(hash(s.substr(j, wsize)));

			if (hashes.size() < lsize)
				continue;
			for (int j = 0; j < lsize; ++j)
				hashsum2 += hashes[j];
			if (hashsum == hashsum2)
				ret.push_back(i);
			for (int j = lsize; j < hashes.size(); ++j)
			{
				hashsum2 = hashsum2 - hashes[j - lsize] + hashes[j];
				if (hashsum == hashsum2)
					ret.push_back(i + (j - lsize + 1) * wsize);
			}
		}

		// check the final result
		unordered_multiset<string> Lset(words.begin(), words.end());
		vector<int> ret2;
		ret2.reserve(ret.size());

		for (int i : ret)
			if (checkSubstring(s, i, Lset))
				ret2.push_back(i);

		return ret2;
	}
};

// use rolling hash twice plus multi windows.
// 16ms, runs faster than other hashing algorithms
class Solution5 {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> result;
		if (words.empty() || words[0].empty())
			return result;
		if (s.size() < words.size() * words[0].size())
			return result;

		const int lsize = words.size();
		const int wsize = words[0].size();
		const int gsize = lsize * wsize;
		const int r = 31;
		const int q = 997;
		const int m = 3355439;

		int lhash = 0;
		for (int i = 0; i < lsize; ++i)
		{
			int whash = 0;
			for (int j = 0; j < wsize; ++j)
				whash = (whash * r + words[i][j]) % q;
			lhash = (lhash + whash) % m;
		}

		vector<int > ghashes(wsize);
		vector<int> window(gsize);
		int whead = 0;

		int whash = 0;
		int i = 0;
		int weight = 1;
		for (; i < wsize - 1; ++i)
		{
			whash = (whash * r + s[i]) % q;
			weight = (weight * r) % q;
		}

		unordered_multiset<string> Lset(words.begin(), words.end());
		for (; i < s.size(); ++i)
		{
			int &ghash = ghashes[whead % wsize];
			ghash = (ghash - window[whead] + m) % m;
			window[whead] = whash = (whash * r + s[i]) % q;
			ghash = (ghash + whash) % m;
			whead = ++whead % gsize;
			whash = (whash - (s[i - wsize + 1] * weight) % q + q) % q;

			if (ghash == lhash && match(s, i - gsize + 1, Lset))
				result.push_back(i - gsize + 1);
		}

		return result;
	}

	bool match(const string &S, int pos, unordered_multiset<string> L) {
		if (pos < 0)
			return false;

		const int lsize = L.size();
		const int wsize = L.begin()->size();
		for (int i = 0; i < lsize; ++i)
		{
			auto iter = L.find(S.substr(pos, wsize));
			if (iter == L.end())
				return false;
			L.erase(iter);
			pos += wsize;
		}
		return true;
	}
};