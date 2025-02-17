// 做法解析见 Lecture 16 - Problem P
#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int ha = 1e9 + 7;
int fac[N * N * 2], ifac[N * N * 2], f[N * 2][N];

int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

void init(int n){
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
        fac[i] = 1ll * fac[i - 1] * i % ha;
    ifac[n] = Pow(fac[n], ha - 2);
    for(int i = n; i >= 1; i--)
        ifac[i - 1] = 1ll * ifac[i] * i % ha;
}

int C(int n, int m){
    return 1ll * fac[n] * ifac[m] % ha * ifac[n - m] % ha;
}

int main(){
    int n, k;
    cin >> n >> k;
    if(k == 1){
        cout << 1 << endl;
        return 0;
    }
    int fuck = max(n, k);
    init(2 * fuck * fuck);
    f[2 * n + 1][0] = 1;
    for(int i = 2 * n; i >= 1; i--)
        for(int x = 0; x <= n; x++){
            f[i][x] = f[i + 1][x + 1];
            if(x && f[i + 1][x - 1]){
                assert((i + x) & 1);
                int pos = (k - 1) * (2 * n - i - 1 + x) / 2 
                        + (2 * n - i + 1 - x) / 2 + 1;
                f[i][x] = (f[i][x] + 
                          1ll * f[i + 1][x - 1] 
                          * C(k - 2 + pos - 1, pos - 1)) % ha;
            }
        }
    cout << 1ll * f[1][0] * fac[n] % ha << endl;
    return 0;
}