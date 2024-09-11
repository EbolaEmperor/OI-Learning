#include <bits/stdc++.h>
using namespace std;

const int ha = 998244353;
const int N = 5010;
int n, a[N], pre[N], g[N], sum[N];
int inv[N];

int Pow(int a, int b){
    int ans = 1;
    for(;b; b >>= 1, a = (long long) a * a % ha)
        if(b & 1) ans = (long long) ans * a % ha;
    return ans;
}

int fac(int n){
    int ans = 1;
    for(int i = 1; i <= n; i++)
        ans = (long long) ans * i % ha;
    return ans;
}

int main(){
    scanf("%d", &n);
    inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (long long) (ha - ha / i) * inv[ha % i] % ha;
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + 1 + n);
    if(a[n] < 2 * a[n-1]) return puts("0"), 0;
    for(int i = 1; i <= n; i++){
        pre[i] = pre[i - 1];
        while(a[pre[i] + 1] * 2 <= a[i]) pre[i]++;
    }
    sum[0] = fac(n - 1);
    for(int i = 1; i <= n; i++){
        g[i] = sum[pre[i]];
        sum[i] = (sum[i - 1] + 1ll * g[i] * inv[n - 1 - pre[i]]) % ha;
    }
    cout << (long long) g[n] * Pow(fac(n - 1 - pre[n]), ha - 2) % ha << endl;
    return 0;
}