#include "huffmanEncode.h"

int lastByteLength;
unique_ptr<TreeNode> generateTree(string &s)
{
    int n = s.size(), value;
    if (n == 0)
        return nullptr;
    vector<unique_ptr<TreeNode>> x(2);
    vector<pair<int, int>> a;
    vector<int> freq(256, 0);
    for (int i = 0; i < n; i++)
    {
        freq[s[i]]++;
    }
    for (int i = 0; i < 128; i++)
    {
        if (freq[i] > 0)
            a.push_back(make_pair(freq[i], i));
    }
    sort(a.begin(), a.end());
    queue<unique_ptr<TreeNode>> q1, q2;
    for (int i = 0; i < a.size(); i++)
    {
        q1.push(make_node(char(a[i].second), a[i].first));
    }
    if (q1.size() == 1)
    {
        q2.push(move(q1.front()));
        q1.pop();
    }
    while (q1.size() + q2.size() > 1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (q1.empty())
            {
                x[i] = move(q2.front());
                q2.pop();
            }
            else if (q2.empty())
            {
                x[i] = move(q1.front());
                q1.pop();
            }
            else if (q1.front()->val <= q2.front()->val)
            {
                x[i] = move(q1.front());
                q1.pop();
            }
            else
            {
                x[i] = move(q2.front());
                q2.pop();
            }
        }
        value = (x[0] ? x[0]->val : 0) + (x[1] ? x[1]->val : 0);
        q2.push(make_node('*', value, move(x[0]), move(x[1])));
    }
    auto res = move(q2.front());
    q2.pop();
    return res;
}

void buildCode(const unique_ptr<TreeNode> &root, string &cur, unordered_map<char, string> &codes)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        codes[root->x] = cur.empty() ? "0" : cur;
        return;
    }
    cur.push_back('0');
    buildCode(root->left, cur, codes);
    cur.back() = '1';
    buildCode(root->right, cur, codes);
    cur.pop_back();
}

vector<uint8_t> getEncode(const string &s, unordered_map<char, string> &codes)
{
    BitWriter bw;

    for (char ch : s)
    {
        for (char bit : codes[ch])
        {
            bw.bit_push(bit == '1');
        }
    }
    lastByteLength = (bw.bit_pos == 0 ? 8 : bw.bit_pos);
    bw.flush();
    return bw.data;
}

void buildCanonicalEncode(const unique_ptr<TreeNode> &root, vector<pair<int, char>> &symbols, int &depth)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        symbols.push_back(make_pair(depth, root->x));
    }
    depth++;
    buildCanonicalEncode(root->left, symbols, depth);
    buildCanonicalEncode(root->right, symbols, depth);
    depth--;
    return;
}

void buildCanonicalCodes(const vector<pair<int, char>> &symbols, unordered_map<char, vector<uint8_t>> &canonicalCodes)
{
    vector<pair<int, char>> sorted = symbols;
    sort(sorted.begin(), sorted.end());

    uint32_t code = 0;
    int prevLen = 0;

    for (auto &[len, ch] : sorted)
    {
        code <<= (len - prevLen);

        vector<uint8_t> bits(len);
        for (int i = 0; i < len; i++)
            bits[len - 1 - i] = static_cast<uint8_t>((code >> i) & 1);

        canonicalCodes[ch] = std::move(bits);

        code++;
        prevLen = len;
    }
}
