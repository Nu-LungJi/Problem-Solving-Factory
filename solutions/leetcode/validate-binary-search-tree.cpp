// https://leetcode.com/problems/validate-binary-search-tree/
// Week 7 Day 6
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isValid(TreeNode* node, long long min_val, long long max_val) {
    if (node == nullptr) return true;
    if (node->val <= min_val || node->val >= max_val) {
        return false;
    }
    return isValid(node->left, min_val, node->val) && 
           isValid(node->right, node->val, max_val);
}
bool isValidBST(TreeNode* root) {
    return isValid(root, -1e18, 1e18);
}