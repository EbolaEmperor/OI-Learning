#include <bits/stdc++.h>
using namespace std;

const int mans = 1e6;
const int N = 2010;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
pair<int, int> black[N], white[N];
int bcnt, wcnt;
char grid[N][N];
int bid[N][N], wid[N][N];
int n, m, cnt = 0;

namespace flow{
    const int N = 2e3 + 10;
    const int M = 2e4 + 10;
    const int INF = 1e9;
    int head[N], cur[N], nxt[M], to[M], cap[M], tot, st, en, level[N];
    void init(){
        memset(head, -1, sizeof(head));
        tot = -1;
    }
    void addEdge(int u, int v, int c){
        to[++tot] = v;
        nxt[tot] = head[u];
        head[u] = tot;
        cap[tot] = c;
        to[++tot] = u;
        nxt[tot] = head[v];
        head[v] = tot;
        cap[tot] = 0;
    }
    bool bfs(){
        memset(level, 0, sizeof(level));
        queue<int> q;
        q.push(st);
        level[st] = 1;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int i = head[u]; ~i; i = nxt[i]){
                int v = to[i];
                if(cap[i] && !level[v]){
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[en];
    }
    int dfs(int u, int f){
        if(u == en) return f;
        int ret = 0;
        for(int &i = cur[u]; (~i) && f; i = nxt[i]){
            int v = to[i];
            if(level[v] == level[u] + 1 && cap[i]){
                int x = dfs(v, min(f, cap[i]));
                cap[i] -= x;
                cap[i ^ 1] += x;
                ret += x;
                f -= x;
            }
        }
        if(!ret) level[u] = 0;
        return ret;
    }
    int maxFlow(){
        int ret = 0;
        while(bfs()){
            memcpy(cur, head, sizeof(head));
            ret += dfs(st, INF);
        }
        return ret;
    }
}

int couple[N];
bool matched[N], fucked[N];
int fuckcnt;

// 本质上是在求二分图最大匹配的非必经点
// 从一个非必经点出发，沿着匹配链依次替换，能替换到的也是非必经点
void doFuck(int u){
    if(fucked[u]) return;
    fucked[u] = 1;
    fuckcnt++;
    for(int i = flow::head[u]; i != -1; i = flow::nxt[i]){
        // cout << "to = " << flow::to[i] << " cap = " << flow::cap[i] << endl;
        if(flow::to[i] != flow::st && flow::cap[i])
            doFuck(couple[flow::to[i] - wcnt]);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> grid[i];
        for(int j = 0; j < m; j++)
            if(grid[i][j] == '.'){
                cnt++;
                if((i + j) % 2 == 0){
                    white[wcnt] = {i, j};
                    wid[i][j] = wcnt++;
                }
                else{
                    black[bcnt] = {i, j};
                    bid[i][j] = bcnt++;
                }
                if(cnt > 2000){
                    cout << mans << endl;
                    return 0;
                }
            }
    }
    assert(bcnt == wcnt);
    flow::st = wcnt + bcnt + 1;
    flow::en = wcnt + bcnt + 2;
    int ans = cnt * (cnt - 1) / 2;
    for(int i = 0; i < bcnt; i++){
        flow::init();
        fuckcnt = 0;
        memset(fucked, 0, sizeof(fucked));
        memset(matched, 0, sizeof(matched));
        // 白点在左，黑点在右，枚举删去的黑点
        int curx = black[i].first, cury = black[i].second;
        // 源点向白点连边，白点向相邻黑点连边
        for(int j = 0; j < wcnt; j++){
            flow::addEdge(flow::st, j, 1);
            for(int k = 0; k < 4; k++){
                int x = white[j].first + dx[k];
                int y = white[j].second + dy[k];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(grid[x][y] == '.' && (x != curx || y != cury)){
                    flow::addEdge(j, wcnt + bid[x][y], 1);
                    // cout << "addEdge " << j << " " << wcnt + bid[x][y] << endl;
                }
            }
        }
        // 黑点向汇点连边
        for(int j = 0; j < bcnt; j++)
            if(i != j) flow::addEdge(wcnt + j, flow::en, 1);
        // 求最大匹配
        int match = flow::maxFlow();
        // cout << "match = " << match << endl;
        assert(match == wcnt - 1);
        // 找到每个黑点的匹配白点
        for(int j = 0; j < wcnt; j++){
            for(int k = flow::head[j]; ~k; k = flow::nxt[k]){
                if(k % 2 == 0 && flow::to[k] >= wcnt && flow::to[k] < wcnt + bcnt && flow::cap[k] == 0){
                    couple[flow::to[k] - wcnt] = j;
                    matched[j] = 1;
                    break;
                }
            }
        }
        // 找到未匹配的白点
        int unmatch = -1;
        for(int j = 0; j < wcnt; j++)
            if(!matched[j]){
                unmatch = j;
                break;
            }
        // cout << "unmatch = " << unmatch << endl;
        assert(unmatch != -1);
        // for(int j = 0; j < bcnt; j++)
        //     if(j != i)
        //         cout << "(" << black[j].first << "," << black[j].second << ") -- " 
        //              << "(" << white[couple[j]].first << "," << white[couple[j]].second << ")" << endl;
        // 删除这个白点，密铺方案仍然存在
        // 也可以保留这个白点，沿着匹配链上去删另一个白点
        doFuck(unmatch);
        // cout << "(" << curx << ", " << cury << ") " << "fuckcnt = " << fuckcnt << endl;
        ans -= fuckcnt;
    }
    cout << min(ans, mans) << endl;
    return 0;
}