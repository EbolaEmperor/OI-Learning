#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
#include <map>
#include <queue>
using namespace std;

const int N = 2010;
map<tuple<int,int,int>, bool> forbid;
int n, m, k;
vector<int> g[N];
int dis[N][N];
pair<int,int> pre[N][N];

void bfs(){
    queue<pair<int,int>> q;
    memset(dis, -1, sizeof(dis));
    q.push(make_pair(0,1));
    dis[0][1] = 0;
    while(!q.empty()){
        auto [p, u] = q.front(); q.pop();
        for(int v : g[u]){
            if(forbid.count(make_tuple(p, u, v))) continue;
            if(dis[u][v] == -1){
                dis[u][v] = dis[p][u] + 1;
                pre[u][v] = make_pair(p, u);
                q.push(make_pair(u, v));
            }
        }
    }
}

void output(int u, int v){
    if(u) output(pre[u][v].first, pre[u][v].second);
    cout << v << " ";
}

int main(){
    cin >> n >> m >> k;
    for(int i = 1, x, y; i <= m; i++){
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1, a, b, c; i <= k; i++){
        cin >> a >> b >> c;
        forbid[make_tuple(a, b, c)] = 1;
    }
    bfs();
    int maxpre = -1;
    for(int i = 1; i <= n; i++)
        if(dis[i][n] != -1 && (maxpre == -1 || dis[i][n] < dis[maxpre][n]))
            maxpre = i;
    if(maxpre == -1) cout << -1 << endl;
    else {
        cout << dis[maxpre][n] << endl;
        output(maxpre, n);
        cout << endl;
    }
    return 0;
}