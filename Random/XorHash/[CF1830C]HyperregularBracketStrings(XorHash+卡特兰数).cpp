#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int ha = 998244353;
int Pow(int a, int b){
    int ans = 1;
    for(; b; b >>= 1, a = 1ll * a * a % ha)
        if(b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int read(){
    int x = 0, fg = 1; char c = getchar();
    while(!isdigit(c) && c != '-') c = getchar();
    if(c == '-') fg = -1, c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * fg;
}

const int N = 300000;
int fac[N + 5], ifac[N + 5];
void initC(){
    fac[0] = 1;
    for(int i = 1; i <= N; i++)
        fac[i] = (long long) fac[i - 1] * i % ha;
    ifac[N] = Pow(fac[N], ha - 2);
    for(int i = N - 1; i >= 0; i--)
        ifac[i] = (long long) ifac[i + 1] * (i + 1) % ha;
}
inline int C(int n, int m){
    return (long long) fac[n] * ifac[m] % ha * ifac[n - m] % ha;
}
inline int Catalan(int n){
    return (long long) C(2 * n, n) * Pow(n + 1, ha - 2) % ha;
}

int work(){
    static mt19937_64 rnd(time(0));
    int n = read(), m = read();
    vector<LL> val(n + 2);
    for(int i = 0; i < m; ++i){
        LL v = rnd();
        val[read()] ^= v;
        val[read() + 1] ^= v;
    }
    unordered_map<LL, int> cnt;
    for(int i = 1; i <= n; ++i)
        ++cnt[val[i] ^= val[i - 1]];
    int ans = 1;
    for(auto pr : cnt){
        if(pr.second & 1) return 0;
        ans = (long long) ans * Catalan(pr.second / 2) % ha;
    }
    return ans;
}

int main(){
    initC();
    int T;
    scanf("%d", &T);
    while(T--) printf("%d\n", work());
    return 0;
}