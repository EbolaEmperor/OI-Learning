#include<bits/stdc++.h>
using namespace std;

const int N = 20010;
int n, m, tot;

namespace Tree{
    vector<int> g[N];
    //  f[u]: 对于圆点，表示从 u 出发，在子树里走，回到 u 点，最长路线长度
    //        对于方点，表示环内节点(除 fa[u] 外) f 值之和
    // f2[u]: 对于圆点，表示从 u 出发，在子树里结束，最长路线长度
    //        对于方点，表示从 fa[u] 出发，在环内以及下方子树中结束，最长路线长度
    int f[N], f2[N];

    void dfs(int u){
        for(int v : g[u]){
            dfs(v);
            if(u > n) f[u] += f[v];
            else if(g[v].size() > 1) f[u] += f[v] + g[v].size() + 1;
        }
        if(u <= n){ // 圆点
            for(int v : g[u]){
                int tmp = (g[v].size() > 1) ? (f[u] - f[v] - g[v].size() - 1) : f[u];
                f2[u] = max(f2[u], tmp + f2[v]);
            }
            f2[u] = max(f2[u], f[u]);
        } else if(g[u].size() > 1){ // 非平凡方点 (长度至少为 3 的环)
            int sum = 1;
            for(int v : g[u]){ // 顺时针走
                f2[u] = max(f2[u], sum + f2[v]);
                sum += f[v] + 1;
            }
            sum = 1;
            for(auto it = g[u].rbegin(); it != g[u].rend(); ++it){ // 逆时针走
                f2[u] = max(f2[u], sum + f2[*it]);
                sum += f[*it] + 1;
            }
        } else f2[u] = f2[g[u].front()] + 1; // 平凡方点
    }
}

namespace Graph{
    vector<int> g[N];
    int pre[N], low[N], dfn = 0;
    stack<int> stk;
    
    void add_edge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void Tarjan(int u){
        pre[u] = low[u] = ++dfn; stk.push(u);
        for(int v : g[u]){
            if(!pre[v]){
                Tarjan(v);
                low[u] = min(low[u], low[v]);
                if(low[v] >= pre[u]){
                    int o; ++tot;
                    do{
                        assert(!stk.empty());
                        o = stk.top();
                        stk.pop();
                        Tree::g[tot].push_back(o);
                    } while(o != v);
                    Tree::g[u].push_back(tot);
                    assert(tot <= 2 * n);
                }
            } else low[u] = min(low[u], pre[v]);
        }
    }
}

int main(){
    scanf("%d%d", &n, &m); tot = n;
    for(int i = 1, u, v; i <= m; i++){
        scanf("%d%d", &u, &v);
        Graph::add_edge(u, v);
    }
    Graph::Tarjan(1);
    Tree::dfs(1);
    cout << Tree::f2[1] << endl;
    return 0;
}
