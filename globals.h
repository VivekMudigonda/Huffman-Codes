#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    char x = '*';
    int val = 0;
    unique_ptr<TreeNode> left = nullptr;
    unique_ptr<TreeNode> right = nullptr;
    TreeNode(char x = '*', int val = 0, unique_ptr<TreeNode> left = nullptr, unique_ptr<TreeNode> right = nullptr)
    {
        this->x = x;
        this->val = val;
        this->left = move(left);
        this->right = move(right);
    }
};

unique_ptr<TreeNode> make_node(char x = '*', int val = 0, unique_ptr<TreeNode> left = nullptr, unique_ptr<TreeNode> right = nullptr)
{
    return make_unique<TreeNode>(x, val, move(left), move(right));
}