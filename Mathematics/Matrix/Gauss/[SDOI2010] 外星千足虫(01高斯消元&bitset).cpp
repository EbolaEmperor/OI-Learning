#include <bits/stdc++.h>
using namespace std;

const int N = 1024;

int Gauss(vector<bitset<N>>& a, int n) {
    int r = 0, maxrow = -1;
    for (int c = 0; c < n; c++) {
        int p = r;
        while (p < a.size() && !a[p][c]) p++;
        if (p == a.size()) return -1;
        maxrow = max(maxrow, p);
        swap(a[r], a[p]);
        for (int i = 0; i < a.size(); i++)
            if (i != r && a[i][c]) a[i] ^= a[r];
        r++;
    }
    return maxrow;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<bitset<N>> a(m);
    for (int i = 0, x; i < m; i++) {
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        a[i] = bitset<N>(s);
        cin >> x;
        a[i][n] = x;
    }
    int res = Gauss(a, n);
    if (res == -1) {
        cout << "Cannot Determine" << endl;
    } else {
        cout << res + 1 << endl;
        for(int i = 0; i < n; i++)
            puts(a[i][n] ? "?y7M#" : "Earth");
    }
    return 0;
}