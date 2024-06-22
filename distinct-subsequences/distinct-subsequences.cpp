/**
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.

The test cases are generated so that the answer fits on a 32-bit signed integer.

 

Example 1:

Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from s.
rabbbit
rabbbit
rabbbit
Example 2:

Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from s.
babgbag
babgbag
babgbag
babgbag
babgbag
 

Constraints:

1 <= s.length, t.length <= 1000
s and t consist of English letters.
*/
#include <iostream>
#include <map>
using namespace std;

class Solution {
public:
	map<pair<int, int>, int> cache;
    int numDistinct(string s, string t) {
        return (compare(s, t, 0, 0));
    }
    int compare(string s, string t, int i, int j) {
		if (j == t.size()) {
			return (1);
		}
		if (i == s.size() || (s.size() - i) < (t.size() - j))
			return (0);
		if (cache.count(pair<int, int>(i, j)) != 0)
			return (cache[pair<int, int>(i, j)]);
        if (s[i] == t[j]) {
			int opt1 = compare(s, t, i + 1, j + 1);
			int opt2 = compare(s, t, i + 1, j);
			cache[pair<int, int>(i, j)] = opt1 + opt2; 
		} else {
			cache[pair<int, int>(i, j)] = compare(s, t, i + 1, j);
		}
		return (cache[pair<int, int>(i, j)]);
    }
};

int main(int ac, char **av) {
	if (ac != 3)
		return (1);
	Solution sol;
	int ret = sol.numDistinct(av[1], av[2]);
	std::cout << "Solution: " << ret << std::endl;
}