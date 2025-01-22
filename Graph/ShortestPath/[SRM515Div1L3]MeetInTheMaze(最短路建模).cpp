#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int inf = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char maze[N][N];
int CL = 0, posL[N * N];
int CR = 0, posR[N], disR[N][N * N];
int CF = 0, posF[N], disF[N][N * N];
vector<int> chain[2 * N * N];
long long sum = 0;
int n, m;

inline void fuck(){puts("fuck"); exit(0);}
inline int idx(int x, int y){return (x - 1) * m + y;}
inline pair<int, int> decomp(int id){
    return make_pair((id - 1) / m + 1, (id - 1) % m + 1);
}

void bfs(int s, int *dis, int lim = 0){
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(u <= n * m){
            auto [i, j] = decomp(u);
            for(int k = 0; k < 4; k++){
                int vi = i + dx[k], vj = j + dy[k], v = idx(vi, vj);
                if(vi >= 1 && vi <= n && vj >= 1 && vj <= m 
                   && maze[vi][vj] != '#' && dis[v] == inf){
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        } else {
            for(int v : chain[u - n * m - 1])
                if(dis[v] == inf){
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            if(u <= n * m + lim){
                dis[u + 1] = dis[u] + 1;
                q.push(u + 1);
            }
        }
    }
}

void readAndInit(){
    freopen("maze.in", "r", stdin);
    freopen("maze.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%s", maze[i] + 1);
        for(int j = 1; j <= m; j++){
            if(maze[i][j] == 'L') posL[++CL] = idx(i, j);
            else if(maze[i][j] == 'R') posR[++CR] = idx(i, j);
            else if(maze[i][j] == 'F') posF[++CF] = idx(i, j);
        }
    }
    memset(disR, 0x3f, sizeof(disR));
    memset(disF, 0x3f, sizeof(disF));
    for(int i = 1; i <= CR; i++) bfs(posR[i], disR[i]);
    for(int i = 1; i <= CF; i++) bfs(posF[i], disF[i]);
}

void work(int F, int R){
    int maxd = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(maze[i][j] != '#'){
                int u = idx(i, j);
                int d = disF[F][u] + disR[R][u];
                if(d <= 2 * n * m){
                    chain[d - 1].push_back(u);
                    maxd = max(maxd, d - 1);
                }
                else if(maze[i][j] == 'L') fuck();
            }
    static int dis[N * N * 3];
    memset(dis, 0x3f, sizeof(int) * (n * m + maxd));
    bfs(n * m + 1, dis, maxd);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(maze[i][j] == 'L')
                sum += dis[idx(i, j)];
    for(int i = 0; i <= maxd; i++)
        chain[i].clear();
}

int main(){
    readAndInit();
    for(int i = 1; i <= CF; i++)
        for(int j = 1; j <= CR; j++)
            work(i, j);

    int cnt = CL * CR * CF;
    auto d = gcd(sum, cnt);
    printf("%lld/%lld\n", sum / d, cnt / d);
    return 0;
}