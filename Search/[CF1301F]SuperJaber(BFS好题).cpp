#include <bits/stdc++.h>
using namespace std;

const int go[][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};
const int N = 1010, K = 45;
int dis[K][N][N];
// dis[c][i][j] : 从 (i,j) 到颜色 c 的最小步数
vector<pair<int,int>> colpos[K];
int col[N][N];
int n, m, k, q;

void bfs(int c){
    static bool viscol[K];
    memset(viscol, 0, sizeof(viscol));
    viscol[c] = 1;
    queue<pair<int,int>> q;
    for(auto p : colpos[c]){
        dis[c][p.first][p.second] = 0;
        q.push(p);
    }
    while(!q.empty()){
        auto p = q.front(); q.pop();
        int i = p.first, j = p.second, nc = col[i][j];
        if(!viscol[nc]){
            viscol[nc] = 1;
            for(auto p : colpos[nc])
                if(dis[c][p.first][p.second] == -1){
                    dis[c][p.first][p.second] = dis[c][i][j] + 1;
                    q.push(p);
                }
        }
        for(int d = 0; d < 4; d++){
            int ni = i + go[d][0], nj = j + go[d][1];
            if(ni >= 1 && ni <= n && nj >= 1 && nj <= m && dis[c][ni][nj] == -1){
                dis[c][ni][nj] = dis[c][i][j] + 1;
                q.push(make_pair(ni, nj));
            }
        }
    }
}

int main(){
    memset(dis, -1, sizeof(dis));
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            scanf("%d", &col[i][j]);
            colpos[col[i][j]].emplace_back(i, j);
        }
    for(int i = 1; i <= k; i++) bfs(i);
    scanf("%d", &q);
    while(q--){
        int i1, j1, i2, j2;
        scanf("%d%d%d%d", &i1, &j1, &i2, &j2);
        int ans = abs(i1 - i2) + abs(j1 - j2);
        for(int c = 1; c <= k; c++)
            ans = min(ans, dis[c][i1][j1] + dis[c][i2][j2] + 1);
        printf("%d\n", ans);
    }
    return 0;
}
