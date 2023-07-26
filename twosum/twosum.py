class Solution:
    # Setting up a basic hash table to store the difference between the target and the current number
    # If the current number is in the hash table, then we have found the pair
    # If not, then we add the difference to the hash table
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