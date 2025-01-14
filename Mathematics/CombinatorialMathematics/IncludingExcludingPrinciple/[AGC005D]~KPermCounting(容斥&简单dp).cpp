#include <bits/stdc++.h>
using namespace std;

const int ha = 924844033;
const int N = 2005;
// f[i][j][0/1]: 前 i 个点，选了 j 个，其中第 i 个点 不选/选 的方案数
int f[N << 1][N][2], fac[N], len[N << 1], n, k, tot = 0;
bool vis[N][N], split[N << 1];

int travel(int i, int j){
    if(vis[i][j]) return 0;
    vis[i][j] = 1;
    int cnt = 1;
    if(j < i){
        if(i > 2 * k) cnt += travel(i - 2 * k, j);
        if(j + 2 * k <= n) cnt += travel(i, j + 2 * k);
    } else {
        if(j > 2 * k) cnt += travel(i, j - 2 * k);
        if(i + 2 * k <= n) cnt += travel(i + 2 * k, j);
    }
    return cnt;
}

inline int add(int x, int y){
    return x + y >= ha ? x + y - ha : x + y;
}

inline int mns(int x, int y){
    return x - y < 0 ? x - y + ha : x - y;
}

int main(){
    cin >> n >> k;
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
        fac[i] = (long long) fac[i - 1] * i % ha;
    for(int i = 1, tmp; i <= n; i++){
        if(i > k){
            tmp = travel(i, i - k);
            if(tmp) len[++tot] = tmp;
        }
        if(i + k <= n){
            tmp = travel(i, i + k);
            if(tmp) len[++tot] = tmp;
        }
    }
    for(int i = 1; i <= tot; i++){
        len[i] += len[i - 1];
        split[len[i] + 1] = true;
    }
    int m = len[tot];
    f[0][0][0] = 1;
    for(int i = 1; i <= m; i++)
        for(int j = 0; j <= i && j <= n; j++){
            f[i][j][0] = add(f[i - 1][j][0], f[i - 1][j][1]);
            if(j){
                f[i][j][1] = f[i - 1][j - 1][0];
                if(split[i]) f[i][j][1] = add(f[i][j][1], f[i - 1][j - 1][1]);
            }
        }
    int ans = 0;
    for(int i = 0; i <= n; i++){
        int tmp = (long long) (f[m][i][0] + f[m][i][1]) * fac[n - i] % ha;
        if(i & 1) ans = mns(ans, tmp);
        else ans = add(ans, tmp);
    }
    cout << ans << endl;
    return 0;
}