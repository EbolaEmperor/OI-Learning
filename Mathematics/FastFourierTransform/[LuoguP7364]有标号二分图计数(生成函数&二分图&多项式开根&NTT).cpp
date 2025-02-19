#include "Polynomial.h"

inline long long Cn2(int n){
    if(n < 2) return 0;
    return (long long) n * (n - 1) / 2;
}

int main(){
    const int n = 1e5;
    Polynomial p(n);
    int fact = 1;
    for(int i = 0; i <= n; i++){
        int pw2 = Pow(2, Cn2(i) % (Mod - 1));
        p[i] = 1ll * Pow(fact, Mod - 2) 
                   * Pow(pw2, Mod - 2) % Mod;
        fact = 1ll * fact * (i + 1) % Mod;
    }
    p = p * p;
    for(int i = 0; i <= n; i++)
        p[i] = 1ll * p[i] * Pow(2, Cn2(i) % (Mod - 1)) % Mod;
    p = sqrt(p);
    fact = 1;
    for(int i = 1; i <= n; i++){
        printf("%lld\n", 1ll * p[i] * fact % Mod);
        fact = 1ll * fact * (i + 1) % Mod;
    }
    return 0;
}