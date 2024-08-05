#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha = 1e9 + 7;
const int N = 110;
int f[N][N*N], p[N][N], C[N][N], n, k;
LL m, cnt[N];

int Pow(int a, LL b){
    int ans = 1;
    for(; b; b >>= 1, a = (LL) a * a % ha)
        if(b & 1) ans = (LL) ans * a % ha;
    return ans;
}

void init(){
    cin >> n >> m >> k;
    for(int i = 0; i <= n; i++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % ha;
    }
    m--;
    for(int i = 0; i < n; i++)
        cnt[i] = m / n + (i <= m % n);
    for(int t = 0; t <= n; t++)
        for(int i = 0; i < n; i++)
            p[t][i] = Pow(C[n][t], cnt[i]);
}

int main(){
    init();
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= (i + 1) * n; j++){
            if(!i){
                f[i][j] = p[j][i];
                continue;
            }
            for(int t = 0; t <= min(n, j); t++)
                f[i][j] = (f[i][j] + (LL) f[i-1][j-t] * p[t][i]) % ha;
        }
    cout << f[n-1][k] << endl;
    return 0;
}