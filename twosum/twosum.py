class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        num_hash = {}
        for idx, num in enumerate(nums):
            diff = target - num
            if num in num_hash:
                return [num_hash[num], idx]
            num_hash[diff] = idx
        return []

solution = Solution()
print(solution.twoSum([2, 7, 11, 15], 9))