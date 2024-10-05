#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
// f[i]: 飞到 i 号树的最小疲劳值
int f[N], h[N], n;

int solve(){
    int k;
    scanf("%d", &k);
    deque<int> dq;
    dq.push_back(1); f[1] = 0;
    for(int i = 2; i <= n; i++){
        if(!dq.empty() && dq.front() < i - k) dq.pop_front();
        f[i] = f[dq.front()] + (h[i] >= h[dq.front()]);
        while(!dq.empty() && (f[i] < f[dq.back()] 
              || f[i] == f[dq.back()] && h[i] >= h[dq.back()])) dq.pop_back();
        dq.push_back(i);
    }
    return f[n];
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", h + i);
    int q; scanf("%d", &q);
    while(q--) printf("%d\n", solve());
    return 0;
}