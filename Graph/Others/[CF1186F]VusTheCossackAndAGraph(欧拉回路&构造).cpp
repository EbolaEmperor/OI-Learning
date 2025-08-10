#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
vector<pair<int,int>> ans;
struct Edge {
    int v, dele, nxt;
} e[N << 1];
int h[N], cur[N], ecnt = 0;
int deg[N], cnt = 0;
bool vis[N];

inline void add_edge(int x, int y) {
    deg[x]++; deg[y]++;
    e[ecnt++] = {y, 0, h[x]};
    h[x] = ecnt - 1;
    e[ecnt++] = {x, 0, h[y]};
    h[y] = ecnt - 1;
}

void dfs_euler(int i) {
    vis[i] = 1;
    while (cur[i] != -1) {
        bool flag = e[cur[i]].dele;
        e[cur[i]].dele = 1;
        e[cur[i]^1].dele = 1;
        int v = e[cur[i]].v;
        cur[i] = e[cur[i]].nxt;
        if(flag) continue;
        dfs_euler(v);
        if (cnt) ans.emplace_back(i, v);
        cnt ^= 1;
    }
}

void dfs_delete(int u) {
    vis[u] = 1;
    for (int j = h[u]; j != -1; j = e[j].nxt) {
        if (vis[e[j].v]) continue;
        dfs_delete(e[j].v);
        if (deg[e[j].v] & 1) {
            ans.emplace_back(u, e[j].v);
            deg[u]--; deg[e[j].v]--;
            e[j].dele = 1;
            e[j ^ 1].dele = 1;
        }
    }
}

int main() {
    memset(h, -1, sizeof(h));
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        add_edge(x, y);
    }
    for (int i = 1; i <= n; i++)
        if(!vis[i]) dfs_delete(i);
    memcpy(cur, h, sizeof(cur));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if(!vis[i] && deg[i]) cnt = 1, dfs_euler(i);
    cout << ans.size() << "\n";
    for (auto [x, y] : ans)
        cout << x << " " << y << "\n";
    return 0;
}