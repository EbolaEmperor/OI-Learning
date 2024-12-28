#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, w;
    Edge(int v, int w): v(v), w(w) {}
};
const int N = 5e5 + 5;
long long dis[N];
int m;
bool inq[N];
vector<Edge> g[N];

void spfa(int s) {
    fill(dis, dis + m, LLONG_MAX);
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (auto &e : g[u]) {
            if (dis[e.v] > dis[u] + e.w) {
                dis[e.v] = dis[u] + e.w;
                if (!inq[e.v]) {
                    q.push(e.v);
                    inq[e.v] = true;
                }
            }
        }
    }
}

long long getans(long long r) {
    long long ans = 0;
    for(int i = 0; i < m; i++) {
        if(dis[i] <= r) {
            ans += (r - dis[i]) / m + 1;
        }
    }
    return ans;
}

int main() {
    static int n, a[N];
    long long l, r;
    cin >> n >> l >> r;
    m = INT_MAX;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] != 0)
            m = min(m, a[i]);
    }
    for(int i = 0; i < m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[j] != m && a[j] != 0) {
                g[i].push_back(Edge((i + a[j]) % m, a[j]));
            }
        }
    }
    spfa(0);
    cout << getans(r) - getans(l - 1) << endl;
    return 0;
}