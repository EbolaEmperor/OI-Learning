#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    Edge() : u(0), v(0), w(0) {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<int> fa;
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for(int i = 0; i < n; i++)
            cin >> p[i];
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());

        if(p.size() == 1) {
            cout << 0 << "\n";
            continue;
        }

        vector<Edge> edges;
        for(int i = 0; i < p.size() - 1; i++) {
            if(p[i + 1] < 2 * p[i]) {
                edges.emplace_back(i, i + 1, p[i + 1] - p[i]);
            }
            for(int j = 2; j * p[i] <= p.back(); j++) {
                auto it = lower_bound(p.begin(), p.end(), j * p[i]);
                if(it != p.end() && *it < (j + 1) * p[i])
                    edges.emplace_back(i, it - p.begin(), *it - j * p[i]);
            }
        }

        sort(edges.begin(), edges.end());
        fa.resize(p.size());
        iota(fa.begin(), fa.end(), 0);
        long long ans = 0;
        int cnt = 0;
        for(const auto& edge : edges) {
            int u = find(edge.u);
            int v = find(edge.v);
            if(u != v) {
                fa[u] = v;
                ans += edge.w;
                if(++cnt == p.size() - 1) break;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}