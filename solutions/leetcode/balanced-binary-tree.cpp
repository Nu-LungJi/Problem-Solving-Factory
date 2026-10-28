// https://leetcode.com/problems/balanced-binary-tree/
// Week 7 Day 2
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

int Height(TreeNode* root) {
    if (root == nullptr) return 0;
    int Left = Height(root->left);
    int Right = Height(root->right);

    if (Left == -1 || Right == -1) return -1;
    if (std::abs(Left - Right) > 1) return -1;

    return std::max(Left, Right) + 1;
} 
bool isBalanced(TreeNode* root) {
    if (root == nullptr) return true;

    return Height(root) != -1;
}