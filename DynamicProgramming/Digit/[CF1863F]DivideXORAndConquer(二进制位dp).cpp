#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull zero = 1ull << 62;
const int N = 10010;
ull xxsum[N], a[N], L[N], R[N];
bool ans[N];

// L[i] = orsum { highbit(xsum(i,r)) : r>=i && [i,r] can be remained }
// R[i] = orsum { highbit(xsum(l,i)) : l<=i && [l,i] can be remained }
// For range [i,j], if a range [i,x] (x>=j) can be remained such that
//    xsum(i,j)>=highbit(xsum(i,x)) or xsum(i,x)==0, 
//    then [i,j] can be remained.
//    This relationship can be translated as 
//       ( xsum(i,j) & L[i] ) != 0 || L[i] == 0
//    Similar for the other side with R[i].
// To avoid the special process that L[i] == 0, we set zero to be 1<<62.
//    If xsum(i,j)==0, we set it to be zero.

inline ull highbit(ull x){
	return (x == zero) ? zero : 1ull << (63 - __builtin_clzll(x));
}

inline ull xsum(int l, int r){
    return (xxsum[r] ^ xxsum[l-1]) ? (xxsum[r] ^ xxsum[l-1]) : zero;
}

int main(){
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%llu", a + i), xxsum[i] = xxsum[i-1] ^ a[i];
        L[1] = R[n] = highbit(xsum(1, n));
        for(int len = n - 1; len >= 1; --len)
            for(int l = 1, r; l + len - 1 <= n; ++l){
                r = l + len - 1;
                auto xs = xsum(l, r);
                if(( (xs | zero) & L[l]) || ( (xs | zero) & R[r])){
                    L[l] |= highbit(xs), R[r] |= highbit(xs);
                    if(len == 1) ans[l] = true;
                }
            }
        if(n == 1) ans[1] = true;
        for(int i = 1; i <= n; ++i)
            putchar('0' + ans[i]);
        putchar('\n');
        for(int i = 1; i <= n; ++i)
            L[i] = R[i] = xxsum[i] = ans[i] = 0;
    }
    return 0;
}