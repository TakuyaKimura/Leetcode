/*

Given an absolute path for a file (Unix-style), simplify it.

For example,
    path = "/home/", => "/home"
    path = "/a/./b/../../c/", => "/c"

Corner Cases:
    Did you consider the case where path = "/../"?
    In this case, you should return "/".

    Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
    In this case, you should ignore redundant slashes and return "/home/foo".

*/

#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stk;
        string dir;
        istringstream in(path);
        while (getline(in, dir, '/'))
        {
            if (dir.empty() || dir == ".")
                continue;
            if (dir == "..")
            {
                if (!stk.empty())
                    stk.pop_back();
            }
            else
                stk.push_back(dir);
        }

        if (stk.empty())
            return "/";

        ostringstream out;
        for (string& dir : stk)
            out << "/" << dir;
        return out.str();
    }
};

class Solution2 {
public:
    string simplifyPath(string path) {
        vector<string> stk;
        string::iterator i = path.begin(), j;
        string dir;
        while (i != path.end())
        {
            j = find(++i, path.end(), '/');  // find value in range, take iterators as arguments
            dir = string(i, j);              // range constructor, take iterators as arguments

            if (dir.empty() || dir == ".")
                continue;

            if (dir == "..")
            {
                if (!stk.empty())
                    stk.pop_back();
            }
            else
                stk.push_back(dir);

            i = j;
        }

        stringstream ss;
        if (stk.empty())
            ss << '/';
        else
            for (string& dir : stk)
                ss << '/' << dir;

        return ss.str();
    }
};

class Solution3 {
public:
    string simplifyPath(string path) {
        stack<string> st;
        string result, sub;
        int n = path.length(), i, j = 0;
        while (j != string::npos)  // -1
        {
            i = j;
            j = path.find_first_not_of('/', i + 1);
            if (j == -1)
                break;
            i = j - 1;
            j = path.find('/', j + 1);
            if (j == string::npos)
                sub = path.substr(i + 1);
            else
                sub = path.substr(i + 1, j - i - 1);
            if (sub == "..")
            {
                if (!st.empty())
                    st.pop();
            }
            else if (sub != ".")
                st.push(sub);
        }
        if (st.empty())
            return "/";
        while (!st.empty())
        {
            result = "/" + st.top() + result;
            st.pop();
        }
        return result;
    }
};