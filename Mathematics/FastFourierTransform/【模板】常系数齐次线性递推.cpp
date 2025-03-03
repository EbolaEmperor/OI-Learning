#include "Polynomial.h"

Polynomial getR(int n, const Polynomial &p){
    Polynomial H(p.degree() - 1), R(0);
    H[1] = 1;
    R[0] = 1;
    for(; n; n >>= 1){
        if(n & 1) R = R * H % p;
        H = H * H % p;
    }
    return R;
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    Polynomial p(k);
    for(int i = 1, c; i <= k; i++){
        scanf("%d", &c);
        p[k - i] = (Mod - c) % Mod;
    }
    p[k] = 1;
    auto R = getR(n, p);
    vector<int> a(k);
    for(int& x : a){
        scanf("%d", &x);
        if(x < 0) x += Mod;
    }
    int ans = 0;
    for(int i = 0; i < k; i++)
        ans = (ans + 1ll * a[i] * R[i]) % Mod;
    printf("%d\n", ans);
    return 0;
}