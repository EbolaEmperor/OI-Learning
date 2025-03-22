#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

const int B1 = 64, B2 = 200;
const int N = 100010;
int n, m, q, a[N], b[N];
vector<int> G[N];

struct Operation{
    int o, x, y, z;
    Operation(int o, int x, int y, int z): o(o), x(x), y(y), z(z) {}
};
vector<Operation> ops;

ull lowbit(ull x){
    return x & -x;
}

int lg2(ull x){
    return 63 - __builtin_clzll(x);
}

void solve(){
    static ull f[N], g[N];
    static int inv_b[N];
    for(int i = 1; i <= n; i++) inv_b[b[i]] = i;
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    int qry = 0;
    vector<int> changed;
    ull cur = 0;
    for(auto [o, x, y, z] : ops){
        if(o == 3){
            f[x] |= 1ull << qry;
            // 询问 qry 对应的区间范围是 [y, z]，这里做一下差分
            g[y] |= 1ull << qry;
            g[z + 1] |= 1ull << qry;
            cur |= 1ull << qry;
            ++qry;
        } else {
            changed.push_back(x);
            changed.push_back(y);
            inv_b[b[x]] = inv_b[b[y]] = 0;
        }
    }
    // cur = (1ull << qry) - 1;
    vector<int> ans(qry, 0);
    for(int i = 1; i <= n; i++) g[i] ^= g[i - 1];
    for(int i = 1; i <= n; i++){
        if(!f[i]) continue;
        for(int v : G[i]){
            f[v] |= f[i];
        }
    }
    for(int bv = n; bv >= 1; bv--){
        int i = inv_b[bv];
        if(!i) continue;
        // cout << i << " " << cur << " " << f[i] << " " << g[a[i]] << endl;
        ull can = f[i] & cur & g[a[i]];
        cur ^= can;
        for(; can; can ^= lowbit(can)){
            int j = lg2(lowbit(can));
            ans[j] = bv;
        }
        if(!cur) break;
    }
    // cout << endl;
    sort(changed.begin(), changed.end());
    changed.erase(unique(changed.begin(), changed.end()), changed.end());
    qry = 0;
    for(auto [o, x, y, z] : ops){
        if(o == 3){
            for(int i : changed){
                if((f[i] & (1ull << qry)) && a[i] >= y && a[i] <= z){
                    ans[qry] = max(ans[qry], b[i]);
                }
            }
            ++qry;
        } else if(o == 1){
            swap(a[x], a[y]);
        } else {
            swap(b[x], b[y]);
        }
    }
    for(int i = 0; i < qry; i++) cout << ans[i] << '\n';
    ops.clear();
}

void work(){
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++) G[i].clear();
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    int qry = 0;
    while(q--){
        int o, x, y, z = -1;
        cin >> o >> x >> y;
        if(o == 3){
            cin >> z;
            ++qry;
        }
        ops.emplace_back(o, x, y, z);
        if(qry == B1 || ops.size() == B2){
            solve();
            qry = 0;
        }
    }
    if(qry) solve();
}

int main(){
    int testID, T;
    cin >> testID >> T;
    while(T--) work();
    return 0;
}