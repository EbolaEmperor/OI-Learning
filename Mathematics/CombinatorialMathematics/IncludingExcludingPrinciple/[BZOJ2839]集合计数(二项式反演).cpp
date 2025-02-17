#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int ha = 1e9 + 7;
int fac[N], ifac[N];
int pw2[N];

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
    pw2[0] = 1;
    for(int i = 1; i <= n; i++)
        pw2[i] = (pw2[i - 1] << 1) % (ha - 1);
}

int C(int n, int m){
    return 1ll * fac[n] * ifac[m] % ha * ifac[n - m] % ha;
}

int computeF(int n, int k){
    return 1ll * C(n, k) * (Pow(2, pw2[n - k]) +  ha - 1) % ha;
}

int main(){
    int n, k;
    cin >> n >> k;
    init(n);
    int ans = 0;
    for(int i = k; i <= n; i++){
        int tmp = 1ll * C(i, k) * computeF(n, i) % ha;
        if((i - k) & 1) ans = (ans - tmp + ha) % ha;
        else ans = (ans + tmp) % ha;
    }
    cout << ans << endl;
}