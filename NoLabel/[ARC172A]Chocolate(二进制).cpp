#include <bits/stdc++.h>
using namespace std;

const int MAX = 35;
int n, m, s;
long long c[MAX], cnt[MAX];
// c[k]: 用户需要几个 2^k * 2^k 的切糕
// cnt[k]: 我有几个 2^k * 2^k 的切糕

int main(){
    cin >> n >> m >> s;
    while(s--){
        int x; cin >> x;
        ++c[x];
    }
    int N = n, M = m;
    for(int k = 30; k >= 0; --k){
        if(n >= (1<<k)) cnt[k] += (M >> k);
        if(m >= (1<<k)) cnt[k] += (N >> k);
        if(n >= (1<<k) && m >= (1<<k)) --cnt[k];
        n %= (1<<k);
        m %= (1<<k);
    }
    for(int k = 30; k >= 0; --k){
        if(c[k] > cnt[k]) return puts("No"), 0;
        cnt[k] -= c[k];
        if(k) cnt[k-1] += 4 * cnt[k];
    }
    puts("Yes");
    return 0;
}