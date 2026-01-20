#include "globals.h"

string decode(const unique_ptr<TreeNode> &root, vector<uint8_t> &encoded)
{
    string result;
    if (!root)
        return result;
    int totalBytes = (encoded.size() - 1) * 8 + lastByteLength;
    if (!root->left && !root->right)
    {
        result.assign(root->x, totalBytes);
        return result;
    }
    TreeNode *cur = root.get();
    BitReader br(encoded);
    for (int i = 0; i < totalBytes; i++)
    {
        int bit = br.read_bit();
        cur = (bit == 0) ? cur->left.get() : cur->right.get();
        if (!cur->left && !cur->right)
        {
            result.push_back(cur->x);
            cur = root.get();
        }
    }
    return result;
}