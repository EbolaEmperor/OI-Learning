#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
int f[120][31][31][31];
int pwv[101][31];
int facn, ifac[31];
int n, m, k;

inline void add(int &x, const int &y){
    x = (x + y) % ha;
}

int Pow(int a, int b){
    int ans = 1;
    for(;b; b>>=1, a = (long long) a*a%ha)
        if(b&1) ans = (long long)ans*a%ha;
    return ans;
}

int main(){
    cin >> n >> m >> k;
    for(int i = 0; i <= m; i++){
        pwv[i][0] = 1;
        cin >> pwv[i][1];
        for(int j = 2; j <= n; j++)
            pwv[i][j] = (long long) pwv[i][j-1] * pwv[i][1] % ha;
    }

    facn = 1;
    for(int i = 1; i <= n; i++) facn = (long long) facn * i % ha;
    ifac[n] = Pow(facn, ha-2);
    for(int i = n-1; i >= 0; i--) ifac[i] = (long long) ifac[i+1] * (i+1) % ha;

    f[0][0][0][0] = facn;
    for(int i = 0; i <= m; i++)
        for(int j = 0; j <= n; j++)
            for(int t = 0; t <= k; t++)
                for(int p = 0; p <= n; p++){
                    for(int r = 0; r <= n-j; r++){
                        int ones = t + ( (p+r) & 1 );
                        if(ones > k) continue;
                        add(f[i+1][j+r][ones][(p+r)>>1], (long long) f[i][j][t][p] * pwv[i][r] % ha * ifac[r] % ha);
                    }
                }
    int ans = 0;
    for(int t = 0; t <= k; t++)
        for(int p = 0; p <= n; p++)
            if(__builtin_popcount(p)+t <= k) add(ans, f[m+1][n][t][p]);
    cout << ans << endl;
    return 0;
}