#include "huffmanDecode.h"

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

void buildCanonicalDecodeTable(
    const vector<pair<int, char>> &symbols,
    unordered_map<int, unordered_map<uint32_t, char>> &decodeTable)
{
    vector<pair<int, char>> sorted = symbols;
    sort(sorted.begin(), sorted.end());

    uint32_t code = 0;
    int prevLen = 0;

    for (auto &[len, ch] : sorted)
    {
        code <<= (len - prevLen);
        decodeTable[len][code] = ch;
        code++;
        prevLen = len;
    }
}

string decodeCanonical(
    const vector<uint8_t> &encoded,
    const unordered_map<int, unordered_map<uint32_t, char>> &decodeTable,
    int expectedLength)
{
    BitReader br(encoded);

    string result;
    result.reserve(expectedLength);

    uint32_t code = 0;
    int length = 0;

    int totalBits =
        (encoded.size() - 1) * 8 + lastByteLength;

    for (int i = 0; i < totalBits; i++)
    {
        code = (code << 1) | br.read_bit();
        length++;

        auto lenIt = decodeTable.find(length);
        if (lenIt != decodeTable.end())
        {
            auto codeIt = lenIt->second.find(code);
            if (codeIt != lenIt->second.end())
            {
                result.push_back(codeIt->second);
                code = 0;
                length = 0;

                if ((int)result.size() == expectedLength)
                    break;
            }
        }
    }
    return result;
}
