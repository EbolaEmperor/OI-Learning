#include "Polynomial.h"

int main(){
    int n, m;
    scanf("%d%d", &n ,&m);
    vector<int> cnt(m + 1, 0);
    for(int i = 1, x; i <= n; i++){
        scanf("%d", &x);
        cnt[x]++;
    }

    int *inv = new int[m + 1];
    inv[1] = 1;
    for(int i = 2; i <= m; i++)
        inv[i] = (Mod - 1ll * (Mod / i) * inv[Mod % i] % Mod) % Mod;
    
    Polynomial f(m);
    for(int k = 1; k <= m; k++)
        for(int j = 1; j * k <= m; j++)
            f[j * k] = (f[j * k] + 1ll * cnt[k] * inv[j]) % Mod;
    f = exp(f);

    for(int i = 1; i <= m; i++)
        printf("%d\n", f[i]);
    return 0;
}