#include <iostream>
#include <queue>
using namespace std;

const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int fa[N], indeg[N], siz[N], n, k;
int f[N];

void toposort(){
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(!indeg[i]) q.push(i);
    while(!q.empty()){
        int u = q.front(); q.pop();
        siz[fa[u]] += siz[u];
        if(!--indeg[fa[u]]) q.push(fa[u]);
    }
}

int cycleSize(int i){
    int cnt = 1; indeg[i] = 0;
    while(indeg[fa[i]])
        i = fa[i], indeg[i] = 0, cnt++;
    return cnt;
}

int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = (long long) a * a % mod)
        if(b & 1) ans = (long long) ans * a % mod;
    return ans;
}

void initf(){
    f[1] = k;
    f[2] = (long long) k * (k - 1) % mod;
    f[3] = (long long) k * (k - 1) * (k - 2) % mod;
    for(int i = 4; i <= n; i++)
        f[i] = ((k - 1ll) * f[i - 2] + (k - 2ll) * f[i - 1]) % mod;
}

int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> fa[i];
        indeg[fa[i]]++;
        siz[i] = 1;
    }
    toposort();
    initf();
    int cyctot = 0, ans = 1;
    for(int i = 1; i <= n; i++){
        if(!indeg[i]) continue;
        int cnt = cycleSize(i);
        ans = (long long) ans * f[cnt] % mod;
        cyctot += cnt;
    }
    ans = (long long) ans * Pow(k - 1, n - cyctot) % mod;
    cout << ans << endl;
    return 0;
}