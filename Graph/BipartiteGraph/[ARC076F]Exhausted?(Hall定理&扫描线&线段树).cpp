#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int trmax[N << 2], tag[N << 2];
vector<int> hang[N];
int n, m;

void build(int o, int l, int r){
    trmax[o] = r;
    if(l == r) return;
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
}

void add(int o, int l, int r, int nl, int nr, int x){
    if(l >= nl && r <= nr) return tag[o] += x, void();
    int mid = (l + r) / 2;
    if(nl <= mid) add(o << 1, l, mid, nl, nr, x);
    if(nr > mid) add(o << 1 | 1, mid + 1, r, nl, nr, x);
    trmax[o] = max(trmax[o << 1] + tag[o << 1], 
                   trmax[o << 1 | 1] + tag[o << 1 | 1]);
}

int main(){
    scanf("%d%d", &n, &m);
    int maxl = 0, minr = m + 1;
    for(int i = 1; i <= n; i++){
        int l, r;
        scanf("%d%d", &l, &r);
        hang[l].push_back(r);
        maxl = max(maxl, l);
        minr = min(minr, r);
    }
    build(1, 0, m + 1);
    // 根据 Hall 定理，本题答案为 max( |S| + |\cap_{i\in S} (l_i, r_i)| ) - m
    //               其中 S \subset [1,n]
    int ans = n + max(minr - maxl - 1, 0);
    for(int l = 0; l <= m + 1; l++){
        // 枚举左端点，在右端点处记录 |S|+r，用线段树维护记录值的区间 max
        for(int r : hang[l])
            add(1, 0, m + 1, 0, r, 1);
        ans = max(ans, trmax[1] + tag[1] - l - 1);
    }
    ans = max(ans - m, 0);
    cout << ans << endl;
    return 0;
}