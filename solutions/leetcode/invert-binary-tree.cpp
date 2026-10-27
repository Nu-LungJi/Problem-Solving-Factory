// https://leetcode.com/problems/invert-binary-tree/
// Week 7 Day 1
// Paste the platform function signature, then implement your solution.
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) return root;

    queue<TreeNode*> Queue;
    Queue.push(root);

    while(!Queue.empty()) {
        TreeNode* Node = Queue.front();
        Queue.pop();

        std::swap(Node->left, Node->right);

        if (Node->left != nullptr) Queue.push(Node->left);
        if (Node->right != nullptr) Queue.push(Node->right);
    }
        
    return root;
}