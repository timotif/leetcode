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
#include <string.h>
#define SEP -1000

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

int intlen(int *arr)
{
    if (!arr)
        return (0);
    int i = 0;
    while (arr[i] != SEP)
        i++;
    return (i);
}

int *dfs(int *sums, int n) {
    if (find_index(sums, n, 0) < 0)
        return (NULL);
    if (n == 2)
        return (sums[0] == 0 ? (int[]){sums[1]} : (int[]){sums[0]});
    int x = sums[n - 1] - sums[n - 2];

    // try positive
    int newSums1[n / 2];
    int idx1 = 0;
    int mask[n];
    int m_idx = 0;
    init_array(mask, n, -1);
    for (int a = n - 1; a >= 0; a--) {
        if (find_index(mask, n, a) < 0) {
            mask[m_idx++] = a;
            int b = sums[a] - x;
            int idx_b = find_unique_r(sums, n, b, mask);
            if (idx_b >= 0) {
                mask[m_idx++] = idx_b;
                newSums1[idx1++] = b;
            }
            else
                break ;
        }
    }
    int *ans1 = malloc(sizeof(int) * n);
    init_array(ans1, n, SEP);
    static int count_ans1 = 0;
    // printf("m_idx positive: %d n: %d\n", m_idx, n);
    if (m_idx == n) { // the positive x number is correct
        ans1[0] = x; // add it to the answer
        count_ans1++;
        /* Now the new sums array is newSums1 and it needs to find the 
        next number for the solution */
        qsort(newSums1, n / 2, sizeof(int), cmpfunc); // sort the array
        // printf("newSums1: ");
        // print_array(newSums1, n / 2);
        int *dfsResult = dfs(newSums1, n / 2);
        // int i;
        if (dfsResult) {
            count_ans1++;
            memcpy(ans1 + 1, dfsResult, sizeof(int) * n / 2);
        }
    }
    // the positive x number is NOT correct
    // try negative
    int newSums2[n / 2];
    int idx2 = 0;
    m_idx = 0;
    init_array(mask, n, -1);
    for (int a = 0; a < n; a++) {
        if (find_index(mask, n, a) < 0) {
            mask[m_idx++] = a;
            int b = sums[a] + x;
            int idx_b = find_unique(sums, n, b, mask);
            if (idx_b >= 0) {
                mask[m_idx++] = idx_b;
                newSums2[idx2++] = b;
            }
            else
                break ;
        }
    }
    int *ans2 = malloc(sizeof(int) * n);
    init_array(ans2, n, SEP);
    static int count_ans2 = 0;
    if (m_idx == n) { // the negatve x number is correct
        ans2[0] = -x; // add it to the answer
        // print_array(newSums2, n / 2);
        int *dfsResult = dfs(newSums2, n / 2);
        // int i;
        if (dfsResult) {
            count_ans2++;
            memcpy(ans2 + 1, dfsResult, sizeof(int) * n / 2);
        }
    }
    if (intlen(ans1) >= intlen(ans2)) {
        free(ans2);
        return (ans1);
    } else {
        free(ans1);
        return (ans2);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* recoverArray(int n, int* sums, int sumsSize, int* returnSize) {
    qsort(sums, sumsSize, sizeof(int), cmpfunc);
    int *ret = dfs(sums, sumsSize);
    print_array(ret, *returnSize);
    return (ret);
}

int main(void)
{
    int size = 3;
    recoverArray(size, (int[]){-3,-2,-1,0,0,1,2,3}, 8, &size);
    size = 4;
    int arr[] = {0,0,5,5,4,-1,4,9,9,-1,4,3,4,8,3,8};
    recoverArray(size, arr, 16, &size);
    int size_sums = 8;
    int size_ans = 3;
    int arr0[] = {0, 0, 5, 5, 5, 5, 10, 10}; 
    qsort(arr0, size_sums, sizeof(int), cmpfunc);
    // print_array(arr0, size_sums);
    recoverArray(size_ans, arr0, size_sums, &size_ans);
    int arr1[] = {0, 0, 5, 5, 6, 6, 11, 11};
    print_array(arr1, size_sums);
    recoverArray(size_ans, arr1, size_sums, &size_ans);
    int arr2[] = {0, 3, 5, 6, 8, 9, 11, 14};
    print_array(arr2, size_sums);
    recoverArray(size_ans, arr2, size_sums, &size_ans);
    int arr3[] = {-3, 0, 2, 3, 5, 6, 8, 11};
    print_array(arr3, size_sums);
    recoverArray(size_ans, arr3, size_sums, &size_ans);
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