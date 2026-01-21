#pragma once
#include "globals.h"
unique_ptr<TreeNode> generateTree(string &s);
void buildCode(const unique_ptr<TreeNode> &root, string &cur, unordered_map<char, string> &codes);
vector<uint8_t> getEncode(const string &s, unordered_map<char, string> &codes);
void buildCanonicalEncode(const unique_ptr<TreeNode> &root, vector<pair<int, char>> &symbols, int &depth);
void buildCanonicalCodes(const vector<pair<int, char>> &symbols, unordered_map<char, vector<uint8_t>> &canonicalCodes);
