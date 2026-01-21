#pragma once
#include "globals.h"

string decode(const unique_ptr<TreeNode> &root, vector<uint8_t> &encoded);
void buildCanonicalDecodeTable(
    const vector<pair<int, char>> &symbols,
    unordered_map<int, unordered_map<uint32_t, char>> &decodeTable);
string decodeCanonical(
    const vector<uint8_t> &encoded,
    const unordered_map<int, unordered_map<uint32_t, char>> &decodeTable,
    int expectedLength);