#include <bits/stdc++.h>
#include <cassert>
using namespace std;

const int N = 1601;
bool freedom[N];

bool Gauss(vector<bitset<N>>& a, int n) {
    for (int c = 0; c < n; c++) {
        int p = c;
        while (p < a.size() && !a[p][c]) p++;
        if (p == a.size()) {
            p = c;
            a[c][c] = 1;
            a[c][n] = a[c][n] ^ 1;
        }
        if(p != c) swap(a[c], a[p]);
        for (int i = 0; i < a.size(); i++)
            if (i != c && a[i][c]) a[i] ^= a[c];
    }
    return true;
}

int main(){
    int n, m;
    cin >> n >> m;
    auto ind = [&](int i, int j) {return i * m + j;};
    vector<bitset<N>> a(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[ind(i, j)][ind(i, j)] = 1;
            if (i > 0) a[ind(i, j)][ind(i - 1, j)] = 1;
            if (i < n - 1) a[ind(i, j)][ind(i + 1, j)] = 1;
            if (j > 0) a[ind(i, j)][ind(i, j - 1)] = 1;
            if (j < m - 1) a[ind(i, j)][ind(i, j + 1)] = 1;
        }
    }
    assert(Gauss(a, n * m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cout << a[ind(i, j)][n * m] << " ";
        cout << "\n";
    }
    return 0;
}