#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
https://leetcode.com/problems/longest-common-prefix/

14. Longest Common Prefix
Write a function to find the longest common prefix string amongst an array of
strings.

If there is no common prefix, return an empty string "".

Example 1:
Input: ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        string tmp = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            tmp = twoStrsPrefix(tmp, strs[i]);
        }
        return tmp;
    }

    string twoStrsPrefix(string &s1, string &s2) {
        for (int i = 0; ;i++) {
            if (s1[i] != s2[i]) {
                return s1.substr(0, i);
            }
            if (i == s1.size() - 1) {
                return s1;
            } else if (i == s2.size() - 1) {
                return s2;
            }
        }
    }
};

int main() {
    Solution s;

    vector<string> v{"flower","flow","flight"};
    cout << "|" << s.longestCommonPrefix(v) << "|" << endl;

    vector<string> v2{"dog","racecar","car"};
    cout << "|" << s.longestCommonPrefix(v2) << "|" << endl;
}
