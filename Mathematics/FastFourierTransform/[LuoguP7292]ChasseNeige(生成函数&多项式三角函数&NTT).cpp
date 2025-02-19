#include "Polynomial.h"

const int M = 2000020;
int fac[M + 5], ifac[M + 5], modinv[105];
int fp[22][M + 5];

int main(){
    fac[0] = 1;
    for(int i = 1; i <= M; i++)
        fac[i] = 1ll * fac[i - 1] * i % Mod;
    ifac[M] = Pow(fac[M], Mod - 2);
    for(int i = M - 1; i >= 0; i--)
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % Mod;
    modinv[1] = 1;
    for(int i = 2; i <= 100; i++)
        modinv[i] = 1ll * (Mod - Mod / i) * modinv[Mod % i] % Mod;

    int T, r;
    scanf("%d%d", &T, &r);
    r += 20;

    // 这里手动泰勒展开，因为多项式运算太慢
    Polynomial sinx(r), cosx(r);
    int fg = 1;
    for(int i = 1; i <= r; i += 2){
        sinx[i] = fg * ifac[i];
        if(sinx[i] < 0) sinx[i] += Mod;
        fg = -fg;
    }

    fg = 1;
    for(int i = 0; i <= r; i += 2){
        cosx[i] = fg * ifac[i];
        if(cosx[i] < 0) cosx[i] += Mod;
        fg = -fg;
    }

    Polynomial f = (sinx + constPoly(1)) * inv(cosx);

    for(int n = 1; n <= r; n++)
        fp[1][n] = 1ll * fac[n] * f[n] % Mod;
    for(int d = 2; d <= 20; d++)
        for(int n = d; n <= r; n++)
            fp[d][n] = (fp[d - 1][n + 1] 
                       - 1ll * (n - d + 2) * fp[d - 2][n] % Mod
                       - 2ll * fp[d - 1][n] % Mod
                       + 2 * Mod) % Mod * modinv[d - 1] % Mod;
    
    while(T--){
        int n, k;
        scanf("%d%d", &n, &k);
        printf("%d\n", fp[n - 2 * k][n]);
    }
    return 0;
}