/*
Find Array Given Subset Sums
You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).

Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.

An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.

Note: Test cases are generated such that there will always be at least one correct answer.

Example 1:

Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
Output: [1,2,-3]
Explanation: [1,2,-3] is able to achieve the given subset sums:
- []: sum is 0
- [1]: sum is 1
- [2]: sum is 2
- [1,2]: sum is 3
- [-3]: sum is -3
- [1,-3]: sum is -2
- [2,-3]: sum is -1
- [1,2,-3]: sum is 0
Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
Example 2:

Input: n = 2, sums = [0,0,0,0]
Output: [0,0]
Explanation: The only correct answer is [0,0].
Example 3:

Input: n = 4, sums = [0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8]
Output: [0,-1,4,5]
Explanation: [0,-1,4,5] is able to achieve the given subset sums.
 

Constraints:

1 <= n <= 15
sums.length == 2^n
-10^4 <= sums[i] <= 10^4
*/

#include <stdlib.h>
#include <stdio.h>

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i ++)
        printf("%d ", arr[i]);
    printf("\n");
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/**
 * @brief Finds the index of a value in an array starting from the beginning
 * @returns The first index of the value in the array, or -1 if not found
*/
int find_index(int *arr, int size, int val)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == val)
            return (i);
    return (-1);
}

/**
 * @brief Finds the index of a value not present in a given exclusion mask
 * @returns The index of the value, or -1 if not found
*/
int find_unique(int *arr, int size, int val, int *mask)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == val && find_index(mask, size, i) < 0)
            return (i);
    return (-1);
}

/**
 * @brief Finds the index of a value in an array starting from the end
 * @returns The first index of the value in the array, or -1 if not found
*/
int find_index_r(int *arr, int size, int val)
{
    for (int i = size - 1; i >= 0; i--)
        if (arr[i] == val)
            return (i);
    return (-1);
}

int find_unique_r(int *arr, int size, int val, int *mask)
{
    for (int i = size - 1; i >= 0; i--)
        if (arr[i] == val && find_index(mask, size, i) < 0)
            return (i);
    return (-1);
}

void init_array(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
        arr[i] = value;
}

int positive_delta(int *arr, int size, int *sub1, int *sub2, int delta)
{
    int *mask = malloc(sizeof(int) * size);
    int m_idx = 0;
    int s1_idx = size / 2 - 1;
    int s2_idx = size / 2 - 1;

    init_array(mask, size, -1);
    init_array(sub1, size / 2, -1);
    init_array(sub2, size / 2, -1);
    for (int i = size - 1; i >= 0; i--)
    {
        if (find_index(mask, size, i) < 0)
        {
            int split_idx = find_unique_r(arr, size, arr[i] - delta, mask);
            if (split_idx >= 0)
            {
                    sub2[s2_idx--] = arr[i];
                    mask[m_idx++] = i;
                    sub1[s1_idx--] = arr[i] - delta;
                    mask[m_idx++] = find_unique_r(arr, size, arr[i] - delta, mask);
            }
            else
                return (0);
        }
    }
    // print_array(sub1, size / 2);
    // print_array(sub2, size / 2);
    return (1);
}

int split_array(int *arr, int size, int delta, int *ans)
{
    if (size < 2)
        return (1);

    int *sub1, *sub2;
    sub1 = malloc(sizeof(int) * size / 2);
    sub2 = malloc(sizeof(int) * size / 2);
    if (positive_delta(arr, size, sub1, sub2, delta))
    {
        *ans = delta;
        ans++;
        int new_delta = sub2[size / 2 - 1] - sub2[size / 2 - 2];
        split_array(sub2, size / 2, new_delta, ans);
    }
    free(sub1);
    free(sub2);
    return (0);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* recoverArray(int n, int* sums, int sumsSize, int* returnSize){
    int *ret = malloc(sizeof(int) * n);
    int *ans = ret;
    qsort(sums, sumsSize, sizeof(int), cmpfunc);
    int delta = sums[sumsSize - 1] - sums[sumsSize - 2];
    split_array(sums, sumsSize, delta, ans);
    print_array(ret, *returnSize);
    return (ret);
}

int main(void)
{
    // int size = 3;
    // recoverArray(size, (int[]){-3,-2,-1,0,0,1,2,3}, 8, &size);
    // int size = 4;
    // int arr[] = {0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8};
    int size_sums = 8;
    int size_ans = 3;
    int arr0[] = {0, 0, 5, 5, 5, 5, 10, 10}; 
    qsort(arr0, size_sums, sizeof(int), cmpfunc);
    print_array(arr0, size_sums);
    recoverArray(size_ans, arr0, size_sums, &size_ans);
    int arr1[] = {0, 0, 5, 5, 6, 6, 11, 11};
    print_array(arr1, size_sums);
    recoverArray(size_ans, arr1, size_sums, &size_ans);
    int arr2[] = {0, 3, 5, 6, 8, 9, 11, 14};
    print_array(arr2, size_sums);
    recoverArray(size_ans, arr2, size_sums, &size_ans);
}
/**
 * - The size of the arr is the n-root of the size of the sums
 * - 0 is always present in the sums
 * - Approach:
 * The largest sum is the sum of all positive numbers.
 * The second largest can be a sum of all positives but one OR
 * the sum of all positives and the largest negative.
 * So the difference between those two values is a number in the set,
 * but it could be positive or negative...
 * I'm trying to sum from the second last element until I reach the 0 in the sums:
 * if I do reach 0 
*/