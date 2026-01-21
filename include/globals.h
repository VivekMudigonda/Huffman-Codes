#pragma once
#include <bits/stdc++.h>
using namespace std;

extern int lastByteLength;
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

struct BitWriter
{
    vector<uint8_t> data;
    uint8_t cur = 0;
    int bit_pos = 0;
    void bit_push(bool b)
    {
        if (b)
        {
            cur |= b ? (1 << (7 - bit_pos)) : 0;
            bit_pos++;
            if (bit_pos == 8)
            {
                data.push_back(cur);
                bit_pos = 0;
            }
        }
    }
    void flush()
    {
        lastByteLength = bit_pos;
        if (bit_pos > 0)
        {
            data.push_back(cur);
        }
        cur = 0;
        bit_pos = 0;
    }
};

struct BitReader
{
    const vector<uint8_t> &data;
    int idx = 0;
    int bit_pos = 0;

    BitReader(const vector<uint8_t> &d) : data(d) {}

    int read_bit()
    {
        int bit = (data[idx] >> (7 - bit_pos)) & 1;
        bit_pos++;
        if (bit_pos == 8)
        {
            bit_pos = 0;
            idx++;
        }
        return bit;
    }
};
