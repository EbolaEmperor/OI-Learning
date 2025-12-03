#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 8005;
const int MAXM = 805;

int n, m;
vector<int> adj[MAXN];
int dep[MAXN];
int max_d[MAXN];
int heavy[MAXN];
long long f[MAXN][MAXM];
long long g[MAXN][MAXM];

// DSU on tree structures
vector<long long> pool[MAXN];
int id[MAXN];
long long lazy[MAXN];

void dfs_init(int u, int d) {
    dep[u] = d;
    max_d[u] = d;
    heavy[u] = 0;
    for (int v : adj[u]) {
        dfs_init(v, d + 1);
        max_d[u] = max(max_d[u], max_d[v]);
        if (heavy[u] == 0 || max_d[v] > max_d[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

void solve_k(int u, int k) {
    if (adj[u].empty()) {
        // Leaf
        id[u] = u;
        pool[u].clear();
        lazy[u] = 0;
        pool[u].push_back(f[u][k+1]); 
        
        g[u][k] = k; 
        f[u][k] = k;
        // if (k <= 2) cerr << "u=" << u << " k=" << k << " f=" << f[u][k] << " g=" << g[u][k] << " leaf" << endl;
        return;
    }

    // Recurse heavy
    solve_k(heavy[u], k);
    id[u] = id[heavy[u]];

    // Recurse light
    for (int v : adj[u]) {
        if (v != heavy[u]) {
            solve_k(v, k);
        }
    }
    
    long long G_base = k;
    for (int v : adj[u]) {
        G_base += g[v][k];
    }

    // Update lazy for heavy child path
    lazy[id[u]] += (G_base - g[heavy[u]][k]);

    // Merge lights
    for (int v : adj[u]) {
        if (v == heavy[u]) continue;
        
        int pid = id[u];
        int vid = id[v];
        long long v_lazy = lazy[vid];
        long long diff = G_base - g[v][k];
        
        int u_sz = pool[pid].size();
        int v_sz = pool[vid].size();
        
        for (int i = 0; i < v_sz; ++i) {
            int v_idx = v_sz - 1 - i;
            int u_idx = u_sz - 1 - i;
            
            long long val = pool[vid][v_idx] + v_lazy;
            long long target = val + diff;
            
            long long current_u = pool[pid][u_idx] + lazy[pid];
            if (target > current_u) {
                pool[pid][u_idx] = target - lazy[pid];
            }
        }
        pool[vid].clear(); // Release memory
    }
    
    // Add current node f(u, k+1) at depth dep[u]
    pool[id[u]].push_back(f[u][k+1] - lazy[id[u]]);

    // Query for g[u][k]
    long long jump_val = -2e18; 
    int sz = pool[id[u]].size();
    int idx = sz - 1 - k;
    
    if (idx >= 0) {
        jump_val = pool[id[u]][idx] + lazy[id[u]];
    }
    
    g[u][k] = G_base;
    if (jump_val > G_base) g[u][k] = jump_val;
    
    // Compute f[u][k]
    long long max_diff = -2e18;
    for (int v : adj[u]) {
        long long diff = f[v][k+1] - g[v][k];
        if (diff > max_diff) max_diff = diff;
    }
    f[u][k] = max_diff + G_base;
}

void run_case() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) adj[i].clear();
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    
    dfs_init(1, 0);
    
    // Init f for k=m+1
    // For any node, if we request f with k > m, it implies we can't extend further validly in a way that matters for g
    // Or it is a leaf case.
    // We set f[u][m+1] = m + 1.
    for (int i = 1; i <= n; ++i) {
        f[i][m+1] = m + 1;
    }
    
    // Iterate k from m down to 1
    for (int k = m; k >= 1; --k) {
        solve_k(1, k);
        pool[id[1]].clear();
    }
    
    cout << f[1][1] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int cases;
    if (cin >> cases)
    while (cases--) run_case();
    return 0;
}

