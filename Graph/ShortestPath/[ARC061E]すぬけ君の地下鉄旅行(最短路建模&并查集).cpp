#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct Edge{int u, v;};
vector<Edge> g[N * 3];
vector<Edge> e[N * 10];
int col[N], n, m, tot;
int fa[N];

int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}

void prework(int c){
    vector<int> p;
    for(auto eg : e[c])
        p.push_back(eg.u), p.push_back(eg.v);
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    for(int x : p) fa[x] = x;
    for(auto eg : e[c])
        if(find(eg.u) != find(eg.v))
            fa[find(eg.u)] = find(eg.v);
    for(int x : p)
        if(fa[x] == x) col[x] = ++tot;
    for(int x : p){
        col[x] = col[find(x)];
        g[x].push_back((Edge){col[x], 1});
        g[col[x]].push_back((Edge){x, 1});
    }
}

int bfs(){
    static int dis[N * 3];
    memset(dis, -1, sizeof(dis));
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    while(!q.empty()){
        int x = q.front(); q.pop();
        for(Edge eg : g[x])
            if(dis[eg.u] == -1){
                dis[eg.u] = dis[x] + eg.v;
                q.push(eg.u);
            }
    }
    return (dis[n] > 0) ? (dis[n] / 2) : -1;
}

int main(){
    scanf("%d%d", &n, &m); tot = n;
    for(int i = 1, u, v, c; i <= m; ++i){
        scanf("%d%d%d", &u, &v, &c);
        e[c].push_back((Edge){u, v});
    }
    for(int c = 1; c <= 1e6; ++c)
        if(!e[c].empty()) prework(c);
    cout << bfs() << endl;
    return 0;
}