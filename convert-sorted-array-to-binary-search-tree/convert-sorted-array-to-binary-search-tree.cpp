/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return (makeBranch(nums, 0, nums.size() - 1));
    }
    TreeNode *makeBranch(vector<int>& nums, int begin, int end) {
        if (begin > end)
            return (nullptr);
        int mid = (begin + end) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = makeBranch(nums, begin, mid -1);
        root->right = makeBranch(nums, mid + 1, end);
        return (root);
    }
};

void printTree(TreeNode *root) {
	if (root == nullptr) {
		return;
	}
	printTree(root->left);
	cout << root->val << " ";
	printTree(root->right);
}

int main(void) {
	vector<int> nums = {-10, -3, 0, 5, 9};
	Solution solution;
	TreeNode* root = solution.sortedArrayToBST(nums);
	printTree(root);
	return 0;
}