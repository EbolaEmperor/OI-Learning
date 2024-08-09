#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int read(){
    int x = 0, fg = 1; char c = getchar();
    while(!isdigit(c) && c != '-') c = getchar();
    if(c == '-') fg = -1, c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * fg;
}

int work(){
    static mt19937_64 rnd(time(0));
    int n = read(), m = read();
    vector<LL> val(n + 2);
    for(int i = 0; i < m; ++i){
        LL v = rnd();
        val[read()] ^= v;
        val[read()] ^= v;
    }
    for(int i = 2; i <= n; ++i)
        val[i] ^= val[i - 1];
    unordered_map<LL, int> cnt;
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        ans = max(ans, ++cnt[val[i]]);
    return n - ans;
}

int main(){
    int T = read();
    while(T--) printf("%d\n", work());
    return 0;
}