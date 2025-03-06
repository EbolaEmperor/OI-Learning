#include "Polynomial.h"

int main(){
    const int m = 1e5;
    static int fac[m + 1];
    fac[0] = 1;
    for(int i = 1; i <= m; i++)
        fac[i] = 1ll * fac[i - 1] * i % Mod;
    Polynomial F(m);
    F[1] = 1;
    F = exp(exp(F) - constPoly(1));
    int T, n;
    cin >> T;
    while(T--){
        cin >> n;
        cout << 1ll * F[n] * fac[n] % Mod << endl;
    }
    return 0;
}