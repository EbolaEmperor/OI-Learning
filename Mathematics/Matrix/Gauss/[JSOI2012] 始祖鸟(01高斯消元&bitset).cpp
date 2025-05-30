#include <bits/stdc++.h>
using namespace std;

const int N = 2048;

bool Gauss(vector<bitset<N>>& a, int n) {
    for (int c = 0; c < n; c++) {
        int p = c;
        while (p < a.size() && !a[p][c]) p++;
        if (p == a.size()) {
            bitset<N> newrow;
            newrow[c] = newrow[n] = 1;
            a.push_back(newrow);
        }
        if(p != c) swap(a[c], a[p]);
        for (int i = 0; i < a.size(); i++)
            if (i != c && a[i][c]) a[i] ^= a[c];
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<bitset<N>> a(n);
    for (int i = 0, m; i < n; i++) {
        cin >> m;
        for (int j = 0, x; j < m; j++) {
            cin >> x;
            a[i][x - 1] = 1;
        }
        if (m & 1) a[i][i] = a[i][n] = 1;
    }
    if (!Gauss(a, n))
        cout << "Impossible" << endl;
    else {
        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (a[i][n]) ans.push_back(i + 1);
        cout << ans.size() << endl;
        for(int x : ans) cout << x << " ";
    }
    return 0;
}