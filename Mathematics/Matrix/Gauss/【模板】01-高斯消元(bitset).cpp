#include <bits/stdc++.h>
using namespace std;

const int N = 1024;

// 版本1: 如果遇到自由变量, 直接返回 false
bool Gauss(vector<bitset<N>>& a, int n) {
    for (int c = 0; c < n; c++) {
        int p = c;
        while (p < a.size() && !a[p][c]) p++;
        if (p == a.size()) return false;
        if (p != c) swap(a[c], a[p]);
        for (int i = 0; i < a.size(); i++)
            if (i != c && a[i][c]) a[i] ^= a[c];
    }
    return true;
}

// 版本2: 如果遇到自由变量, 将其设为 1, 继续处理
bool Gauss(vector<bitset<N>>& a, int n) {
    for (int c = 0; c < n; c++) {
        int p = c;
        while (p < a.size() && !a[p][c]) p++;
        if (p == a.size()) {
            bitset<N> newrow;
            newrow[c] = newrow[n] = 1;
            a.push_back(newrow);
        }
        if (p != c) swap(a[c], a[p]);
        for (int i = 0; i < a.size(); i++)
            if (i != c && a[i][c]) a[i] ^= a[c];
    }
    return true;
}