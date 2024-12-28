#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, w;
    Edge(int v, int w): v(v), w(w) {}
};
const int N = 1e5 + 5;
long long dis[N];
bool inq[N];
vector<Edge> g[N];

void spfa(int s) {
    fill(dis, dis + N, LLONG_MAX);
    dis[s] = 1;
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

long long getans(long long m, long long r) {
    long long ans = 0;
    for(int i = 0; i < m; i++) {
        if(dis[i] <= r) {
            ans += (r - dis[i]) / m + 1;
        }
    }
    return ans;
}

int main() {
    long long h, x, y, z;
    cin >> h >> x >> y >> z;
    if(x == 1){
        cout << h << endl;
        return 0;
    }
    for(int i = 0; i < x; i++) {
        g[i].push_back(Edge((i + y) % x, y));
        g[i].push_back(Edge((i + z) % x, z));
    }
    spfa(1);
    cout << getans(x, h) << endl;
    return 0;
}