#include <globals.h>
using namespace std;

unique_ptr<TreeNode> generateTree(string &s)
{
    int n = s.size(), value;
    if (n == 0)
        return nullptr;
    vector<unique_ptr<TreeNode>> x(2);
    vector<pair<int, int>> a;
    vector<int> freq(128, 0);
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
