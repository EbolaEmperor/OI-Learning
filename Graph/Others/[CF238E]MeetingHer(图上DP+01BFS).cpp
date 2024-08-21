#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int N = 110;
int n, m, Romeo, Juliet, num;
int dis[N][N];
int s[N], t[N];
int f[N][N];
// f[i][u] : 当前在点 u，正乘坐 i 号线，最坏情况下最少还要几次换乘才能到终点
int cnt[N][N];
// cnt[i][k] : 有几个点 x 满足 dist(s[i],x)=k 且 x 在 s[i] 到 t[i] 的最短路上
int deg[N][N];
// deg[i][u] : 在 s[i] 出发的最短路 DAG 上，点 u 的出度是多少

void Floyd(){
    for(int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}

inline bool inSP(int i, int x){
    return dis[s[i]][x] + dis[x][t[i]] == dis[s[i]][t[i]];
}

inline bool isNext(int i, int x, int y){
    return dis[x][y] == 1 && dis[s[i]][x] + 1 == dis[s[i]][y];
}

inline bool mustPass(int i, int x){
    return inSP(i, x) && cnt[i][dis[s[i]][x]] == 1;
}

void initcnt(){
    for(int i = 1; i <= num; i++){
        for(int x = 1; x <= n; x++)
            if(inSP(i, x)){
                cnt[i][dis[s[i]][x]]++;
                for(int y = 1; y <= n; y++)
                    if(inSP(i, y) && isNext(i, x, y)) deg[i][x]++;
            }
    }
}

void bfs01(){
    memset(f, 0x3f, sizeof(f));
    static bool vis[N][N];
    deque<pair<int,int>> q;
    for(int i = 1; i <= num; i++){
        if(inSP(i, Juliet)){
            q.push_back(make_pair(i, Juliet));
            f[i][Juliet] = 0;
        }
    }
    while(!q.empty()){
        auto [j, v] = q.front();
        q.pop_front();
        if(vis[j][v]) continue;
        vis[j][v] = 1;
        for(int i = 1; i <= num; i++){
            if(i != j && inSP(i, v) && mustPass(j, v) && f[j][v] + 1 < f[i][v]){
                f[i][v] = f[j][v] + 1;
                q.push_back(make_pair(i, v));
            }
        }
        for(int u = 1; u <= n; u++)
            if(isNext(j, u, v) && !--deg[j][u] && f[j][v] < f[j][u]){
                f[j][u] = f[j][v];
                q.push_front(make_pair(j, u));
            }
    }
}

int main(){
    memset(dis, 0x3f, sizeof(dis));
    scanf("%d%d%d%d", &n, &m, &Romeo, &Juliet);
    for(int i = 1, u, v; i <= m; i++){
        scanf("%d%d", &u, &v);
        dis[u][v] = 1;
    }
    Floyd();
    scanf("%d", &num);
    for(int i = 1; i <= num; i++){
        scanf("%d%d", &s[i], &t[i]);
        if(dis[s[i]][t[i]] == inf) num--, i--;
    }
    initcnt();
    bfs01();
    int ans = inf;
    for(int i = 1; i <= num; i++)
        if(mustPass(i, Romeo))
            ans = min(ans, f[i][Romeo] + 1);
    cout << (ans == inf ? -1 : ans) << endl;
    return 0;
}
