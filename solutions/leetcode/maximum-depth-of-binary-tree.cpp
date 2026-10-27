// https://leetcode.com/problems/maximum-depth-of-binary-tree/
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

int maxDepth(TreeNode* root) {
    int Depth = 1;
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return Depth;

    std::queue<TreeNode*> Queue;
    Queue.push(root);

    while (!Queue.empty()) {
        int LevelSize = static_cast<int>(Queue.size());
        for (int i = 0; i < LevelSize; ++i) {
            auto* Node = Queue.front();
            Queue.pop();

            if (Node->left != nullptr) Queue.push(Node->left);
            if (Node->right != nullptr) Queue.push(Node->right);
        }
        if (!Queue.empty()) Depth++;
    }

    return Depth;
}