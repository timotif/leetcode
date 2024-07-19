class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        prefix = ""
        if len(strs) == 0:
            return prefix
        string = strs[0]
        for i in range(len(string)):
            c = string[i]
            for s in strs:
                if i >= len(s) or s[i] != c:
                    return prefix
            prefix += c
        return prefix
