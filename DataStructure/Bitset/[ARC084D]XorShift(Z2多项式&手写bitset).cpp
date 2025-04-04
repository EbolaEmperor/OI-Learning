#include <bits/stdc++.h>
#include "MyBitset.h"
using namespace std;

const int MAX = 4000;
const int ha = 998244353;

BitSet<63> a[6], M, P, Q;
int pw2[MAX + 5];

int main() {
    pw2[0] = 1;
    for(int i = 1; i <= MAX; i++)
        pw2[i] = (pw2[i - 1] * 2) % ha;
    int n;
    cin >> n >> M;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        P = gcd(a[i], P);
    }
    int ans = 0, m = P.find_high();
    for (int i = M.find_high() - m; i >= 0; i--) {
        if(!Q[i + m]) {
            if(M[i + m]) {
                ans = (ans + pw2[i]) % ha;
                Q = Q ^ (P << i);
            }
        } else {
            if (!M[i + m]) Q = Q ^ (P << i);
            else ans = (ans + pw2[i]) % ha;
        }
        if(i == 0 && Q <= M) ans++;
    }
    printf("%d\n", ans % ha);
    return 0;
}