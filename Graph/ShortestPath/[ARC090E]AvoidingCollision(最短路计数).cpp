#include <bits/stdc++.h>
using namespace std;

const int ha = 1e9 + 7;
const int N = 100010;
struct Node{
    int u; long long dis;
    bool operator < (const Node &b) const{
        return dis > b.dis;
    }
};
struct Edge{int v, w;};
vector<Edge> g[N];
long long dis1[N], dis2[N];
int cnt1[N], cnt2[N];
int n, m, s, t;

inline void add(int &x, const int &y){
    x += y; if(x >= ha) x -= ha;
}
inline void mns(int &x, const int &y){
    x -= y; if(x < 0) x += ha;
}

void dijkstra(int s, long long *dis, int *cnt){
    priority_queue<Node> pq;
    static bool vis[N];
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(long long) * (n + 1));
    memset(cnt, 0, sizeof(int) * (n + 1));
    pq.push((Node){s, 0});
    cnt[s] = 1; dis[s] = 0;
    while(!pq.empty()){
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto& ed : g[u]){
            if(dis[u] + ed.w < dis[ed.v]){
                dis[ed.v] = dis[u] + ed.w;
                cnt[ed.v] = cnt[u];
                pq.push((Node){ed.v, dis[ed.v]});
            } else if(dis[u] + ed.w == dis[ed.v])
                add(cnt[ed.v], cnt[u]);
        }
    }
}

int main(){
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1, u, v, w; i <= m; ++i){
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((Edge){v,w});
        g[v].push_back((Edge){u,w});
    }
    dijkstra(s, dis1, cnt1);
    dijkstra(t, dis2, cnt2);
    int ans = 1ll * cnt1[t] * cnt1[t] % ha;
    long long d = dis1[t];
    for(int i = 1; i <= n; ++i)
        if(dis1[i] + dis2[i] == d && dis1[i] == dis2[i])
            mns(ans, 1ll * cnt1[i] * cnt1[i] % ha * cnt2[i] % ha * cnt2[i] % ha);
    for(int u = 1; u <= n; ++u)
        for(auto &ed : g[u])
            if(dis1[u] + ed.w + dis2[ed.v] == d
               && 2 * dis1[u] < d && 2 * dis2[ed.v] < d)
                mns(ans, 1ll * cnt1[u] * cnt1[u] % ha
                             * cnt2[ed.v] % ha * cnt2[ed.v] % ha);
    cout << ans << endl;
    return 0;
}