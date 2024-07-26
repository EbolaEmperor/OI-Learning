#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

void simpSqrt(int &m, int &p){
    p = 1;
    for(int i = 2; i * i <= m; i++)
        while(m % (i * i) == 0){
            m /= (i * i);
            p *= i;
        }
}

void simpFrac(int &p, int &q){
    int d = gcd(abs(p), abs(q));
    p /= d;
    q /= d;
    if(q < 0) p = -p, q = -q;
}

int main(){
    int T, M, a, b, c;
    scanf("%d%d", &T, &M);
    while(T--){
        scanf("%d%d%d", &a, &b, &c);
        if(a < 0) a = -a, b = -b, c = -c;
        int delta = b * b - 4 * a * c;
        if(delta < 0){
            puts("NO");
            continue;
        }
        int p;
        simpSqrt(delta, p);
        if(b == 0 && delta == 0){
            puts("0");
            continue;
        }
        if(delta == 1){
            int v = -b + p;
            int u = 2 * a;
            simpFrac(v, u);
            if(u == 1) printf("%d\n", v);
            else printf("%d/%d\n", v, u);
            continue;
        }
        int v = 2 * a;
        b = -b;
        simpFrac(b, v);
        int u = 2 * a;
        simpFrac(p, u);
        if(b != 0){
            if(v == 1) printf("%d", b);
            else printf("%d/%d", b, v);
        }
        if(b != 0 && delta != 0) printf("+");
        if(delta != 0){
            if(p != 1) printf("%d*", p);
            printf("sqrt(%d)", delta);
            if(u != 1) printf("/%d", u);
        }
        printf("\n");
    }
    return 0;
}