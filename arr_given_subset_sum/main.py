from collections import Counter

class Solution:
    def recoverArray(self, n: int, sums: list[int]) -> list[int]:
        def dfs(sums):
            if 0 not in sums:
                return []
            n = len(sums)
            if n == 2:
                sums.remove(0)
                return [sums[0]]
            x = sums[-1] - sums[-2]

            #try positive
            newSums1 = []
            count1 = Counter(sums)
            for a in sums[::-1]:
                b = a - x
                if count1[a]:
                    if count1[b]:
                        newSums1.append(b)
                        count1[a] -= 1
                        count1[b] -= 1
                    else:
                        break
            ans1 = []
            if len(newSums1) == n // 2:
                ans1 = [x] + dfs(newSums1[::-1])
        
            #try negative
            newSums2 = []
            count2 = Counter(sums)
            for a in sums:
                b = a + x
                if count2[a]:
                    if count2[b]:
                        newSums2.append(b)
                        count2[a] -= 1
                        count2[b] -= 1
                    else:
                        break
            ans2 = []
            if len(newSums2) == n // 2:
                ans2 = [-x] + dfs(newSums2)
            return ans1 if len(ans1) >= len(ans2) else ans2

        sums.sort()
        return dfs(sums)
x = Solution()
print("**********\n", x.recoverArray(4, [0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8]))
print("**********\n", x.recoverArray(3, [0, 0, 5, 5, 5, 5, 10, 10]))
print("**********\n", x.recoverArray(3, [0, 0, 5, 5, 6, 6, 11, 11]))
print("**********\n", x.recoverArray(3, [0, 3, 5, 6, 8, 9, 11, 14]))
print("**********\n", x.recoverArray(3, [-3, 0, 2, 3, 5, 6, 8, 11]))