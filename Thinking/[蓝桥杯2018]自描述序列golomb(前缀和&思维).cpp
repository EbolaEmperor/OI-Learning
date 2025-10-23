#include <bits/stdc++.h>
using namespace std;

const int N = 11000000;
int a[N+5];
long long g[N+5], h[N+5];

int main(){
    long long n; cin >> n;
    int i, x = 0, cnt = 0;
    for(i = 1; i <= N; ++i){
        if(cnt >= a[x]) ++x, cnt = 0;
        a[i] = x; ++cnt;
        g[i] = g[i-1] + a[i];
        h[i] = h[i-1] + (long long) i * a[i];
        if (h[i] >= n) break;
    }
    long long ans = g[i], p = h[i];
    while (p - i >= n) p -= i, --ans;
    cout << ans << endl;
    return 0;
}