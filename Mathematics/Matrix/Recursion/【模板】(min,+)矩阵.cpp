#include <bits/stdc++.h>
#include <cassert>
using namespace std;

struct MatrixMinPlus {
    vector<vector<int>> a;

    MatrixMinPlus() {}

    MatrixMinPlus(int n) {
        a.resize(n, vector<int>(n, 0x3f3f3f3f));
    }

    static MatrixMinPlus identity(int n) {
        MatrixMinPlus c(n);
        for (int i = 0; i < n; i++) c.a[i][i] = 0;
        return c;
    }

    MatrixMinPlus operator * (const MatrixMinPlus &b) const {
        const int N = a.size();
        assert(N == b.a.size());
        MatrixMinPlus c(N);
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                for (int j = 0; j < N; j++)
                    c.a[i][j] = min(c.a[i][j], a[i][k] + b.a[k][j]);
        return c;
    }

    MatrixMinPlus operator ^ (int b) const {
        const int N = a.size();
        MatrixMinPlus c = identity(N);
        MatrixMinPlus aa = *this;
        for(; b; b >>= 1, aa = aa * aa)
            if (b & 1) c = c * aa;
        return c;
    }
};

// 以 [USACO07NOV] Cow Relays G 为例
int main(){
    int n, t, s, e;
    cin >> n >> t >> s >> e;

    static int adj[205][205];
    memset(adj, 0x3f, sizeof(adj));

    map<int, int> num;
    auto add = [&](int x) { return num.count(x) ? num[x] : num[x] = num.size(); };

    s = add(s); e = add(e);
    for (int i = 0; i < t; i++) {
        int u, v, w;
        cin >> w >> u >> v;
        u = add(u); v = add(v);
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }

    MatrixMinPlus A(num.size());
    for (int i = 0; i < num.size(); i++)
        for (int j = 0; j < num.size(); j++)
            A.a[i][j] = adj[i][j];
    A = A ^ n;
    cout << A.a[s][e] << endl;

    return 0;
}